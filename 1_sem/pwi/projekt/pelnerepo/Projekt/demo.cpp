//instrukcja kompilacji:
//g++ -std=c++17 Szyfr_RSA.c rozpoznawanie_jezyka.c regex.c podzial.c plot.c nawiasowanie.c najdluzszy_palindrom.c biblioteka.c base64.cpp arithmetic.cpp demo.cpp  -o demonstracja





#include "Szyfr_RSA.h"
#include "rozpoznawanie_jezyka.h"
#include "regex.h"
#include "podzial.h"
#include "plot.h"
#include "nawiasowanie.h"
#include "najdluzszy_palindrom.h"
//#include "biblioteka.h"
#include "base64.hpp"
#include "arithmetic.hpp"
#include <iostream>
#define MAXLENGTH 4096
#define MAX_TEXT_SIZE 1000000





void arithmetic_demo(){
	std::cout<<"Podaj nazwe pliku jaki chcesz skompresowac:\n";
	std::string nazwa; std::cin>>nazwa;

	auto input_path = std::string(nazwa);
    auto input_stream = std::ifstream(input_path);

    if (!input_stream.is_open()) {
        std::cerr << "Error: cannot open given file: " << input_path << "\n";
        return;
    }

    std::string compressed_path = input_path + ".comp";
    std::string decompressed_path = input_path + ".decomp";

    std::cout << "Compressing to '" << compressed_path << "' ...";
    bitio::bit_ofstream compressed_stream(compressed_path);
    arithmetic::compress(input_stream, compressed_stream);
    std::cout << " Done." << std::endl;

    std::cout << "Decompressing to '" << decompressed_path << "' ...";
    bitio::bit_ifstream input_stream2(compressed_path);
    auto decompressed_stream = std::ofstream(decompressed_path);
    arithmetic::decompress(input_stream2, decompressed_stream);
    std::cout << " Done." << std::endl;
    return;
}

void base64_demo(){
	std::cout<<"Podaj nazwe algorytmu jaki chcesz uzyc:\n";
	std::cout<<"Do wyboru 1421, 2045, 2152, 3501, 4648_4, 4648_5, 4880\n";
	std::string alg; std::cin>>alg;
	auto encoder = base64::encode4648_4;
    auto decoder = base64::decode4648_4;

    auto algorithm = alg;
    if (algorithm == "1421") {
        encoder = base64::encode1421;
        decoder = base64::decode1421;
    } else if (algorithm == "2045") {
        encoder = base64::encode2045;
        decoder = base64::decode2045;
    } else if (algorithm == "2152") {
        encoder = base64::encode2152;
        decoder = base64::decode2152;
    } else if (algorithm == "3501") {
        encoder = base64::encode3501;
        decoder = base64::decode3501;
    } else if (algorithm == "4648_4") {
        encoder = base64::encode4648_4;
        decoder = base64::decode4648_4;
    } else if (algorithm == "4648_5") {
        encoder = base64::encode4648_5;
        decoder = base64::decode4648_5;
    } else if (algorithm == "4880") {
        encoder = base64::encode4880;
        decoder = base64::decode4880;
    } else {
        std::cerr << "Wrong algorithm: " << algorithm << "\n";
        return;
    }
    

    std::string input;

    std::cout << "Enter text to be encoded:" << std::endl;
    std::cin>>input;

    std::string encoded = encoder(input);
    std::string decoded = decoder(encoded).value_or("<ERROR>");

    std::cout << "Text encoded with base64:\n" << encoded << "\n";
    std::cout << "Text decoded from base64:\n" << decoded << "\n";
}


void nawiasowanie_demo(){
	std::cout<<"Wpisz nawiasowanie skladajace się ze znakow: {}[]()\n";
	// std::cout<<"Do wyboru 1421, 2045, 2152, 3501, 4648_4, 4648_5, 4880\n";
	std::string alg; std::cin>>alg;
	char s1[MAXLENGTH];
	for(int i = 0; i < alg.size(); i++) s1[i] = alg[i];
	printf("%s\n", check(s1) ? "Poprawne" : "Niepoprawne");
	
}

void regex_demo(){
	std::cout<<"Test wyrazen regularnych:\n";
    char *expr[] = {strdup("a*b"), strdup("a+b"), strdup("a{2,4}b"), strdup("a.c"), strdup(".*ab$"), NULL};
    char *text[] = {strdup("aab"), strdup("ab"), strdup("aaaab"), strdup("ababababb"), strdup("abababcabb"), NULL};
    for(int i = 0; expr[i] != NULL; ++i){
        printf("Testowanie: %s\n", expr[i]);
        for(int j = 0; text[j] != NULL; ++j){
            printf("    Text: %s -> ", text[j]);
            if(match(expr[i], text[j])) printf("Znaleziono\n");
            else printf("Nie znaleziono.\n");
        }
        printf("\n");
    }
}

