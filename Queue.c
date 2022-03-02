/*CODREANU DAN 311CB*/
#include "MyQueue.h"
// Functie de creare integrala a unui serial
TCoada createSerial(void* serial, int nrOfSeasons, int sznDuration[], int(*epDuration)[20])
{
    // Alocare si initializare coada ce va contine un serial
    TCoada serialQueue = malloc(sizeof(TCoadaCel));
    if (serialQueue == NULL)
        return NULL;

    serialQueue->info = serial;
    iC(serialQueue) = NULL;
    sC(serialQueue) = NULL;

    int i = 0;
    // for pentru fiecare sezon din serial
    for (; i < nrOfSeasons; i++)
    {
        // Alocare si initializare coada ce va contine un sezon din serial
        TCoada seasonQueue = malloc(sizeof(TCoadaCel));
        if (seasonQueue == NULL)
            return NULL;
        int* sznEpi = malloc(sizeof(int));
        memcpy(sznEpi, &sznDuration[i], sizeof(int));
        seasonQueue->info = (void*)sznEpi;
        iC(seasonQueue) = NULL;
        sC(seasonQueue) = NULL;

        int j = 0;
        // for pentru fiecare episod din sezon
        for (; j < sznDuration[i]; j++)
        {
            TLista episod = malloc(sizeof(TCelula)); //celula pentru fiecare episod
            if (episod == NULL)
                return NULL;
            int* epiTime = malloc(sizeof(int));
            memcpy(epiTime, &epDuration[i][j], sizeof(int));
            episod->info = (void*)epiTime;
            episod->next = NULL;
            // introducere celula cu episod in coada sezon pentru cazurile de coada vida si nevida
            if (VIDA(seasonQueue))
            {
                iC(seasonQueue) = episod;
                sC(seasonQueue) = episod;
            }
            else
            {
                sC(seasonQueue)->next = episod;
                sC(seasonQueue) = episod;
            }
        }
        //alocarea unei celule ce contine un sezon
        TLista fullSeason = malloc(sizeof(TCelula));
        if (fullSeason == NULL)
            return NULL;

        fullSeason->info = seasonQueue;
        fullSeason->next = NULL;
        // introducere celula cu sezon in coada serial pentru cazurile de coada vida si nevida
        if (VIDA(serialQueue))
        {
            iC(serialQueue) = fullSeason;
            sC(serialQueue) = fullSeason;
        }
        else
        {
            sC(serialQueue)->next = fullSeason;
            sC(serialQueue) = fullSeason;
        }
        
    }
    return serialQueue;
}

// Functia de extragere a primei celule de tip TLista din coada q
TLista ExtrQ(TCoada q)
{
    // Daca coada e vida se returneaza NULL
    if(VIDA(q))
        return NULL;
    
    // Stochez primul element din coada in aux
    TLista aux = iC(q);
    // Daca e singurul element, setez sC la NULL
    if (aux->next == NULL)
        sC(q) = NULL;
    // Mut iC la urmatorul element 
    iC(q) = aux->next;
    aux->next = NULL;
    return aux;
}
// Functie de inserare element in coada
void InsertQ(TLista to_insert, TCoada q)
{
    // Daca coada e vida, IC si SC vor pointa la elementul inserat
    if(VIDA(q))
    {
        IC(q) = to_insert;
        SC(q) = to_insert;
    }
    // In caz contrar ultimul element si SC vor pointa la elementul inserat
    else
    {
        SC(q)->next = to_insert;
        SC(q) = to_insert;
    }
}


/*-----------------------Functii de eliberare------------------------*/
// Functie pentru eliberarea unui sezon
void freeSeason(void* to_free_season)
{
    TCoada season = (TCoada)to_free_season;
    TLista aux = NULL;
    // Cat timp coada sezon nu e vida
    while (!VIDA(season))
    {
        // Extragere o celula (episod) din serial si eliberarea acesteia
        aux = ExtrQ(season);
        free(aux->info);
        free(aux);
        aux = NULL;
    }
    // Eliberarea memoriei pentru coada serial
    free(season->info);
    free(season);
    season = NULL; 
}

// Functie pentru eliberarea informatiei unui serial
void freeSerialInfo(void* to_free_info)
{
    serialInfo* info = (serialInfo*)to_free_info;
    free(info->nume);
    free(info);
    info = NULL;
}

// Functie pentru eliberarea unui serial
void freeSerial(void* to_free_serial)
{
    TCoada serial = (TCoada)to_free_serial;
    // Eliberez informatiile despre un serial
    freeSerialInfo(serial->info);

    TLista aux = NULL;
    // Cat timp serialul nu e vid se extrage din el cate o celula ce contine un sezon si se elibereaza
    while (!VIDA(serial))
    {
        aux = ExtrQ(serial);
        freeSeason(aux->info);
        free(aux);
        aux = NULL;
    }
    // Se elibereaza memoria pentru coada serial
    free(serial);
    serial = NULL;
}


/*-----------------------Functii de eliberare------------------------*/


// Functia show este apelata in cazul primirii comenzii show X si afiseaza numele si rating-ul serialelor dintr-o anumita structura
void show(char* text, char* numeFisierOut, TLista* categories, TFWrite f_write)
{
    // Daca lungimea lui text = 1 atunci se cere afisarea serialelor din una dintre categoriile 1-3, altfel se afiseaza cele din top10
    if (strlen(text) == 1)
    {
        int category = atoi(text);
        f_write(numeFisierOut, categories[category-1], text);
    }
    else if (!strcmp(text,"top10"))
    {
       f_write(numeFisierOut, categories[3], text);
    }    
}

