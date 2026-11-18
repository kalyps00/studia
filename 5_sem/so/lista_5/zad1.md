trace -o pipeline.log -f dash -c 'ps -ef | grep sh | wc -l > cnt'

13469 – powłoka dash
13470 – ps -ef
13471 – grep sh
13472 – wc -l  
pipeline.log
+ 3

pierwszy pipe dla ps -ef :
13469 pipe2([3, 4], 0) - 3 to koniec do odczytu a 4 do zapisu
pozniej clone -> 13470
13469 close(4 <unfinished ...> - zamykamy 4 (bo powloka nie bedzie nic zapisywac, zostawia 3 dla grepa)
13470 close(3 <unfinished ...> - potem proces potomny zamyka 3 czyli koniec do odczytu
13470 dup2(4, 1 <unfinished ...> - przekierowujemy standardowe wyjscie na 4
13470 close(4 <unfinished ...> - zamykamy 4
13470 execve("/usr/bin/ps", ["ps", "-ef"], ...) - odpala sie ps  
pipeline.log
+ 4

drugi pipe dla grep sh :
13469 pipe2([4, 5], 0) - powloka tworzy drugiego pipe'a (4 bylo wolne wiec dostaje je jako odczyt, 5 to zapis)
pozniej clone -> 13471
13469 close(3 <unfinished ...> - powloka zamyka 3 (odczyt z pierwszego pipe'a, juz przekazane do grepa)
13469 close(5 <unfinished ...> - powloka zamyka 5 (zapis do drugiego pipe'a, zostawia tylko 4 dla wc)
13471 close(4 <unfinished ...> - grep zamyka 4 (odczyt z drugiego pipe'a, nie potrzebuje go)
13471 dup2(3, 0 <unfinished ...> - przekierowuje standardowe wejscie na 3 (czyta z pierwszego pipe'a)
13471 close(3 <unfinished ...> - zamyka 3
13471 dup2(5, 1 <unfinished ...> - przekierowuje standardowe wyjscie na 5 (pisze do drugiego pipe'a)
13471 close(5 <unfinished ...> - zamyka 5
13471 execve("/usr/bin/grep", ["grep", "sh"], ...) - odpala sie grep  
pipeline.log
+ 4

ostatni proces wc -l i przekierowanie do pliku cnt :
nie robimy juz pipe2 bo to ostatnie polecenie
pozniej clone -> 13472
13469 close(4 <unfinished ...> - powloka zamyka ostatni otwarty koniec pipe'a (4)
13469 wait4(-1 <unfinished ...> - powloka czeka na zakonczenie dzieci
13472 dup2(4, 0 <unfinished ...> - wc przekierowuje standardowe wejscie na 4 (czyta z drugiego pipe'a)
13472 close(4 <unfinished ...> - zamyka 4
13472 openat(AT_FDCWD, "cnt", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3 - otwiera/tworzy plik cnt pod deskryptorem 3
13472 dup2(3, 1 <unfinished ...> - przekierowuje standardowe wyjscie na 3 (czyli na plik cnt)
13472 close(3 <unfinished ...> - zamyka 3
13472 execve("/usr/bin/wc", ["wc", "-l"], ...) - odpala sie wc
