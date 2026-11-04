### 1. Do czego służy `mknod` i problemy z nim związane

`mknod` to narzędzie linii poleceń (i powiązane z nim wywołanie systemowe), które służy do ręcznego tworzenia plików specjalnych (urządzeń znakowych i blokowych) poprzez bezpośrednie podanie nazwy oraz numerów major i minor.

Dlaczego to było problematyczne?
- Brak automatyzacji (hotplugging): po podłączeniu pendrive'a w trakcie pracy systemu trzeba było ręcznie utworzyć dla niego plik.
- Zaśmiecanie `/dev`: żeby system był gotowy na każdy sprzęt, podczas instalacji tworzono tysiące węzłów na zapas. Większość z nich nigdy nie była używana.
- Bezpieczeństwo: użytkownik mający dostęp do `mknod` mógłby stworzyć węzeł urządzenia wskazujący na pamięć RAM (major 1, minor 1) i próbować odczytać dane jądra z pominięciem uprawnień w `/dev`. Dlatego do tworzenia urządzeń potrzebne są uprawnienia roota.

### 2. Tworzenie plików w NetBSD

W NetBSD tworzenie plików urządzeń nadal opiera się głównie na alokacji statycznej i kilku dedykowanych narzędziach:
- `MAKEDEV`: skrypt w katalogu `/dev`, który tworzy węzły na podstawie określonych reguł.
- `majors`: plik mapujący ze stałą listą numerów głównych dla sterowników.
- `devpubd`: demon obsługujący urządzenia podłączane w trakcie pracy systemu. Nasłuchuje komunikatów z jądra, np. o podłączeniu USB, i uruchamia odpowiednią część skryptu `MAKEDEV`, żeby zaktualizować `/dev`.

### 3. Tworzenie własnego `/dev/random`

```bash
# Tworzymy węzeł urządzenia (c - character, 1 - major, 8 - minor)
sudo mknod losowe_dane c 1 8

# Nadajemy uprawnienia do odczytu, tak jak w prawdziwym /dev/random
sudo chmod 666 losowe_dane

# Testujemy działanie pobierając 16 bajtów losowych danych
head -c 16 losowe_dane | hexdump -C
```

*Wyjaśnienie:* Major `1` to identyfikator standardowego sterownika pamięci w Linuksie (mem driver). Minor `8` kieruje ten sterownik do specyficznej podfunkcji, która generuje wartości pseudolosowe, dokładnie tak samo jak oryginalny plik `/dev/random`.