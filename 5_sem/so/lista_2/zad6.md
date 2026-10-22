top / ps -eo pid,comm,pri,ni
echo "" | awk '{for(;;) {}}'
pgrep firefox
renice +15 -p <PID>
pkill awk
