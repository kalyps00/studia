Jaki jest minimalny kwant czasu procesora w Twoim systemie operacyjnym?
cat /proc/sys/kernel/sched_rr_timeslice_ms
-procesy czasu rzeczywistego audio sterowanie czyms etc
sudo cat /sys/kernel/debug/sched/base_slice_ns
-wiekszosc procesow

W jaki sposób dzielone jest wykorzystanie karty graficznej? Z użyciem czasu (ang. time sharing) czy z
użyciem przestrzeni (ang. space sharing)?
obydwa sa wykorzystywane obecniew

Uruchom «top» i posortuj malejąco po wartościach kolumny VIRT. Policz sumę, dla pierwszych 5
procesów, porównaj z dostępną pamięcią RAM na Twoim komputerze, a następnie skomentuj otrzymane
rezultaty.

top -> f -> VIRT -> s -> q

jest to zarezerownwana pamiec wirtualna ktora jest znacznie wieksz aniz realna pamiec ram w komputerze
