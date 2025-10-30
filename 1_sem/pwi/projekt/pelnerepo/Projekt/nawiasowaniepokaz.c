#include <stdio.h>
#include "nawiasowanie.h"
 
#define MAXLENGTH 4096
 
int main(){
    char s1[MAXLENGTH];
    scanf("%s", s1);
    printf("%s\n", check(s1) ? "Poprawne" : "Niepoprawne");
    return 0;
}
