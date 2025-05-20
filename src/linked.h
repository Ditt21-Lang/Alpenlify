/* Dibuat oleh : Raffi, Andi, Gilag */
/* Tanggal     : 17-18-1945 */

#ifndef spnrsll_H
#define spnrsll_H
#include <stdio.h>
#include "player.h"
#define Nil NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) (L).First

typedef MusicNode* infotype;
typedef Node *address;


typedef struct {
	  address First;
} List;

bool ListEmpty (List L);

void CreateList (List * L);

address Alokasi (infotype X);

void DeAlokasi (address P);

address Search (List L, infotype X);

bool FSearch (List L, address P);

address SearchPrec (List L, infotype X);

void InsVFirst (List * L, infotype X);

void InsVLast (List * L, infotype X);

void DelVFirst (List * L, infotype * X);

void DelVLast (List * L, infotype * X);

void InsertFirst (List * L, address P);

void InsertAfter (List * L, address P, address Prec);

void InsertLast (List * L, address P);

void DelFirst (List * L, address * P);

void DelP (List * L, infotype X);

void DelLast (List * L, address * P);

void DelAfter (List * L, address * Pdel, address Prec);

void PrintInfo (List L);

void DelAll (List * L);

#endif