// Functie de alocare a unei cozi vide
TCoada allocQ()
{
     // Alocare si initializare coada ce va contine un serial
    TCoada Queue = malloc(sizeof(TCoadaCel));
    if (Queue == NULL)
        return NULL;

    Queue->info = NULL;
    iC(Queue) = NULL;
    sC(Queue) = NULL;

    return Queue;
}
// Functie ce gaseste serialul cu numele corect dintr-o lista
TLista findSerial(char* name, TLista* head, TFCompN compNames)
{
    // Setare aux la capul listei si ant cu NULL
    TLista aux = *head, ant = NULL;
    while (aux != NULL)
    {
        // Parcurgerea listei si verificarea daca serialul este cel cautat
        TCoada serial = (TCoada)(aux->info);
        char* nameToCheck = ((serialInfo*)(serial->info))->nume;
        if (compNames(name, nameToCheck))
            break;
        
        ant = aux;
        aux = aux->next;
    }
    // Daca s-a gasit serialul se face extragerea si restabilirea legaturilor
    if (aux)
    {
        if(ant == NULL)
        {
            *head = aux->next;
            aux->next = NULL;
        }
        else
        {
            ant->next = aux->next;
            aux->next = NULL;
        }
        // Celula ce contine serialul cautat este returnata
        return aux;
    }
    // Daca nu s-a gasit serialul necesar, functia returneaza NULL
    return NULL;
    
}

// Functia de inserare a unei celule ce contine un serial in coada
int insertLater(TLista to_insert, char* numeFisierOut, TCoada LaterQ)
{
    FILE *f;
    //deschiderea fisierului cu optiunea append
    f = fopen(numeFisierOut, "at");
    if (f == NULL)
        return -1;

    // Daca coada e vida IC si SC vor pointa catre serialul de inserat si in fisier va fi afisat mesajul de inserare cu pozitia 1
    if (VIDA(LaterQ))
    {
        IC(LaterQ) = to_insert;
        SC(LaterQ) = to_insert;
        fprintf(f, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n",infoSRL(to_insert)->nume, 1);
    }
    // Altferl serialul este inserat la sfarsitul cozii
    else
    {
        int position = 1;
        TLista aux = IC(LaterQ);
        // Se afla pozitia pe care va fi inserat serialul
        while (aux)
        {
            aux = aux->next;
            position++;
        }
        SC(LaterQ)->next = to_insert;
        SC(LaterQ) = to_insert;
        fprintf(f, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n",infoSRL(to_insert)->nume, position);
    }
    // Inchiderea fisierului
    fclose(f);
    return 1;
}
// Functie de eliberare a memoriei ocupate de o coada
void freeLater(TCoada later)
{
    // Cat timp coada later nu e vida se extrage cate o celula ce contine un serial
    while (!VIDA(later))
    {
        TLista aux = ExtrQ(later);
        // Elib. memoriei ocupata de un serial
        freeSerial(aux->info);
        free(aux);
        aux = NULL;
    }
    // Elib. memoriei ocupata de coada later
    free(later);
    later = NULL;
}

// Functia determina daca serialul cu numele dat ca parametru este in coada later
// Intoarce 1 in caz ca exista, 0 altfel
int findLater(TCoada laterQueue, char* name)
{
    int found = 0;
    TCoada aux = allocQ();
    // Cat timp coada initiala nu e vida extrag fiecare serial si verific daca e cel cautat apoi inserez in coada auxiliara
    while (!VIDA(laterQueue))
    {
        TLista current = ExtrQ(laterQueue);
        char* current_name = infoSRL(current)->nume;
        if (!strcmp(name, current_name))
        {
            found = 1;
        }
        InsertQ(current, aux);
    }
    // Reformez coada initiala
    while (!VIDA(aux))
    {
        TLista to_insert = ExtrQ(aux);
        InsertQ(to_insert, laterQueue);
    }
    free(aux);
    return found;
}

// Functia creeaza un nou sezon integral
TCoada CreateSeason(int episodeDurations[], int numberOfEpisodes)
{
    // Aloc coada pentru noul sezon
    TCoada newSeason = allocQ();
    int* numOfEps = malloc(sizeof(int));
    if(!numOfEps)
        return NULL;
    memcpy(numOfEps, &numberOfEpisodes, sizeof(int));
    // Inserez numarul de episoade din noul sezon
    newSeason->info = (void*)numOfEps;

    int i = 0;
    for (; i < numberOfEpisodes; i++)
    {
        TLista aux = malloc(sizeof(TCelula));
        if (aux == NULL)
                return NULL;
        int* epsDuration = malloc(sizeof(int));
        memcpy(epsDuration, &episodeDurations[i], sizeof(int));
        // Inserez durata fiecarui episod in celula sa
        aux->info = (void*)epsDuration;
        aux->next = NULL;
        InsertQ(aux, newSeason);
    }
    return newSeason;
}
// Functie de extragere a unui element cu nume dat ca parametru din coada
TLista get_by_nameQ(TCoada q, char *name)
{
    int found;
    // Aloc o coada auxiliara
    TCoada aux = allocQ();
    TLista current = NULL, to_return = NULL;
    // Cat timp coada nu e vida, extrag fiecare serial si verific daca este cel cautat 
    while (!VIDA(q))
    {
        found = 0;
        current = ExtrQ(q);
        char* current_name = infoSRL(current)->nume;
        // Daca am gasit serialul potrivit il stochez in to_return
        if (!strcmp(name, current_name))
        {
            to_return = current;
            found = 1;
        }
        if(!found)
            InsertQ(current, aux);
    }
    // Reformez coada initiala
    while (!VIDA(aux))
    {
        TLista to_insert = ExtrQ(aux);
        InsertQ(to_insert, q);
    }
    free(aux);
    return to_return;
}
