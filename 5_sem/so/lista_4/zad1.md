### 1. Rodzaje sterowników w Linuksie

1. Sterowniki urządzeń znakowych (Character devices)
   - Dostęp do nich przypomina dostęp do pliku - przesyłają dane jako ciągły strumień bajtów (odczyt i zapis sekwencyjny). Nie pozwalają na swobodne przechodzenie do dowolnego miejsca danych.
   - Przykłady: klawiatury, myszki i urządzenia wirtualne jak /dev/null.

2. Sterowniki urządzeń blokowych (Block devices)
   - Przesyłają dane w określonych blokach (np. 512 B lub 4 KB). Każdy blok ma swój adres, więc system może od razu odwołać się do wybranego fragmentu bez czytania wcześniejszych danych. Dzięki temu na takich urządzeniach można tworzyć systemy plików.
   - Przykłady: dyski twarde (HDD/SSD), pendrive'y i karty SD.

3. Sterowniki interfejsów sieciowych (Network interfaces)
   - Nie są to urządzenia znakowe, tylko osobna kategoria. Służą do wysyłania i odbierania pakietów danych. Komunikacja z nimi odbywa się przez gniazda sieciowe (sockets), a nie przez wywołania systemowe `read/write`. Interfejsy sieciowe nie mają też plików urządzeń w katalogu `/dev/`.
   - Przykłady: karty sieciowe (Ethernet), adaptery Wi-Fi i interfejs loopback (`lo`).

### 2. Rozpoznawanie urządzeń poleceniem `ls`

Aby sprawdzić typ urządzenia, można użyć polecenia `ls -l /dev/`. Pierwsza litera w kolumnie uprawnień informuje o jego typie:

- `c` - urządzenie znakowe (np. `crw-rw-rw-`)
- `b` - urządzenie blokowe (np. `brw-rw----`)
  (Urządzeń sieciowych nie znajdziemy w tym katalogu, bo nie mają węzłów w `/dev/`.)

### 3. Dlaczego we FreeBSD usunięto urządzenia blokowe?

W tradycyjnym systemie UNIX każdy dysk miał dwa interfejsy (dwa pliki w `/dev`):

- blokowy (korzystający z buforów i cache'u jądra)
- znakowy, nazywany też surowym albo raw (bezpośredni zapis i odczyt z pominięciem cache'u).

Dwie drogi dostępu do tych samych danych powodowały problem z niespójnością pamięci podręcznej (cache aliasing). Jeśli proces modyfikował dane przez interfejs raw, zmiany nie pojawiały się w buforach interfejsu blokowego. Mogło to prowadzić do uszkodzenia danych na dysku. Zamiast komplikować jądro synchronizacją obu ścieżek, twórcy FreeBSD usunęli interfejs blokowy z przestrzeni użytkownika. Urządzenia pamięci masowej są teraz widoczne wyłącznie jako urządzenia znakowe, a pod spodem działa jeden spójny mechanizm obsługi żądań GEOM.
