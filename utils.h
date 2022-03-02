/*CODREANU DAN 311CB*/
#include "MyQueue.h"
#include "Stack.h"


int compSerial(void *el1, void *el2); //Functie de comparare a doua elemente dupa rating sau in caz de rating egal, dupa nume.

int compTopSerial(void *el1, void *el2); // Functie de comparare a pozitiilor a doua seriale din top

int compNames(char* name1, char*name2); // Functie de comparare a doua nume de serial

void f_write(char* numeFisierOut, TLista head, char* cat); // Functia de scriere pentru serialele dintr-o lista, functia scrie numele si ratingul fiecarui serial din lista in fisierul numeFisierOut

void f_writeQ(char* numeFisierOut, TCoada Q, char* cat); // Functia de scriere pentru serialele dintr-o coada, functia scrie numele si ratingul fiecarui serial din coada in fisierul numeFisierOut

void f_writeS(char* numeFisierOut, TStiva S, char* cat); // Functia de scriere pentru serialele dintr-o stiva, functia scrie numele si ratingul fiecarui serial din stiva in fisierul numeFisierOut

void freeCategory(TLista* head); // Functia elibereaza memoria ocupaata de o categorie

void restrictTop(TLista* top); // Functia de restrictionare a numarului de elemente din top la maximum 10

int add_sez_list(char *name, TCoada newSeason, TLista categories[]); // Functia adauga un sezon serialului cu nume dat ca parametru daca acesta exista in una din categorii

int add_sez_queue(char *name, TCoada newSeason, TCoada later); // Functia adauga un sezon serialului cu nume dat ca parametru daca acesta exista in coada watch later

int add_sez_stack(char* name, TCoada newSeason, TStiva currentlyW); // Functia adauga un sezon serialului cu nume dat ca parametru daca acesta exista in stiva currently watching

int add_sez(char* name, TCoada newSeason, TLista categories[], TCoada later, TStiva currentlyW, char* numeFisierOut); // Functia adauga un sezon nou serialului cu numele dat ca parametru

int watch_serial(void* to_serial, int watchDuration, char* numeFisierOut); // Functia verifica daca un serial este privit integral sau nu
