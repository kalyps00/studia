Wzory na podstawie pól superbloku:

- Rozmiar bloku (w bajtach): 1024 << s_log_block_size = 1024 \* 2^(s_log_block_size)

- Liczba i-węzłów w grupie bloków: bezpośrednio pole s_inodes_per_group.

- Liczba bloków w grupie bloków: bezpośrednio pole s_blocks_per_group

- Liczba grup bloków (N_groups): sufit z (s_blocks_count / s_blocks_per_group). bo nawet niepełna końcówka bloków mieć grupę.

- Liczba wpisów tablicy deskryptorów grup bloków (GDT): równa liczbie grup bloków, czyli sufit z (s_blocks_count / s_blocks_per_group). Każda grupa ma dokładnie jeden 32-bajtowy wpis w tej tablicy, więc liczba wpisów to po prostu liczba grup.

Składowe grupy bloków i ich rozmiar w blokach:

- Superblok - 1 blok (ma stały rozmiar 1024 B). Trzyma globalne parametry całego systemu plików. Występuje w grupie 0 (od offsetu 1024 B od początku partycji) oraz jako kopia w wybranych grupach.

Tablica deskryptorów grup bloków (GDT) - każda grupa ma tu jeden 32-bajtowy wpis z adresami swoich bitmap i tablicy i-węzłów, więc całość zajmuje sufit z (N_groups \* 32 / rozmiar_bloku) bloków.

- Bitmapa bloków - 1 blok. Ciąg bitów dla tej konkretnej grupy, gdzie każdy bit informuje, czy dany blok jest wolny (0), czy zajęty (1).

- Bitmapa i-węzłów - 1 blok. Działa tak samo jak wyżej, tylko każdy bit oznacza stan jednego i-węzła w tej grupie (0 wolny, 1 zajęty).

- Tablica i-węzłów - sufit z ((s_inodes_per_group \* s_inode_size) / rozmiar_bloku) bloków. Zbiór metryczek plików i katalogów. Rozmiar pojedynczego i-węzła określa pole s_inode_size (domyślnie 128 B).

- Bloki danych - wszystkie pozostałe bloki w grupie. Przechowują właściwą zawartość plików, katalogów oraz bloki pośrednie.

Kopie zapasowe superbloku i tablicy deskryptorów grup bloków:

- Kopie nie są trzymane w każdej grupie, żeby nie marnować miejsca. Trafiają wyłącznie do grupy 1 oraz grup o numerach będących potęgami liczb 3, 5 i 7.
