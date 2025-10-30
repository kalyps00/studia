import random
import requests


def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    tekst = tekst.split()
    tekst = [str for str in tekst if len(str) < dl_slowa and str.isalpha()]
    if len(tekst) > liczba_slow:
        while len(tekst) > liczba_slow:
            tekst.pop(random.randint(0, len(tekst) - 1))
    return " ".join(tekst)


tekst = "Podział peryklinalny inicjałów wrzecionowatych \
kambium charakteryzuje się ścianą podziałową inicjowaną \
w płaszczyźnie maksymalnej."
print(uprosc_zdanie(tekst, 10, 5), "\n")

url = "https://wolnelektury.pl/media/book/txt/pan-tadeusz.txt"
response = requests.get(url)
tekst = response.text
print(uprosc_zdanie(tekst, 2, 20))
