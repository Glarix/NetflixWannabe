/*CODREANU DAN*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "MyQueue.h"
#include "utils.h"



//Functie care citeste fisierul de intrare si prelucreaza informatia din el
void citesteInput(char *numeFisier, char *numeFisierOut, TLista *categories, TCoada laterQueue, TStiva currently_watching, TStiva history)
{
    FILE *f;
    char *line = NULL;
    size_t len = 0;

    //deschiderea fisierului de intrare
    f = fopen(numeFisier, "rt");
    if (f == NULL)
        return;

    //citirea fisierului linie cu linie
    while (getline(&line, &len, f) != -1)
    {
        //obtinerea comenzii
        char *comanda = strtok(line, " ");
        if (!strcmp(comanda, "add") || !strcmp(comanda, "add_top"))
        {
            // Obtinerea informatiilor pentru un serial
            char *id = strtok(NULL, " ");
            char *numeSRL = strtok(NULL, " ");
            char *rating = strtok(NULL, " ");
            char *manySeasons = strtok(NULL, " ");
            
            serialInfo *serial = NULL;
            topSerialInfo *topSerial = NULL;

            if (!strcmp(comanda, "add"))
            {
                // Alocarea si stocarea informatiilor unui serial in structura de informatii pentru serial
                serial = (serialInfo*)malloc(sizeof(serialInfo));
                if (serial == NULL)
                    return;
                serial->nume = (char *)malloc((strlen(numeSRL) + 1) * sizeof(char));
                strcpy(serial->nume, numeSRL);
                serial->ID = atoi(id);
                serial->rating = atof(rating);
                serial->nrOfSeasons = atoi(manySeasons);
            }
            

            if (!strcmp(comanda, "add_top"))
            {
                // Alocarea si stocarea informatiilor unui serial din top in structura de informatii pentru serial
                topSerial = (topSerialInfo*)malloc(sizeof(topSerialInfo));
                if (topSerial == NULL)
                    return;
                topSerial->nume = (char *)malloc((strlen(numeSRL) + 1) * sizeof(char));
                strcpy(topSerial->nume, numeSRL);
                topSerial->ID = 4;
                topSerial->position = atoi(id);
                topSerial->rating = atof(rating);
                topSerial->nrOfSeasons = atoi(manySeasons);
            }

            

            // Tabel pentru stocarea numarului de episoade din fiecare sezon posibil
            int szn_duration[10];
            // Matrice pentru stocarea duratei fiecarui episod din fiecare sezon posibil
            int szn_array[10][20];
            int i = 0;

            // For pentru obtinerea informatiilor pentru fiecare sezon
            for (; i < atoi(manySeasons); i++)
            {
                char *epsPerSzn = strtok(NULL, " ");
                szn_duration[i] = atoi(epsPerSzn);

                int j = 0;
                // For pentru obtinerea informatiilor pentru fiecare episod
                for (; j < szn_duration[i]; j++)
                {
                    char *time = strtok(NULL, " ");
                    szn_array[i][j] = atoi(time);
                }
            }
            // Formarea cozii ce stocheaza un serial
            if (!strcmp(comanda, "add")){
                TCoada serialQueue = createSerial(serial, serial->nrOfSeasons, szn_duration, szn_array);
                // Inserarea serialului in categoria potrivita
                push_in(&categories[(serial->ID) - 1], serialQueue, compSerial, numeFisierOut, numeSRL);
            }else
            {
                TCoada serialQueue = createSerial(topSerial, topSerial->nrOfSeasons, szn_duration, szn_array);
                // Inserarea serialului in categoria potrivita(categoria top)
                push_inTop(&categories[3], serialQueue, compTopSerial);
                // Apel catre functia de verificare a conditiei de elemente maxime din top si update a pozitiei elementelor
                restrictTop(&categories[3]);
                show("top10", numeFisierOut, categories, f_write);
            }
        }
        else if (!strcmp(comanda, "show"))
        {
            // Obtinerea id-ului pentru structura care contine serialele de afisat
            char *id = strtok(NULL, " ");
            if (id[strlen(id) - 1] == '\n')
                id[strlen(id) - 1] = '\0';
            if (id[strlen(id) - 1] == '\r')
                id[strlen(id) - 1] = '\0';
            // Verificarea ID-ului si apelarea functiei corespunzatoare de afisare
            if(!strcmp(id, "later"))
            {
                // Afisarea serialelor din categoria later
                f_writeQ( numeFisierOut, laterQueue, "later");
            }
            else if(!strcmp(id, "watching"))
            {
                f_writeS(numeFisierOut, currently_watching, "watching");
            }
            else if(!strcmp(id, "history"))
            {
                f_writeS(numeFisierOut, history, "history");
            }
            else
            {
                // Afisarea serialelor din categoria potrivita
                show(id, numeFisierOut, categories, f_write);
            }
        }
        else if (!strcmp(comanda, "later"))
        {
            // Obtinerea numelui serialului si eliminarea \n || \r de pe ultima pozitie in caz ca acestea exista
            char *name = strtok(NULL, " ");
            if (name[strlen(name) - 1] == '\n')
                name[strlen(name) - 1] = '\0';
            if (name[strlen(name) - 1] == '\r')
                name[strlen(name) - 1] = '\0';

            // Initializarea unui element de tip TLista in care se va stoca celula
            // ce contine serialul de mutat in later, daca acaesta va fi gasit
            TLista goodSerial = NULL;
            int i = 0;

            // Se verifica fiecare dintre cele 4 categorii posibile si se cauta serialul dorit
            // Daca exista serialul, acesta este stocat in goodSerial si se intrerupe cautarea
            for(; i < 4; i++)
            {
                goodSerial = findSerial(name, &categories[i], compNames);
                if(goodSerial)
                    break;
            }
            // Daca serialul necesar a fost gasit se introduce in coada later
            if (goodSerial)
            {
                insertLater(goodSerial, numeFisierOut, laterQueue);
                // Se verifica daca serialul mutat a fost scos din categoria top10
                // In caz afirmativ, aceasta categorie este actualizata 
                restrictTop(&categories[3]);
            }         
        }
        else if(!strcmp(comanda, "add_sez"))
        {
            // Colectez si stochez datele noului sezon 
            char *name = strtok(NULL, " ");
            char *nrEpis = strtok(NULL, " ");
            int epArr[20], k = 0;
            for (; k < atoi(nrEpis); k++)
            {
                char *epDur = strtok(NULL, " ");
                epArr[k] = atoi(epDur);
            }
            int numberOfEp = atoi(nrEpis);
            // Creez noul sezon
            TCoada newSeason = CreateSeason(epArr, numberOfEp);
            // Adaug noul sezon serialului potrivit (serialul trebuie sa se afle in categorii sau coada later sau stiva currently_watching)
            add_sez(name, newSeason, categories, laterQueue, currently_watching, numeFisierOut);
        }
        else if(!strcmp(comanda, "watch"))
        {
            // Obtin informatiile
            char *name = strtok(NULL, " ");
            char *time = strtok(NULL, " ");
            int watchTime = atoi(time); 
            // Setez o celula care va contine in info serialul potrivit
            TLista goodSerial = NULL;
            int i = 0, view = 0;
            // Caut serialul in cele 4 categorii
            for(; i < 4; i++)
            {
                goodSerial = findSerial(name, &categories[i], compNames);
                // Daca a fost gasit verific ca top10 sa fie in regula
                if(goodSerial)
                {
                    restrictTop(&categories[3]);
                    break;
                }
            }
            // Daca nu a fost gasit in categorii e cautat in coada later
            if(!goodSerial)
            {
                goodSerial = get_by_nameQ(laterQueue, name);
            }
            // Daca nu a fost gasit e cautat in stiva currently_watching
            if(!goodSerial)
            {
                goodSerial = get_by_nameS(currently_watching, name);
            }
            // Daca serialul a fost gasit se verifica daca este vizionat integral sau nu
            if(goodSerial){
                view = watch_serial(goodSerial->info, watchTime, numeFisierOut);
                if (view == 0)
                {
                    // Daca nu a fost vizionat integral este pus in varful stivei currently_watching
                    Push(currently_watching, goodSerial);
                }
                else
                {
                    // Daca a fost vizionat integral este pus in stiva history
                    Push(history, goodSerial);
                }
            }
        }
    }
    fclose(f);
    if (line)
        free(line); //eliberarea memoriei pentru line

}

int main(int argc, char *argv[])
{
    int cat = 0;
    // Formarea celor 4 categorii de seriale
    TLista categories[4];
    for (; cat < 4; cat++)
    {
        categories[cat] = NULL;
    }
    // Alocarea memoriei pentru coada later, stivele currently_watching si history
    TCoada laterQueue = allocQ();
    TStiva currently_watching = AllocStack();
    TStiva history = AllocStack();

    //citirea si prelucrarea informatiei din fisierul de intrare
    citesteInput(argv[1], argv[2], categories, laterQueue, currently_watching, history);

    // Eliberare memorie pentru coada later
    freeLater(laterQueue);

    // Eliberare memorie ocupata de stivele currently_watching si history
    freeStack(currently_watching);
    freeStack(history);

    // Eliberare memorie pentru cele 4 categorii de seriale
    for(cat = 0; cat < 4; cat++)
    {
        freeCategory(&categories[cat]);
    }
    return 0;
}