void palindrom_demo(){
	std::string tekst;
	std::cout<<"Wpisz tekst:\n";
	std::cin>>tekst;
	char * wsk = new char[tekst.size()+1];
	strcpy(wsk, tekst.c_str());
	std::cout<<"Najdluzszy palindrom w tekscie to:\n";
	std::string rezultat(find_longest_palindrome(tekst.c_str()));
	std::cout<<rezultat<<"\n";
}

void szyfr_plotkowy_demo(){
	szyfruj();
}

void szyfr_rsa_demo(){
long seed = time(NULL);
	srand(seed);	

	//Wygeneruj klucz RSA
	key klucz = RSA();
	//Zadeklaruj obiekt c_string i wczytaj do niego tekst
	c_string* tekst = (c_string *)malloc(sizeof(c_string));  init_c_string(tekst);	
	const char * lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras suscipit eget nunc at feugiat. Nunc convallis elit id mauris fringilla ultrices. Morbi iaculis egestas orci, vitae dapibus tellus porta at. Interdum et malesuada fames ac ante ipsum primis in faucibus. Mauris tempor, purus vestibulum molestie laoreet, dolor erat tempus sapien, ut sollicitudin libero metus et odio. Sed elementum porttitor diam ac condimentum. Vestibulum finibus orci eget lacus vehicula, vitae tempor dui laoreet.";
	puts("Oto tekst ktory zostanie wkrotce zaszyfrowany:");
	printf("%s\n", lorem);
	while(*lorem != '\0'){
		push_c_string(tekst,*lorem);
		lorem++;
	}
	//zaszyfruj tekst
	c_string* zaszyfrowany_tekst = (c_string *)malloc(sizeof(c_string)); init_c_string(zaszyfrowany_tekst);
	RSA_encode(tekst,klucz.publickey,zaszyfrowany_tekst);
	
	//wypisz zaszyfrowany tekst na ekran
	puts("Oto zaszyfrowany tekst:");
	print_c_string(zaszyfrowany_tekst);


	//wypisz klucz prywatny w miare przyjaznej do skopiowania postaci
	c_string* prywatny_klucz_d = (c_string *)malloc(sizeof(c_string)); init_c_string(prywatny_klucz_d);
	print_hex(klucz.privatekey.d, prywatny_klucz_d);
	c_string* prywatny_klucz_n = (c_string *)malloc(sizeof(c_string)); init_c_string(prywatny_klucz_n);
	print_hex(klucz.privatekey.n, prywatny_klucz_n);
	puts("Oto klucz prywatny:");
	print_c_string(prywatny_klucz_d);
	puts("Oto modulo:");
	print_c_string(prywatny_klucz_n);

	//nie zapomnij zwolnic zaalokowanej pamieci c_stringow!!! uzyj do tego funkcji free_c_string
	free_c_string(tekst); 
	free_c_string(zaszyfrowany_tekst);
	free_c_string(prywatny_klucz_d);
	free_c_string(prywatny_klucz_n);

	//wypisz linijke przerwy na ekran
	puts("");
	//jesli uzytkownik wklei teraz wynik dzialania czesci szyfrujacej - czyli
	//kolejno: zaszyfrowany_tekst, prywatny_klucz_d, prywatny_klucz_n
	//to program odszyfruje z ich pomoca tekst
	puts("Wklej prosze zaszyfrowany tekst do odkodowania (z tej lub innej instancji programu):");
	read_c_string(zaszyfrowany_tekst);
	puts("A teraz klucz prywatny:");
	read_c_string(prywatny_klucz_d);
	puts("A teraz modulo:");
	read_c_string(prywatny_klucz_n);

	klucz.privatekey.d = read_hex(prywatny_klucz_d);
	klucz.privatekey.n = read_hex(prywatny_klucz_n);
	RSA_decode(zaszyfrowany_tekst,klucz.privatekey,tekst);
	puts("Oto odkodowany tekst:");
	print_c_string(tekst);
	
	free_c_string(tekst); 
	free_c_string(zaszyfrowany_tekst);
	free_c_string(prywatny_klucz_d);
	free_c_string(prywatny_klucz_n);

	//jeszcze trzeba zwolnic pamiec samych c_stringow
	free(tekst);
	free(zaszyfrowany_tekst);
	free(prywatny_klucz_d);
	free(prywatny_klucz_n);
}

