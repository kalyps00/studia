#include "biblioteka.h"

typedef struct language_profile
{
    char name[4];       // Skrót nazwy języka, np. "GER", "POL"
    double letters[26]; // Częstotliwości liter a-z
} LanguageProfile;

typedef const struct language_base
{
    LanguageProfile German;
    LanguageProfile French;
    LanguageProfile Polish;
    LanguageProfile Finnish;
    LanguageProfile Spanish;
    LanguageProfile Italian;
    LanguageProfile English;
    LanguageProfile Turkish;
    LanguageProfile Swedish;
    LanguageProfile Danish;
    LanguageProfile Icelandic;
    LanguageProfile Czech;
    LanguageProfile Hungarian;
} LanguageBase;
extern const LanguageBase LANGUAGES;
// Hardkodowane dane o częstotliwościach liter
const char *detect_language(char *text);
