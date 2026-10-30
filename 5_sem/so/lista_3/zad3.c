setup_rt_frame(struct ksignal *ksig, struct pt_regs *regs)
{
    /* Perform fixup for the pre-signal frame. */
    rseq_signal_deliver(ksig, regs); // zabezpiecznie na ramke sygnalu (to sie dzieje jak przerwalo w trakcie modyfikowania rseq)

    /* Set up the stack frame */
    if (is_ia32_frame(ksig)) // 32 bitowy proces na 64 biyowym krenelu
    {
        if (ksig->ka.sa.sa_flags & SA_SIGINFO)
            return ia32_setup_rt_frame(ksig, regs);
        else
            return ia32_setup_frame(ksig, regs);
    }
    else if (is_x32_frame(ksig)) // 64 bitowe rejestry ale 32 bitowe wskazniki odpalone na 64 bitowym kernelu
    {
        return x32_setup_rt_frame(ksig, regs);
    }
    else
    {
        return x64_setup_rt_frame(ksig, regs); // 64 na 64 bitowym kernelu
    }
}

static void
handle_signal(struct ksignal *ksig, struct pt_regs *regs)
{
    bool stepping, failed;
    struct fpu *fpu = x86_task_fpu(current);

    if (v8086_mode(regs))
        save_v86_state((struct kernel_vm86_regs *)regs, VM86_SIGNAL);

    /* Are we from a system call? */ // dokładnie to tutaj sie dzieje sprawdzamy czy ejstesmyw  syscallu
    if (syscall_get_nr(current, regs) != -1)
    {
        /* If so, check system call restarting.. */
        switch (syscall_get_error(current, regs))
        {
        case -ERESTART_RESTARTBLOCK:
        case -ERESTARTNOHAND:
            regs->ax = -EINTR;
            break;

        case -ERESTARTSYS:
            if (!(ksig->ka.sa.sa_flags & SA_RESTART))
            {
                regs->ax = -EINTR;
                break;
            }
            fallthrough;
        case -ERESTARTNOINTR:
            regs->ax = regs->orig_ax; // przywrocenie numeru syscallu do rejestru ax
            regs->ip -= 2;            // instuction pointer -2 bo tyle ma instrukcja syscall
            break;
        }
    }

    /*
     * If TF is set due to a debugger (TIF_FORCED_TF), clear TF now
     * so that register information in the sigcontext is correct and
     * then notify the tracer before entering the signal handler.
     */
    stepping = test_thread_flag(TIF_SINGLESTEP);
    if (stepping)
        user_disable_single_step(current);

    failed = (setup_rt_frame(ksig, regs) < 0); // stawiamy ramke sygnalowa na stosie procesu i sprawdzamy czy sie udalo
    if (!failed)
    {
        /*
         * Clear the direction flag as per the ABI for function entry.
         *
         * Clear RF when entering the signal handler, because
         * it might disable possible debug exception from the
         * signal handler.
         *
         * Clear TF for the case when it wasn't set by debugger to
         * avoid the recursive send_sigtrap() in SIGTRAP handler.
         */
        regs->flags &= ~(X86_EFLAGS_DF | X86_EFLAGS_RF | X86_EFLAGS_TF); // zerujemy Direction flag, Resume flag i Trap flag
        /*
         * Ensure the signal handler starts with the new fpu state.
         */
        fpu__clear_user_states(fpu); // czyszczenie stanu fpu w procesie (floating point unit takie do liczenia floatow)
    }
    signal_setup_done(failed, ksig, stepping);
}
void arch_do_signal_or_restart(struct pt_regs *regs)
{
    struct ksignal ksig;

    if (get_signal(&ksig))
    {
        /* Whee! Actually deliver the signal.  */
        handle_signal(&ksig, regs);
        return;
    }

    /* Did we come from a system call? */
    if (syscall_get_nr(current, regs) != -1)
    {
        /* Restart the system call - no handlers present */
        switch (syscall_get_error(current, regs))
        {
        case -ERESTARTNOHAND:
        case -ERESTARTSYS:
        case -ERESTARTNOINTR:
            regs->ax = regs->orig_ax;
            regs->ip -= 2;
            break;

        case -ERESTART_RESTARTBLOCK:
            regs->ax = get_nr_restart_syscall(regs);
            regs->ip -= 2;
            break;
        }
    }

    /*
     * If there's no signal to deliver, we just put the saved sigmask
     * back.
     */
    restore_saved_sigmask();
}