void podzial_demo(){
	const char *plik_slownika = "polski.txt";
    int rozmiar_slownika;
    char **slownik = wczytaj_slownik(plik_slownika, &rozmiar_slownika);
    if (!slownik) {
        printf("Blad wczytywania slownika z pliku: %s\n", plik_slownika);
        return;
    }

    const char *tekst = "starymłynstałnaskrajuwioski.Oddawnanikttamniemieszkał.Pewnegodniadrzwiotworzyłsilnywiatr.Wśrodkuchłopiecznalazłdziwnąksięgę.Odtegodniamłynznowupracował.";
    int liczba_zdan;
    char **zdania = podziel_na_zdania(tekst, &liczba_zdan);
    if (!zdania) {
        printf("\nBlad podczas dzielenia tekstu na zdania.\n");
        zwolnij(slownik, rozmiar_slownika);
        return;
    }

    char *wynik = NULL;
    polacz_wyniki_do_ciagu(zdania, liczba_zdan, &wynik, slownik, rozmiar_slownika);

    // Wyświetlenie wynikowego podzielonego tekstu
    printf("\nPodzielony tekst:\n%s\n", wynik);

    // Sprawdzanie gramatyki na wynikowym tekście
    printf("\nSprawdzanie gramatyki:\n");
    sprawdz_gramatyke(wynik);

    free(wynik);
    zwolnij(zdania, liczba_zdan);
    zwolnij(slownik, rozmiar_slownika);

}


void rozpoznawanie_jezyka_demo(){
	std::string tekst;
	std::cout<<"Wpisz tekst w jakims jezyku: (bez liter specjalnych):\n";
	std::cin>>tekst;
	char * wsk = new char[tekst.size()+1];
	strcpy(wsk, tekst.c_str());
	std::string rezultat(detect_language(wsk)); 
	std::cout<<"Prawdopodnie jest to: "<<rezultat<<"\n";

}

void statystyki_demo(){


    char text[MAX_TEXT_SIZE] = {0};
    std::string nazwa;
    std::cout<<"Wpisz nazwe pliku:\n";
    std::cin>>nazwa;
    
        FILE *file = fopen(nazwa.c_str(), "r");
        if (!file) {
            //perror("Nie mozna otworzyć pliku");
           
            std::cerr<<"Nie mozna otworzyc pliku\n";
            return;
        }
        else {
            fread(text, sizeof(char), MAX_TEXT_SIZE, file);
            fclose(file);
        }
    
    
   

    TextStats stats;
    statystyki(text, &stats);

    ignorowanie_wielkosci_liter(text, "Milac");
    wypisanie_statystyk_liter(stats);
    puts("Podmienienie 'mogla' na 'liczba' w tekscie");
    podmiana_wzorca(text, "mogla", "liczba", text);
    printf("%s\n", text);
    puts("Zliczanie dwukropkow");
    printf("%i\n", zliczanie_wzorca(text, ":"));
    puts("Wyszukiwanie wzorca: 'Milac'");
    wyszukiwanie_wzorca(text, "Milac");
   // ignorowanie_wielkosci_liter(text, "jestem");





}




int main(int argc, char *argv[]){
	const std::string usage =
        "usage: " + std::string(argv[0]) + " <COMMAND>\n"
        "COMMANDS:\n"
        "\tarithmetic\n"
        "\tbase64\n"
        "\tnawiasowanie\n"
        "\tregex\n"
	    "\trozpoznawanie_jezyka\n"
        "\tpalindrom\n"
        "\tpodzial\n"
        "\tstatystyki\n"
        "\tszyfr_plotkowy\n"
        "\tszyfr_rsa\n";

    if (argc <= 1) {
        std::cerr << usage << std::endl;
        return 0;
    }
    std::string command = std::string(argv[1]);
   
    	if(command == "arithmetic"){
    		arithmetic_demo();
    		}else
    	if(command == "base64"){
    		base64_demo();
    		}else
    	if(command == "nawiasowanie"){
    		nawiasowanie_demo();
    		}else
    	if(command == "regex"){
    		regex_demo();
    		}else
    	if(command == "palindrom"){
    		palindrom_demo();
    		}else
    	if(command == "podzial"){
    		podzial_demo();
    		}else
    	if(command == "statystyki"){
    		statystyki_demo();
    		}
    	if(command == "szyfr_plotkowy"){
    		szyfr_plotkowy_demo();
    		}else
	if(command == "rozpoznawanie_jezyka"){
    		rozpoznawanie_jezyka_demo();
		}else
    	if(command == "szyfr_rsa"){
    		szyfr_rsa_demo();
    		}else{
    	
    		std::cerr << usage << std::endl;
        	return 1;
    		}

    






	return 0;
}
