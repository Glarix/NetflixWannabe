/*CODREANU DAN 311CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>



#ifndef _SIMPLE_LIST_
#define _SIMPLE_LIST_

typedef int (*TFComp)(void*, void*);

typedef struct list{
    void* info;
    struct list* next;
}TCelula, *TLista;

// Functia de introducere sortata in lista unei categorii in baza informatiilor primite la functia add
int push_in(TLista* head, void* serial, TFComp compare, char* numeFisierOut, char*name);

void push_inTop(TLista* head, void* serialQueue, TFComp comparePosition); // Functia de introducere a unui serial in top pe pozitia potrivita

#endif