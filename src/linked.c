#include <limits.h>
#include <malloc.h>
#include <string.h>
#include "linked.h"
#include <stdbool.h>
#define UNUSED(x) (void)x;

bool ListEmpty(List L)

{
    return (First(L) == Nil);
}

void CreateList(List *L)

{
    First(*L) = Nil;
}

address Alokasi(infotype X)

{
    address P;

    P = (address)malloc(sizeof(ElmtList));
    if (P != Nil)
    {
        Info(P) = X;
        Next(P) = Nil;
    }
    return (P);
}

void DeAlokasi(address P)

{
    if (P != Nil)
    {
        free(P);
    }
}

address Search(List L, infotype X)

{

    address P;
    bool found = false;

    P = First(L);
    while ((P != Nil) && (!found))
    {
        if (strcmp(Info(P), X) == 0)
        {
            found = true;
        }
        else
        {
            P = Next(P);
        }
    }

    return (P);
}

bool FSearch(List L, address P)

{

    bool found = false;
    address PSearch;

    PSearch = First(L);
    while ((PSearch != Nil) && (!found))
    {
        if (PSearch == P)
        {
            found = true;
        }
        else
        {
            PSearch = Next(PSearch);
        }
    }

    return (found);
}

address SearchPrec(List L, infotype X)

{

    address Prec, P;
    bool found = false;

    Prec = Nil;
    P = First(L);
    while ((P != Nil) && (!found))
    {
        if (strcmp(Info(P), X) == 0)
        {

            found = true;
        }
        else
        {
            Prec = P;
            P = Next(P);
        }
    }
    if (found)
    {
        return (Prec);
    }
    else
    {
        return (Nil);
    }
}

void InsVFirst(List *L, infotype X)

{

    address P;

    P = Alokasi(X);
    if (P != Nil)
    {
        InsertFirst(L, P);
    }
}

void InsVLast(List *L, infotype X)

{

    address P;

    P = Alokasi(X);
    if (P != Nil)
    {
        InsertLast(L, P);
    }
}

void DelVFirst(List *L, infotype *X)

{

    address P;

    DelFirst(L, &P);
    *X = P->info;
    DeAlokasi(P);
}

void DelVLast(List *L, infotype *X)

{

    address PDel;

    DelLast(L, &PDel);
    *X = PDel->info;
    DeAlokasi(PDel);
}

void InsertFirst(List *L, address P)

{

    P->next = L->First;
    L->First = P;
    UNUSED(L)
}

void InsertAfter(List *L, address P, address Prec)

{
    UNUSED(L)

    P->next = Prec->next;
    Prec->next = P;
}

void InsertLast(List *L, address P)

{

    address Last;

    if (L->First == Nil)
    {
        L->First = P;
    }
    else
    {
        Last = L->First;

        while (Last->next != Nil)
        {
            Last = Last->next;
        }

        Last->next = P;
    }
}

void DelFirst(List *L, address *P)

{

    *P = L->First;
    L->First = L->First->next;
}

void DelP(List *L, infotype X)

{

    address P, Prec;
    bool found = false;
    UNUSED(found)

    Prec = SearchPrec(*L, X);

    if (Prec == Nil)
    {
        if (strcmp(Info(First(*L)), X) == 0)
        {
            DelVFirst(L, &X);
        }
        else
        {
            printf("Elemen pertama not found");
        }
    }
    else
    {
        found = true;
        DelAfter(L, &P, Prec);
        DeAlokasi(P);
    }
}

void DelLast(List *L, address *P)

{

    address Prev;

    Prev = L->First;
    if (Prev->next == Nil)
    {
        *P = L->First;
        L->First = Nil;
        return;
    }

    while (Prev->next->next != Nil)
    {
        Prev = Prev->next;
    }

    *P = Prev->next;
    Prev->next = Nil;
}

void DelAfter(List *L, address *Pdel, address Prec)

{
    UNUSED(L)

    *Pdel = Prec->next;
    Prec->next = Prec->next->next;
}

void PrintInfo(List L)

{

    address P;

    if (First(L) == Nil)
    {
        printf("List Kosong\n");
    }
    else
    {
        P = First(L);
        while (P != Nil)
        {
            printf("%s ", Info(P));
            P = Next(P);
        }
        printf("\n");
    }
}

void DelAll(List *L)

{

    address PDel;

    PDel = L->First;

    while (PDel != Nil)
    {
        DelFirst(L, &PDel);
        DeAlokasi(PDel);
        PDel = L->First;
    }
}
