def kompresja(tekst):
    tekst = tekst.split()
    wynik = []
    for slowo in tekst:
        last = slowo[0]
        count = 0
        for litera in slowo:
            if litera != last:
                wynik.append((last, count))
                last = litera
                count = 1
            else:
                count += 1
        wynik.append((last, count))
        wynik.append((" ", 1))
    return wynik


def dekompresja(lista):
    tekst = ""
    for litera, ilosc in lista:
        tekst += litera * ilosc
    return tekst


print(dekompresja(kompresja("suuuuper zdanie aaaa")))
