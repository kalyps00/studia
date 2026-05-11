nonsense(long*, long, long*, long*):
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -72(%rbp)
        movq    %rsi, -80(%rbp)
        movq    %rdx, -88(%rbp)
        movq    %rcx, -96(%rbp)
        movq    -72(%rbp), %rax
        movq    16(%rax), %rax
        movq    %rax, -8(%rbp)
        movq    -72(%rbp), %rax
        movq    24(%rax), %rax
        movq    %rax, -16(%rbp)
        movq    -72(%rbp), %rax
        movq    32(%rax), %rax
        movq    %rax, -24(%rbp)
        movq    -80(%rbp), %rdx
        movq    %rdx, %rax
        salq    $2, %rax
        addq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        movq    %rax, -32(%rbp)
        movq    -16(%rbp), %rax
        imulq   -32(%rbp), %rax
        movq    %rax, -40(%rbp)
        movq    -40(%rbp), %rax
        leaq    0(,%rax,8), %rdx
        movq    -72(%rbp), %rax
        addq    %rdx, %rax
        movq    (%rax), %rax
        movq    %rax, -48(%rbp)
        movq    -8(%rbp), %rax
        salq    $3, %rax
        movq    %rax, -56(%rbp)
        movq    -24(%rbp), %rdx
        movq    -56(%rbp), %rax
        addq    %rax, %rdx
        movq    -88(%rbp), %rax
        movq    %rdx, (%rax)
        movq    -48(%rbp), %rax
        leaq    4(%rax), %rdx
        movq    -96(%rbp), %rax
        movq    %rdx, (%rax)
        nop
        popq    %rbp
        ret