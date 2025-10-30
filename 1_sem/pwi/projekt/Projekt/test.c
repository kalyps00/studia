#include "rozpoznawanie_jezyka.h"
#include <najdluzszy_palindrom.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    printf("%s", detect_language(argv[1]));
    printf("%s", n(argv[1]));

    return 0;
}
