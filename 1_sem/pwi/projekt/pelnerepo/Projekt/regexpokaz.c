#include "regex.h"
#include <stdio.h>
#include <string.h>


int main() {
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
    return 0;
}
