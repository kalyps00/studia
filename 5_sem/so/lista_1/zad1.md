ps -eo user,pid,ppid,pgid,tid,pri,stat,wchan,cmd | head -n 25

USER - właściciel,
PID - identyfikator procesu, (Process ID)
PPID - identyfikator rozica procesu (Process parent ID)
PGID -identyfikator grupy procesu (Process group ID)

Kto jest rodzicem procesu innit? - rodzicem innit jest proces 0 czyli swapper/ idle process

Które procesy sa procesami jądra?
to te ktore w CMD maja [] do tego w grupie procesu sa grupa 0 i ich parentem jest 2 czyli [kthreadd]
którego rodziccem jest proces 0 (swapper) i do tego w WCHAN -

Znaczneie znaków w kolumnie stat
R - running
S - interuptable sleep - proces czeka na np dane z wejscia i jest budzony jak jedostanie
D -uninteruptable sleep - proces czeka na np operacje sprzetowa np dysk inie mozna go obudzić a nawet zabic
I - idle kernel thread - bezczynny watek jadra
T/t - proces zatrzymany sygnalem np (SIGSTOP) lub sledzony przez debuger
Z - zombie - proces zakonoczny ale rodzic dalej nie odebral konca jego dzialania

flagi dodatkowe:
s - sesion leader
< - high priority (niski niceness)
N - low priority ( wysoki niceness)
l - proces wielowatkowy

pstree
watki to te w {}
