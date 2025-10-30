#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tree_node
{
    struct tree_node **children; // n
    int column;
    int free_space; // -1 -free else is attacked by which column
};
typedef struct tree_node Tree_node;
void print_tree(Tree_node **node, int n, int depth, char *format)
{
    if (node == NULL || depth >= n)
        return;

    for (int i = 0; i < n; i++)
    {
        if (node[i] == NULL)
            continue;
        if (node[i]->free_space != -1)
        {
            printf("%s+-- Kolumna %d wiersz %d jest atakowany przez hetmana z kolumny %d\n",
                   format, node[i]->column, i, node[i]->free_space);
        }
        else
        {

            if (depth == n - 1)
            {
                printf("%s+-- Kolumna %d wiersz %d nie jest atakowany, stawiamy hetmana - SUKCES!\n",
                       format, node[i]->column, i);
                continue;
            }
            printf("%s+-\\ Kolumna %d wiersz %d nie jest atakowany, stawiamy hetmana\n",
                   format, node[i]->column, i);
            format[2 * depth] = '|';
            format[2 * depth + 1] = ' ';
            format[2 * depth + 2] = '\0';
            if (i == n - 1)
            {
                format[2 * depth] = ' ';
                format[2 * depth + 1] = ' ';
                format[2 * depth + 2] = '\0';
            }
            print_tree(node[i]->children, n, depth + 1, format);
            format[depth * 2] = '\0';
        }

        // Zwolnienie pamięci
        free(node[i]->children);
        free(node[i]);
    }
}

void add_node(Tree_node *parent, int n, int column)
{
    parent->children = (Tree_node **)malloc(sizeof(Tree_node *) * n);
    for (int i = 0; i < n; i++)
    {
        parent->children[i] = (Tree_node *)malloc(sizeof(Tree_node));
        parent->children[i]->column = column;
        parent->children[i]->free_space = -1;
        parent->children[i]->children = NULL;
    }
}
int is_safe(char **board, int row, int column, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (board[row][i] == 'Q')
            return i;
    }
    // Check left diagonal
    for (int i = row, j = column; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 'Q')
            return j;
    }

    // Check right diagonal
    for (int i = row, j = column; i < n && j >= 0; i++, j--)
    {
        if (board[i][j] == 'Q')
            return j;
    }
    return -1;
}
void solve(Tree_node **node, int n, char **board, int column)
{
    if (column >= n)
        return;
    for (int i = 0; i < n; i++)
    {
        int issafe = is_safe(board, i, column, n);
        if (issafe == -1)
        {
            board[i][column] = 'Q';
            node[i]->free_space = -1;
            add_node(node[i], n, column + 1);
            solve(node[i]->children, n, board, column + 1);
            board[i][column] = '.';
        }
        else
        {
            node[i]->free_space = issafe;
        }
    }
}
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Nie podano rozmiaru planszy jako argument\n");
        return 1;
    }
    for (int i = 0; i < (int)strlen(argv[1]); i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("Podano nieprawidłowy argument\n");
            return 1;
        }
    }
    int n = atoi(argv[1]);
    char **board = (char **)malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
    {
        board[i] = (char *)malloc(sizeof(char) * n);
        memset(board[i], '.', n);
    }
    Tree_node **root = (Tree_node **)malloc(sizeof(Tree_node *) * n);
    for (int i = 0; i < n; i++)
    {
        root[i] = (Tree_node *)malloc(sizeof(Tree_node));
        root[i]->column = 0;
        root[i]->free_space = -1;
        root[i]->children = NULL;
    }

    solve(root, n, board, 0);
    for (int i = 0; i < n; i++)
    {
        free(board[i]);
    }
    free(board);

    char *format = (char *)malloc(sizeof(char) * (n - 1) * 2);
    format[0] = '\0';
    print_tree(root, n, 0, format);
    free(root);
    free(format);
}
