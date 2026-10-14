bash -c 'sleep 20 & echo "PPID: $$, child PID: $!"'
ps -C sleep -o user,pid,ppid,pgid,stat,cmd

sierota jest przejmowana przez proces najblizej w drzewie ktorey ejst subreaperem lub repera(PID 1)

Zombie:
(bash -c 'sleep 0.1 & exec sleep 30') &
ps -C sleep -o user,pid,ppid,pgid,stat,cmd

W jaki sposób pogrzebać proces, który wszedł w stan zombie?
Rodzic musi pogrzebać naszego zombie wywołujać wait(2) lub
waitpid(2), przez wysłanie SIGCHLD do rodzica lub przez zabicie rodzica

Czemu proces nie może sam siebie pogrzebać?
Przez to ze proces umierajac robi \_exit(2) procesor wykonując to krozyta ze stosu jadra ktory nalezy o tego procesu czyi musialby ejdnoczesnie robic cos i usuwac swoja pamiec do tego obsluga kodu wyjscia obecnie zjamuje sie tym rodzic

(a) dziecko może czekać na zmianę stanu swojego
rodzica
zapetlili by sie bo rodzic czeka na dzieckoa dziecko na rodzica i procesy nigdy sie nie skoncza

(b) wiele procesów oczekuje na zmianę stanu jednego procesu
race condition przez to ze waitpid(2) usuwa zombie to wiele precosow by scigalo sie kto usunie a mozna toz robic tylko raz a gdyby czekac na osttni to sakd mamy wiedziec ze to jest wlasnie soatni czekajacy proces i zombie mogly by wisiec
