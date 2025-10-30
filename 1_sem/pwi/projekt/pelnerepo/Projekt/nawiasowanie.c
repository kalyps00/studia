#include <stdio.h>
#include <string.h>
#include "nawiasowanie.h"
 
enum {FALSE, TRUE};
 
#define MAXLENGTH 4096
#define COMMENT 1
#define REPLACEMENT ' '
#define INCOMMENT 1
#define OUTOFCOMMENT 0
 
int checkMatch(char c1, char c2){
    if(c1 == '(' && c2 == ')') return TRUE;
    if(c1 == '[' && c2 == ']') return TRUE;
    if(c1 == '{' && c2 == '}') return TRUE;
    return FALSE;
}
 
int check(char s[]) {
    int head = -1;
    char stack[MAXLENGTH];
    for(int i = 0; i < strlen(s); ++i) {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack[++head] = s[i];
        }else if(s[i] == ')' || s[i] == ']' || s[i] == '}') {
            if(head < 0 || !checkMatch(stack[head], s[i])) {
                return 0;
            }
            --head;
        }else {
            continue;
        }
    }
    return head == -1;
}
 
 
void removecomments(char code[], char replacewith){
    int commentstart, state;
    commentstart = 0;
    state = OUTOFCOMMENT;
    int length = strlen(code);
    for(int i = 0; i < length; i++){
        if(code[i] == '/' && state == OUTOFCOMMENT && i + 1 < length){
            if(code[++i] == '*'){
                commentstart = i - 1;
                state = INCOMMENT;
            }
        }
        if(code[i] == '*' && state == INCOMMENT && i + 1 < length){
            if(code[++i] == '/'){
                for(int j = commentstart; j <= i; j++){
                    code[j] = replacewith;
                }
                state = OUTOFCOMMENT;
            }
        }
    }
}
