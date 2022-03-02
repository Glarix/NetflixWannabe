/*CODREANU DAN 311CB*/
#include "Stack.h"


// Functie pentru alocarea unei stive vide
TStiva AllocStack()
{
    TStiva Stack;
    Stack = (TStiva)malloc(sizeof(StivaCel));
    if(!Stack)
        return NULL;

    //Setarea elementelor stivei la NULL
    Stack->info = NULL;
    Stack->vf = NULL;
    return Stack;
}
// Functie pentru extragerea elementului din varful stivei
TLista Pop(TStiva s)
{
    if (VIDAS(s))
        return NULL;
    // Extragerea elementului din varf
    TLista aux = VF(s);
    // Mutarea pointerului catre urmatorul element
    VF(s) = aux->next;
    return aux;   
}
// Functie de introducere element in stiva
void Push(TStiva s, TLista to_push)
{
    to_push->next = VF(s);
    VF(s) = to_push;
}
// Functie de eliberare a memorieiocupate de stiva
void freeStack(TStiva s)
{
    while (!VIDAS(s))
    {
        TLista aux = Pop(s);
        freeSerial(aux->info);
        free(aux);
        aux = NULL;
    }
    free(s);
    s = NULL;
}
// Functia determina daca serialul cu numele dat ca parametru este in stiva
// Intoarce 1 daca serialul e gasit, 0 altfel
int findStack(TStiva currentlyW, char* name)
{
    int found = 0;
    TStiva aux = AllocStack();
    // Cat timp stiva nu e vida, verific fiecare serial apoi il pun in stiva auxiliara
    while (!VIDAS(currentlyW))
    {
        TLista current = Pop(currentlyW);
        char* current_name = infoSRL(current)->nume;
        if (!strcmp(name, current_name))
        {
            found = 1;
        }
        Push(aux, current);
    }
    // Refac stiva originala
    while (!VIDAS(aux))
    {
        TLista to_push = Pop(aux);
        Push(currentlyW, to_push);
    }
    free(aux);
    return found;
}
// Functia cauta in stiva elementul cu numele dat ca parametru si intoarce celula acestuia sau NULL daca nu exista
TLista get_by_nameS(TStiva s, char*name)
{   
    int found;
    // Aloc memorie pentru o stiva auxiliara
    TStiva aux = AllocStack();
    TLista to_return = NULL, current = NULL;
    // Cat timp stiva nu e vida caut serialul in ea
    while (!VIDAS(s))
    {
        found = 0;
        current = Pop(s);
        char* current_name = infoSRL(current)->nume;
        // Daca s-a gasit serialul il stochez in to_return
        if (!strcmp(name, current_name))
        {
            to_return = current;
            found = 1;
        }
        if(!found)
            Push(aux, current);
    }

    // Refac stiva originala
    while (!VIDAS(aux))
    {
        TLista to_push = Pop(aux);
        Push(s, to_push);
    }
    free(aux);
    return to_return;
}
