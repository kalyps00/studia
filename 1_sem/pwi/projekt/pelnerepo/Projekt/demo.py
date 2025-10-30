from pyton import *
lib = get_all_libs()
#arithmetic


with open("a.txt", "w", encoding="utf-8") as file:
    file.write("lubie placki ziemniaczane")
lib['arithmetic'].c_compress(b'a.txt',b'b.txt')
lib['arithmetic'].c_decompress(b'b.txt',b'a.txt')


#base64
lib['base64']

print(lib['base64'].c_encode1421(b'lubie placki').decode('utf-8'))
print(lib['base64'].c_decode1421(lib['base64'].c_encode1421(b'lubie placki')).decode('utf-8'))



#biblioteka

statystyki = TextStats()
lib['biblioteka'].statystyki(b'lubie placki',statystyki)
lib['biblioteka'].wypisanie_statystyk_liter(statystyki)
print(lib['biblioteka'].zliczanie_wzorca(b'lubie placki bardzo lubie',b'lub'))
buffer_size = 50
char_pointer = ctypes.create_string_buffer(buffer_size)
lib['biblioteka'].podmiana_wzorca(b'amogus',b'am',b'ma',char_pointer)
print(char_pointer.value.decode('utf-8'))


#nawiasowanie

lib['nawiasowanie'].check(b'[[]{[[()]]}]{()}')
komentarz = s=b'/*    */'
lib['nawiasowanie'].removecomments(komentarz,b'#')
print(komentarz)

#palindrom

print(lib['palindrom'].find_longest_palindrome(b'shshjsjjhskobylamamalybokwiiuuwiiuwui').decode('utf8'))

#plot
lib['plot'].szyfruj()


#podzial
lib['podzial'].sprawdz_gramatyke(b'Malpka je banana')
lib['podzial'].sprawdz_gramatyke(b'malpka je banana')
'''
const char *tekst = "starymłynstałnaskrajuwioski.Oddawnanikttamniemieszkał.Pewnegodniadrzwiotworzyłsilnywiatr.Wśrodkuchłopiecznalazłdziwnąksięgę.Odtegodniamłynznowupracował.";
    int liczba_zdan;
    char **zdania = podziel_na_zdania(tekst, &liczba_zdan);
    if (!zdania) {
        printf("\nBlad podczas dzielenia tekstu na zdania.\n");
        zwolnij(slownik, rozmiar_slownika);
        return 1;
    }

    char *wynik = NULL;
    polacz_wyniki_do_ciagu(zdania, liczba_zdan, &wynik, slownik, rozmiar_slownika);
'''
rozmiar_slownika = ctypes.c_int()
slownik = lib['podzial'].wczytaj_slownik(b'polski.txt',ctypes.byref(rozmiar_slownika))
tekst = b'Staryjestnaskrajuwioski.Pewnegodniadrzwisilnywiatr'
liczba_zdan = ctypes.c_int()
zdania = lib['podzial'].podziel_na_zdania(tekst,ctypes.byref(liczba_zdan))
wynik = ctypes.c_char_p()
lib['podzial'].polacz_wyniki_do_ciagu(zdania,liczba_zdan,ctypes.byref(wynik),slownik,rozmiar_slownika)
print(wynik.value.decode('utf-8'))

#regex

print(lib['regex'].match(b'a.c',b'abbabababbca'))
print(lib['regex'].match(b'a.*.b{2}',b'abbabababba'))


#rozpoznawanie_jezyka

print(lib['rozpoznawanie_jezyka'].detect_language(b'i like to play with toys').decode('utf-8'))
print(lib['rozpoznawanie_jezyka'].detect_language(b'lubie bawic sie zabawkami').decode('utf-8'))
print(lib['rozpoznawanie_jezyka'].detect_language(b'ich spiele gerne mit spielzeug').decode('utf-8'))
print(lib['rozpoznawanie_jezyka'].detect_language(b'Jaime jouer avec des jouets').decode('utf-8'))


#szyfr_rsa

klucz = lib['szyfr_rsa'].RSA()
tekst = c_string()
lib['szyfr_rsa'].init_c_string(ctypes.byref(tekst))
tmp = [lib['szyfr_rsa'].push_c_string(ctypes.byref(tekst),x.encode('utf-8')) for x in "Lorem ipsum"]
zaszyfrowany_tekst = c_string()
lib['szyfr_rsa'].RSA_encode(ctypes.byref(tekst),klucz.publickey,ctypes.byref(zaszyfrowany_tekst))
lib['szyfr_rsa'].free_c_string(ctypes.byref(tekst))
lib['szyfr_rsa'].RSA_decode(ctypes.byref(zaszyfrowany_tekst),klucz.privatekey,ctypes.byref(tekst))
print(tekst.wsk.decode('utf-8'))
lib['szyfr_rsa'].free_c_string(ctypes.byref(zaszyfrowany_tekst))
lib['szyfr_rsa'].free_c_string(ctypes.byref(tekst))





