#include "regex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {FALSE, TRUE};

int match(char *pattern, char *text);
int reg_pos(char *pattern, char *text);
int reg_ast(char c, char *pattern, char *text);
int reg_pl(char c, char *pattern, char *text);
int reg_br(char c, int m, int n, char *pattern, char *text);
int is_digit(char c);
int parse_dgt(char **pattern);

int match(char *pattern, char *text){
    do{
        if(reg_pos(pattern, text)) return TRUE;
    } while(*text++ != '\0');
    return FALSE;
}

int reg_pos(char *pattern, char *text) {
    if(pattern[0] == '\0') return TRUE;
    if(pattern[1] == '*') return reg_ast(pattern[0], pattern + 2, text);
    if(pattern[1] == '+') return reg_pl(pattern[0], pattern + 2, text);
    if(pattern[1] == '{') {
        char *p = pattern + 2;
        int m = parse_dgt(&p);
        int n = m;
        if(*p == ','){
            p++;
            if(is_digit(*p)) n = parse_dgt(&p);
            else n = -1;
        }
        if (*p == '}') return reg_br(pattern[0], m, n, p + 1, text);
    }
    if(pattern[0] == '$' && pattern[1] == '\0') return *text == '\0';
    if(*text != '\0' && (pattern[0] == '.' || pattern[0] == *text)) return reg_pos(pattern + 1, text + 1);
    return FALSE;
}

int reg_br(char c, int m, int n, char *pattern, char *text) {
    int count = 0;
    while (count < m) {
        if (*text == '\0' || (*text != c && c != '.')) return FALSE;
        text++;
        count++;
    }
    while (n == -1 || count < n) {
        if (reg_pos(pattern, text)) return TRUE;
        if (*text == '\0' || (*text != c && c != '.')) break;
        text++;
        count++;
    }
    return reg_pos(pattern, text);
}


int reg_ast(char c, char *pattern, char *text) {
    do{
        if (reg_pos(pattern, text)) return TRUE;
    } while(*text != '\0' && (*text++ == c || c == '.'));
    return FALSE;
}

int reg_pl(char c, char *pattern, char *text) {
    if(*text != '\0' && (*text == c || c == '.')) return reg_ast(c, pattern, text + 1);
    return FALSE;
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

int parse_dgt(char **pattern) {
    int num = 0;
    while (is_digit(**pattern)) {
        num = num * 10 + (**pattern - '0');
        (*pattern)++;
    }
    return num;
}
