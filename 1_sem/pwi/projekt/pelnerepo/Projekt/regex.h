int match(char *text, char * expr);
int reg_ast(char c,  char *text,  char *expr);
int reg_pl(char c,  char *text,  char *expr);
int reg_br(char c, int m, int n,  char *pattern,  char *text);
int is_dgt(char c);
int parse_dgt( char **pattern);
void reverse(char * s);
void int_str(int n, char * s);
int match_pos( char *text,  char * expr);
