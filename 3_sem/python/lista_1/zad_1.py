import decimal
from decimal import Decimal
def vat_faktura(lista):
   return sum(lista) * 0.23

def vat_paragon(lista):
    suma = 0
    for i in lista:
        suma+= i *0.23
    return suma
zakupy = [0.11, 0.33]
print(vat_faktura(zakupy) == vat_paragon(zakupy))
#
zakupyd = [Decimal("0.11") , Decimal("0.33")]

def vat_faktura_d(lista):
   return sum(lista) * Decimal("0.23")

def vat_paragon_d(lista):
    suma = 0
    for i in lista:
        suma+= i *Decimal("0.23")
    return suma

print(vat_faktura_d(zakupyd) == vat_paragon_d(zakupyd))