Punkt montażowy (np. katalog /proc albo /tmp) to zawsze zwykły katalog w drzewie systemu plików

Wydruk mount (na przykładzie /dev/sda4 on / type ext4 (rw,relatime)) ma następujące kolumny:

- Źródło (/dev/sda4, tmpfs, none) - partycja dyskowa, plik obrazu lub umowna nazwa systemu wirtualnego.
- Punkt montażowy (/, /proc, /tmp) - ścieżka katalogu, pod którą system jest widoczny.
- Typ systemu plików (ext4, squashfs, proc, tmpfs) - nazwa sterownika w jądrze.
- Opcje (rw, ro, nosuid, nodev, noexec, relatime) - flagi trybu dostępu.

Punkty montażowe pseudo systemów plików to wszystkie wpisy poza / (ext4) i /snap/\* (squashfs):

- Interfejsy jądra i sprzętu: /proc (proc), /sys (sysfs), /dev (devtmpfs), /dev/pts (devpts), /sys/fs/cgroup (cgroup2), /sys/firmware/efi/efivars (efivarfs), /sys/kernel/security (securityfs), /sys/fs/bpf (bpf), /sys/kernel/tracing (tracefs), /sys/kernel/debug (debugfs), /sys/kernel/config (configfs), /sys/fs/pstore (pstore), /sys/fs/fuse/connections (fusectl), /proc/sys/fs/binfmt_misc (autofs).
- Systemy w pamięci RAM: /run, /dev/shm, /tmp, /run/credentials/... (tmpfs), /dev/hugepages (hugetlbfs), /dev/mqueue (mqueue).

Atrybuty montowania z man 8 mount:

- relatime - aktualizuje czas dostępu (atime) tylko gdy atime <= mtime lub ctime, albo minęły 24 godziny. Ogranicza zbędne zapisy przy odczycie.
- noexec - blokuje bezpośrednie uruchamianie programów i skryptów (execve zwraca EACCES). Nadal można odpalić skrypt przez interpreter (np. bash skrypt.sh).
- nodev - ignoruje pliki specjalne urządzeń (blokowe i znakowe) w tym systemie plików.

Scenariusz użycia (przenośny dysk USB):

- nodev uniemożliwia użycie spreparowanego na innym komputerze pliku urządzenia (np. dającego dostęp do surowego dysku /dev/sda4).
- noexec chroni przed przypadkowym lub złośliwym uruchomieniem nieznanych plików wykonywalnych z pendrive'a.
- relatime zmniejsza liczbę zapisów eliminujac zapisy atime przy odczytcie ograniczajac je jedynie do zapisow.
