/*CODREANU DAN 311CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lists.h"


#ifndef COADA
#define COADA

#define iC(c) (((TCoada) (c))->ic)
#define sC(c) (((TCoada) (c))->sc)

#define IC(c) (c->ic) 
#define SC(c) (c->sc)

#define VIDA(c) ((iC(c) == NULL) && (sC(c) == NULL)) // Verificare daca o coada e vida

#define infoSRL(c) ((serialInfo*)(((TCoada)(c->info))->info)) // acces la informatiile dintr-un serial

typedef void (*TFWrite)(char*, TLista, char*); // tip de functie de scriere

typedef int (*TFCompN)(char*, char*); // tip de functie pentru compararea a 2 char*

typedef struct serial_info
{
    int ID;
    char *nume;
    float rating;
    int nrOfSeasons;
}serialInfo; // Informatiile despre un serial obisnuit 

typedef struct serial_info_top
{
    int ID;
    char *nume;
    float rating;
    int nrOfSeasons;
    int position;
}topSerialInfo; // Informatiile despre un serial din top10


typedef struct coada
{
    void* info;
    TLista ic, sc;
}TCoadaCel, *TCoada; // Structura unei cozi

// Functie de creare integrala a unui serial
TCoada createSerial(void* serial, int nrOfSeasons, int sznDuration[], int(*epDuration)[20]);

TLista ExtrQ(TCoada q); // Functia de extragere a primei celule de tip TLista din coada q

void InsertQ(TLista to_insert, TCoada q); // Functie de inserare element in coada q

void freeSeason(void* to_free_season); // Functie pentru eliberarea unui sezon

void freeSerialInfo(void* to_free_info); // Functie pentru eliberarea informatiei unui serial

void freeSerial(void* to_free_serial); // Functie pentru eliberarea unui serial

void show(char* text, char* numeFisierOut, TLista* categories, TFWrite f_write); // Functie pentru afisarea uneia dintre cele 4 categorii

TCoada allocQ(); // Functie de alocare a unei cozi vide

TLista findSerial(char*name, TLista* head, TFCompN compNames); // Functie ce gaseste serialul cu numele corect dintr-o lista

int insertLater(TLista to_insert, char* numeFisierOut, TCoada LaterQ); // Functia de inserare a unei celule ce contine un serial in coada

void freeLater(TCoada later); // Functie de eliberare a memoriei ocupate de o coada

int findLater(TCoada laterQueue, char* name); // Functia determina daca serialul cu numele dat ca parametru este in coada later

TCoada CreateSeason(int episodeDurations[], int numberOfEpisodes); // Functia creeaza un nou sezon integral

TLista get_by_nameQ(TCoada q, char *name); // Functie de extragere a unui element cu nume dat ca parametru din coada


#endif