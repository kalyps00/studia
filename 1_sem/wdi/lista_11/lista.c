#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node *pnode;
typedef struct node
{
    int val;
    pnode left;
    pnode right;
} snode;

pnode utworz(int wart)
{
    pnode pom = (pnode)malloc(sizeof(snode));
    pom->left = NULL;
    pom->right = NULL;
    pom->val = wart;
    return pom;
}

// Zadanie 1: Kolejność wstawiania dla maksymalnej i minimalnej wysokości drzewa BST
// Maksymalna wysokość: 1, 2, 3, 4, 5, 6, 7 (rosnąco)
// Minimalna wysokość: 4, 2, 6, 1, 3, 5, 7 (tworzy zbalansowane drzewo)

// Zadanie 2: Liczba elementów w drzewie
int liczbaElementow(pnode t)
{
    if (t == NULL)
        return 0;
    return 1 + liczbaElementow(t->left) + liczbaElementow(t->right);
}

// Zadanie 3: Wysokość drzewa
int wysokosc(pnode t)
{
    if (t == NULL)
        return 0;
    int lewa = wysokosc(t->left);
    int prawa = wysokosc(t->right);
    return 1 + (lewa > prawa ? lewa : prawa);
}

// Zadanie 4: Wypisanie elementów dodatnich w porządku niemalejącym
void wypiszDodatnie(pnode t)
{
    if (t == NULL)
        return;
    wypiszDodatnie(t->left);
    if (t->val > 0)
        printf("%d ", t->val);
    wypiszDodatnie(t->right);
}

// Zadanie 5: Sprawdzenie, czy drzewo jest BST //sprawdz
// zle ma byc sprawdzenie czy wieksze od wszytkich/mniejsze
// INT_MIN, INT_MAX
int czyBST(pnode t, int min, int max)
{
    if (t == NULL)
        return 1;
    if (t->val < min || t->val > max)
        return 0;
    return czyBST(t->left, min, t->val) && czyBST(t->right, t->val, max);
}

// Zadanie 6: Łączenie dwóch drzew BST
pnode polaczBST(pnode t1, pnode t2)
{
    if (t1 == NULL)
        return t2;
    if (t2 == NULL)
        return t1;

    pnode max1 = t1;
    while (max1->right != NULL)
        max1 = max1->right;

    max1->right = t2;
    return t1;
}

// Zadanie 7: Wstawianie elementu do BST bez rekurencji
pnode wstawBST(pnode root, int wart)
{
    pnode nowy = utworz(wart);
    if (root == NULL)
        return nowy;

    pnode parent = NULL, temp = root;
    while (temp != NULL)
    {
        parent = temp;
        if (wart < temp->val)
        {
            temp = temp->left;
            if (temp != NULL && temp->val < wart)
                break;
        }
        else if (wart > temp->val)
        {
            temp = temp->right;
            if (temp != NULL && temp->val > wart)
                break;
        }
    }
    // parent nad i temp pod miejsce do wstawienia
    if (wart < parent->val)
    {
        nowy->left = parent->left;
        parent->left = nowy;
    }
    else
    {
        nowy->right = parent->right;
        parent->right = nowy;
    }

    return root;
}
// Zadanie 8: Rotacja, gdy v jest lewym dzieckiem u
pnode rotacjaLewo(pnode u)
{
    pnode newroot = u->left;
    u->left = newroot->right;
    newroot->right = u;
    return newroot;
}
void usun(pnode root, int val)
{
    pnode temp = root;
    pnode parent = NULL;
    while (temp->val != val && temp != NULL)
    {
        if (val < temp->val)
        {
            parent = temp;
            temp = temp->left;
        }
        else if (val > temp->val)
        {
            parent = temp;
            temp = temp->right;
        }
        else
        {
        }
    }
    if (parent == NULL)
        ;
}
// Funkcja pomocnicza do testowania
void wypisz(pnode t)
{
    if (t == NULL)
        return;
    wypisz(t->left);
    printf("%d ", t->val);
    wypisz(t->right);
}

int main()
{
    pnode drzewo = NULL;
    drzewo = wstawBST(drzewo, 4);
    drzewo = wstawBST(drzewo, 2);
    drzewo = wstawBST(drzewo, 6);
    drzewo = wstawBST(drzewo, 1);
    drzewo = wstawBST(drzewo, 3);
    drzewo = wstawBST(drzewo, 5);
    drzewo = wstawBST(drzewo, 7);

    printf("Elementy drzewa BST: ");
    wypisz(drzewo);
    printf("\n");

    printf("Liczba elementów: %d\n", liczbaElementow(drzewo));
    printf("Wysokość drzewa: %d\n", wysokosc(drzewo));

    printf("Elementy dodatnie: ");
    wypiszDodatnie(drzewo);
    printf("\n");

    return 0;
}
