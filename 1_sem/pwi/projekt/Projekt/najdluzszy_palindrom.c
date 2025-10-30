#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Funkcja przetwarza tekst, dodając separatory (#) pomiędzy literami
char *preprocess_text(const char *text)
{
    int n = strlen(text);
    char *processed = (char *)malloc((2 * n + 2 + 1) * sizeof(char)); // Dwa razy długość tekstu + znaki krańcowe + null
    processed[0] = '^';                                               // Znak krańcowy
    for (int i = 0; i < n; i++)
    {
        processed[2 * i + 1] = '#';
        processed[2 * i + 2] = text[i];
    }
    processed[2 * n + 1] = '#';
    processed[2 * n + 2] = '$'; // Znak krańcowy
    processed[2 * n + 3] = '\0';
    return processed;
}

// Funkcja znajdująca najdłuższy palindrom w tekście
char *find_longest_palindrome(const char *text)
{
    char *processed = preprocess_text(text);
    int n = strlen(processed);
    int *P = (int *)calloc(n, sizeof(int));
    int C = 0, R = 0; // Środek i prawe ograniczenie aktualnego palindromu
    int max_len = 0, center_index = 0;

    // Główna pętla algorytmu Manachera
    for (int i = 1; i < n - 1; i++)
    {
        int mirror = 2 * C - i; // Odbicie względem środka

        if (i < R)
        {
            P[i] = (R - i) < P[mirror] ? (R - i) : P[mirror];
        }

        // Próba rozszerzenia palindromu wokół `i`
        while (processed[i + 1 + P[i]] == processed[i - 1 - P[i]])
        {
            P[i]++;
        }

        // Aktualizacja C i R, jeśli rozszerzony palindrom wykracza poza obecne ograniczenie
        if (i + P[i] > R)
        {
            C = i;
            R = i + P[i];
        }

        // Aktualizacja najdłuższego palindromu
        if (P[i] > max_len)
        {
            max_len = P[i];
            center_index = i;
        }
    }

    // Odtwarzanie oryginalnego najdłuższego palindromu
    int start = (center_index - max_len) / 2; // Indeks w oryginalnym tekście
    char *longest_palindrome = (char *)malloc((max_len + 1) * sizeof(char));
    strncpy(longest_palindrome, text + start, max_len);
    longest_palindrome[max_len] = '\0';

    // Zwolnienie pamięci
    free(P);
    free(processed);

    return longest_palindrome;
}