int x64_setup_rt_frame(struct ksignal *ksig, struct pt_regs *regs)
{
    sigset_t *set = sigmask_to_save();
    struct rt_sigframe __user *frame;
    void __user *fp = NULL;
    unsigned long uc_flags;

    /* x86-64 should always use SA_RESTORER. */
    if (!(ksig->ka.sa.sa_flags & SA_RESTORER)) // restorer - funkcja do przywrocenia stanu procesu po sygnale
        return -EFAULT;

    frame = get_sigframe(ksig, regs, sizeof(struct rt_sigframe), &fp);
    // obliczamy gdzie na stosie procesu ma byc ramka sygnalowa i zwracamy wskaznik do niej w frame,
    // a w fp wskaznik do miejsca gdzie ma byc zapisany kontekst fpu
    uc_flags = frame_uc_flags(regs);

    if (!user_access_begin(frame, sizeof(*frame)))
        return -EFAULT;

    /* Create the ucontext.  */
    unsafe_put_user(uc_flags, &frame->uc.uc_flags, Efault);
    unsafe_put_user(0, &frame->uc.uc_link, Efault);
    unsafe_save_altstack(&frame->uc.uc_stack, regs->sp, Efault);

    /* Set up to return from userspace.  If provided, use a stub
       already in userspace.  */
    unsafe_put_user(ksig->ka.sa.sa_restorer, &frame->pretcode, Efault);   // restorer - funkcja do przywrocenia stanu procesu po sygnale
    unsafe_put_sigcontext(&frame->uc.uc_mcontext, fp, regs, set, Efault); // zapisujemy kontekst procesu w ramce sygnalowej na stosie procesu
    unsafe_put_sigmask(set, frame, Efault);
    user_access_end();

    if (ksig->ka.sa.sa_flags & SA_SIGINFO)
    {
        if (copy_siginfo_to_user(&frame->info, &ksig->info)) // informacje o sygnale zapisujemy uzytkownikowi w ramce sygnalowej na stosie procesu np kto wyslal sygnal
            return -EFAULT;
    }

    if (setup_signal_shadow_stack(ksig))
        return -EFAULT;

    /* Set up registers for signal handler */
    regs->di = ksig->sig; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! do rdi wpisujemy numer sygnalu
    /* In case the signal handler was declared without prototypes */
    regs->ax = 0;

    /* This also works for non SA_SIGINFO handlers because they expect the
       next argument after the signal number on the stack. */
    regs->si = (unsigned long)&frame->info;           // wstawiamy wskaznik do struktury siginfo_t w rejestrze rsi
    regs->dx = (unsigned long)&frame->uc;             // do rdx struktury ucontext_t w której zapisany jest kontekst procesu w momencie wyslania sygnalu
    regs->ip = (unsigned long)ksig->ka.sa.sa_handler; // wstawiamy wskaznik do funkcji obslugi sygnalu w rejestrze rip jak oddamy dsotep to zacznie sie wykonywać handler

    regs->sp = (unsigned long)frame; // ustawiamy wskaznik stosu w rejestrze rsp na ramke sygnalowa na stosie procesu

    /*
     * Set up the CS and SS registers to run signal handlers in
     * 64-bit mode, even if the handler happens to be interrupting
     * 32-bit or 16-bit code.
     *
     * SS is subtle.  In 64-bit mode, we don't need any particular
     * SS descriptor, but we do need SS to be valid.  It's possible
     * that the old SS is entirely bogus -- this can happen if the
     * signal we're trying to deliver is #GP or #SS caused by a bad
     * SS value.  We also have a compatibility issue here: DOSEMU
     * relies on the contents of the SS register indicating the
     * SS value at the time of the signal, even though that code in
     * DOSEMU predates sigreturn's ability to restore SS.  (DOSEMU
     * avoids relying on sigreturn to restore SS; instead it uses
     * a trampoline.)  So we do our best: if the old SS was valid,
     * we keep it.  Otherwise we replace it.
     */
    regs->cs = __USER_CS;

    if (unlikely(regs->ss != __USER_DS))
        force_valid_ss(regs);

    return 0;

Efault:
    user_access_end();
    return -EFAULT;
}