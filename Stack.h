/*CODREANU DAN 311CB*/
#include <stdio.h>
#include <stdlib.h>
#include "MyQueue.h"

#ifndef _STIVA_
#define _STIVA_

#define VF(s) (s->vf)
#define VIDAS(s) (VF(s) == NULL)

typedef struct stiva{
    void* info;
    TLista vf;
}StivaCel, *TStiva;

TStiva AllocStack(); // Functie pentru alocarea unei stive vide

TLista Pop(TStiva s); // Functie pentru extragerea elementului din varful stivei

void Push(TStiva s, TLista to_push); // Functie de introducere element in stiva

void freeStack(TStiva s); // Functie de eliberare a memorieiocupate de stiva 

int findStack(TStiva currentlyW, char* name); // Functia determina daca serialul cu numele dat ca parametru este in stiva

TLista get_by_nameS(TStiva s, char*name); // Functia cauta in stiva elementul cu numele dat ca parametru si intoarce celula acestuia sau NULL daca nu exista

#endif