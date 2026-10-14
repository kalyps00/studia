time find /usr >/dev/null 2>&1
(a) nie jest równa real
bo czekamy np na I/O sprzętu np dysku w tym wypadku lub np proces moze czekac na wykonanie na rzecz innego procesu przez jakis czaswtedy real czas rosnie a zaden pozostalych sie nie zmienia
(b) może być większa od real?
tak np gdy program ejst wielowatkowy i wtedy suma jest po rspotu wieksza bo praca byla jednoczesnie na kilku watkach

(ulimit -t 1; find /usr / >/dev/null 2>&1; echo "$?")
dostajemy kod wysjcia 137 czyli 137-128=9 czyli
SIGKILL czyli bezwarunkowo i bez mzoliwsoci przechwycenia ubija proces
