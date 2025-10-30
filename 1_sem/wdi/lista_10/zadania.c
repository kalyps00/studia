#include <stdio.h>
#include <stdlib.h>

struct elem
{
    int val;
    struct elem *next;
};

struct elem *utworz(int value)
{
    struct elem *new_elem = (struct elem *)malloc(sizeof(struct elem));
    new_elem->val = value;
    new_elem->next = NULL;
    return new_elem;
}
// 1
void dodajNaKoniec(struct elem *list, int value)
{
    struct elem *new_elem = utworz(value);
    if (list->next == NULL)
    {
        list->next = new_elem;
        return;
    }
    struct elem *temp = list;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_elem;
}
// 2
void usun_otatni(struct elem *list)
{
    if (list == NULL)
        return;
    struct elem *pom = list;
    if (list->next = NULL)
    {
        free(list);
        list = NULL;
    }

    while (pom->next->next != NULL)
    {
        pom = pom->next;
    }
    free(pom->next);
    pom->next = NULL;
}
// 3
void dolaczListe(struct elem *list1, struct elem *list2)
{
    if (list1 == NULL)
    {
        list1 = list2;
        return;
    }
    struct elem *temp = list1;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = list2;
}
// 4
void usunWartosc(struct elem *list, int value)
{
    struct elem *pom = list;
    if (pom == NULL)
        return;
    while (pom->next != NULL)
    { // nastepny ma dana wartosc
        while (pom->next != NULL && pom->next->val == value)
        {
            struct elem *temp = pom->next->next;
            free(pom->next);
            pom->next = temp;
            if (temp = NULL)
                break;
        }
        if (pom->next = NULL)
            break;
        pom = pom->next;
    }
}
// 5

// 6
void print_reverse(struct elem *list)
{
    if (list == NULL)
        return;
    print_reverse(list->next);
    printf("%d ", list->val);
}
// 7
void reverse_list(struct elem *list)
{
    struct elem *prev = NULL, *current = list, *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list = prev;
}