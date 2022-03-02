/*CODREANU DAN 311CB*/
#include "utils.h"


//Functie de comparare a doua elemente dupa rating sau in caz de rating egal, dupa nume.
//Intoarce 1 daca el2 trebuie pozitionat in fata lui el1, invers, intoarce 0
int compSerial(void *el1, void *el2)
{
    TCoada elem1 = (TCoada)el1;
    TCoada elem2 = (TCoada)el2;
    serialInfo *elem1Info = (serialInfo *)(elem1->info);
    serialInfo *elem2Info = (serialInfo *)(elem2->info);

    if (elem1Info->rating < elem2Info->rating)
        return 1;

    if (elem1Info->rating == elem2Info->rating)
    {
        if (strcmp(elem1Info->nume, elem2Info->nume) > 0)
            return 1;
    }
    return 0;
}

// Functie de comparare a pozitiilor a doua seriale din top
// Intoarce 1 daca pozitiile sunt egale, 0 altfel
int compTopSerial(void *el1, void *el2)
{
    TCoada elem1 = (TCoada)el1;
    TCoada elem2 = (TCoada)el2;
    topSerialInfo *elem1Info = (topSerialInfo *)(elem1->info);
    topSerialInfo *elem2Info = (topSerialInfo *)(elem2->info);

    if (elem1Info->position == elem2Info->position)
        return 1;
    return 0;
}

// Functie de comparare a doua nume de serial
// Intoarce 1 daca serialul are acelasi nume cu cel cautat, 0 altfel
int compNames(char* name1, char*name2)
{
    if (!strcmp(name1, name2))
        return 1;
    return 0;   
}

//Functia de scriere pentru serialele dintr-o lista, functia scrie numele si ratingul fiecarui serial din lista in fisierul numeFisierOut
void f_write(char* numeFisierOut, TLista head, char* cat)
{
    FILE *f;
    //deschiderea fisierului cu optiunea append
    f = fopen(numeFisierOut, "at");
    if (f == NULL)
        return;
    
    fprintf(f, "Categoria %s: [", cat);
    // Daca lista nu contine seriale atunci nu se printeaza denumirea niciunui serial
    if (head == NULL)
    {
        fprintf(f, "].\n");
        fclose(f);
        return;
    }
    
    TLista aux = head;
    // Se itereaza prin toata lista pana la ultimul element(fara ultimul) si se printeaza informatiile
    while (aux->next != NULL)
    {
        char*nume = infoSRL(aux)->nume;
        float rating = infoSRL(aux)->rating;
        fprintf(f, "(%s, %.1f), ",nume,rating);
        aux = aux->next;
    }
    // Se printeaza informatiile si pentru ultimul element
    fprintf(f, "(%s, %.1f)].\n", infoSRL(aux)->nume,infoSRL(aux)->rating);
    
    fclose(f);
}
// Functia de scriere pentru serialele dintr-o coada, functia scrie numele si ratingul fiecarui serial din coada in fisierul numeFisierOut
void f_writeQ(char* numeFisierOut, TCoada Q, char* cat)
{
    FILE *f;
    // Deschiderea fisierului cu optiunea append
    f = fopen(numeFisierOut, "at");
    if (f == NULL)
        return;

    fprintf(f, "Categoria %s: [", cat);
    // Daca coada este vida, afisez o coada goala
    if (VIDA(Q))
    {
        fprintf(f, "].\n");
        fclose(f);
        return;
    }
    else
    {
        // Obtin denumirea ultimului serial din coada
        char* last_name = ((serialInfo*)(((TCoada)(((TLista)(Q->sc))->info))->info))->nume;
        // Aloc o coada auxiliara
        TCoada aux = allocQ();
        // Cat timp coada nu este vida extrag o celula ce contine un serial
        // Numele serialului se compara cu numele ultimului serial apoi se face scrierea in fisier
        // La final celula se insereaza in coada auxiliara
        while (!VIDA(Q))
        {
            TLista check = ExtrQ(Q);
            if (strcmp(last_name,infoSRL(check)->nume))
            {
                fprintf(f, "(%s, %.1f), ", infoSRL(check)->nume,infoSRL(check)->rating);
            }
            else{
                fprintf(f, "(%s, %.1f)].\n", infoSRL(check)->nume,infoSRL(check)->rating);
            }
            InsertQ(check, aux);
        }
        // Cat timp coada auxiliara nu e vida, extrag un element din ea si il inserez in coada originala
        while (!VIDA(aux))
        {
            TLista to_insert = ExtrQ(aux);
            
            InsertQ(to_insert, Q);
        }
        // Elib. memoria ocupata de coada auxiliara
        free(aux);
    }
    fclose(f);
    return;
}
// Functia de scriere pentru serialele dintr-o stiva, functia scrie numele si ratingul fiecarui serial din stiva in fisierul numeFisierOut
void f_writeS(char* numeFisierOut, TStiva S, char* cat)
{
    FILE *f;
    // Deschiderea fisierului cu optiunea append
    f = fopen(numeFisierOut, "at");
    if (f == NULL)
        return;

    fprintf(f, "Categoria %s: [", cat);
    // Daca stiva este vida, se va afisa o stiva goala
    if (VIDAS(S))
    {
        fprintf(f, "].\n");
        fclose(f);
        return;
    }
    else{
        // Aloc o stiva auxiliara
        TStiva aux = AllocStack();
        // Extrag fiecare element din stiva si ii printez numele si rating-ul
        while (!VIDAS(S))
        {
            TLista check = Pop(S);
            if(!VIDAS(S)){
                fprintf(f, "(%s, %.1f), ", infoSRL(check)->nume,infoSRL(check)->rating);
            }
            else{
                fprintf(f, "(%s, %.1f)].\n", infoSRL(check)->nume,infoSRL(check)->rating);
            }
            Push(aux, check);
        }
        // Resetez stiva originala
        while (!VIDAS(aux))
        {
            TLista to_push = Pop(aux);
            Push(S, to_push);
        }
        free(aux);
    }
    fclose(f);
    return;
}
// Functia elibereaza memoria ocupaata de o categorie
void freeCategory(TLista* head)
{
    while(*head != NULL)
    {
        // Adresa celulei eliminate 
        TLista aux = *head;     
        if (!aux)
            return;
        // Elib.spatiul ocupat de element
        freeSerial(aux->info);  
        *head = aux->next;    
        free(aux);   
    }
}


// Functia de verificare daca top contine mai mult de 10 elemente, daca contine 11 returneaza 1, altfel 0
int full_top(TLista head){
    int i = 0;
    while (head != NULL)
    {
        head = head->next;
        i++;
    }
    if(i == 11)
        return 1;
    return 0;
}

// Functia de restrictionare a numarului de elemente din top la maximum 10
// In cazul in care sunt 11 elemente cel de pe pozitia 11 este eliminat
// Functia mai face si update pozitiilor fiecarui serial din top dupa o noua inserare
void restrictTop(TLista* top)
{
    TLista aux = *top, ant = *top;
    if (full_top(aux))
    {
        // Daca lista este plina(11 elemente), se parcurge pana la ultimul element si se elibereaza memoria
        while (aux->next != NULL)
        {
            ant = aux;
            aux = aux->next;    
        }
        ant->next = NULL;
        freeSerial(aux->info);
        free(aux);
    }
    // Resetare aux la prima pozitie
    aux = *top;
    int position = 1;
    // Parcurgerea listei si setarea pozitiei actualizate fiecarui element
    while(aux != NULL)
    {
        ((topSerialInfo*)(((TCoada)(aux->info))->info))->position = position;
        position++;
        aux = aux->next;
    }  
}


/**---------------------------Functii de adaugare sezon------------------------------------**/
// Functia adauga un sezon serialului cu nume dat ca parametru daca acesta exista in una din categorii
int add_sez_list(char *name,TCoada newSeason, TLista categories[])
{
    // Formez celula pentru noul sezon
    TLista seasonHolder = malloc(sizeof(TCelula));
    if (!seasonHolder)
        return 0;
    seasonHolder->info = (void*)(newSeason);
    seasonHolder->next = NULL;
    int i = 0;
    // Caut serialul in categorii si inserez sezonul daca acesta exista
    for(; i < 4; i++)
    {
        TLista aux = categories[i];
        while (aux != NULL)
        {
            char* serialName = infoSRL(aux)->nume;
            if (compNames(name, serialName))
            {
                infoSRL(aux)->nrOfSeasons += 1;
                sC(aux->info)->next = seasonHolder;
                sC(aux->info) = seasonHolder;
                return 1;
            }
            aux = aux->next;
        }
        
    }
    return 0;
}
// Functia adauga un sezon serialului cu nume dat ca parametru daca acesta exista in coada watch later
int add_sez_queue(char *name, TCoada newSeason, TCoada later)
{
    int inserted = 0;
     // Formez celula pentru noul sezon
    TLista seasonHolder = malloc(sizeof(TCelula));
    if (!seasonHolder)
        return 0;
    seasonHolder->info = (void*)(newSeason);
    seasonHolder->next = NULL;

    // Caut serialul prin coada si daca este gasit ii adaug un sezon nou
    TCoada aux = allocQ();
    while (!VIDA(later))
    {
        TLista current = ExtrQ(later);
        char* serialName = infoSRL(current)->nume;
        if (compNames(name, serialName))
        {
            infoSRL(current)->nrOfSeasons += 1;
            sC(current->info)->next = seasonHolder;
            sC(current->info) = seasonHolder;
            inserted = 1;
        }
        InsertQ(current, aux);
    }
    // Refac coada initiala 
    while (!VIDA(aux))
    {
        TLista to_insert = ExtrQ(aux);
        InsertQ(to_insert, later);
    }
    free(aux);
    return inserted;
    
}
// Functia adauga un sezon serialului cu nume dat ca parametru daca acesta exista in stiva currently watching
int add_sez_stack(char* name, TCoada newSeason, TStiva currentlyW)
{
    int inserted = 0;
    // Formez celula pentru noul sezon
    TLista seasonHolder = malloc(sizeof(TCelula));
    if (!seasonHolder)
        return 0;
    seasonHolder->info = (void*)(newSeason);
    seasonHolder->next = NULL;

    TStiva aux = AllocStack();
    // Caut serialul prin stiva si daca este gasit ii adaug un sezon nou
    while (!VIDAS(currentlyW))
    {
        TLista current = Pop(currentlyW);
        char* serialName = infoSRL(current)->nume;
        if (compNames(name, serialName))
        {
            infoSRL(current)->nrOfSeasons += 1;
            sC(current->info)->next = seasonHolder;
            sC(current->info) = seasonHolder;
            inserted = 1;
        }
        Push(aux, current);
    }
    // Refac stiva initiala
    while (!VIDAS(aux))
    {
        TLista to_push = Pop(aux);
        Push(currentlyW, to_push);
    }
    free(aux);
    return inserted;  
}
// Functia adauga un sezon nou serialului cu numele dat ca parametru
int add_sez(char* name, TCoada newSeason, TLista categories[], TCoada later, TStiva currentlyW, char* numeFisierOut)
{
    FILE *f;
    // Deschiderea fisierului cu optiunea append
    f = fopen(numeFisierOut, "at");
    if (f == NULL)
        return 0;
    // Daca serialul se afla in coada watch later se adauga sezonul
    if (findLater(later, name))
    {
       int good = add_sez_queue(name, newSeason, later);
        if (good)
        {
            fprintf(f,"Serialul %s are un sezon nou.\n", name);
            fclose(f);
            return 1;
        }
        
    }
    // Daca serialul se afla in stiva currently watching se adauga sezonul
    if (findStack(currentlyW, name))
    {
        int good = add_sez_stack(name, newSeason, currentlyW);
        if(good)
        {
            fprintf(f,"Serialul %s are un sezon nou.\n", name);
            fclose(f);
            return 1;
        }
    }
    // Daca serialul se afla in una dintre categorii, se adauga sezonul
    int good = add_sez_list(name, newSeason, categories);
    if(good)
    {
        fprintf(f,"Serialul %s are un sezon nou.\n", name);
        fclose(f);
        return 1;
    }

    fclose(f);
    return 0;
}
/**---------------------------Functii de adaugare sezon------------------------------------**/

/**---------------------------Functii pentru comanda watch---------------------------------**/
// Functia verifica daca un serial este privit integral sau nu
int watch_serial(void* to_serial, int watchDuration, char* numeFisierOut)
{
    FILE *f;
    // Deschiderea fisierului cu optiunea append
    f = fopen(numeFisierOut, "at");
    if (f == NULL)
        return 0;
    // Aloc cozi auxiliare pentru un serial si un sezon
    TCoada auxSRL = allocQ();
    TCoada auxSEZ = allocQ();
    TCoada serial = (TCoada)(to_serial);
    // Cat timp nu e gol serialul iau fiecare sezon din el
    while (!VIDA(serial))
    {
        TLista celToSeason = ExtrQ(serial);
        TCoada season = (TCoada)(celToSeason->info);
        // Cat timp sezonul si timpul de privit exista, extrag si verific fiecare episod
        while (!VIDA(season) && watchDuration)
        {
            TLista episode = ExtrQ(season);
            int epDuration = *((int*)(episode->info));

            // Daca episodul are mai mult decat timpul de privit
            if (epDuration > watchDuration)
            {
                // Micsorez durata episodului actual si setez timpul de privire la 0
                *((int*)(episode->info)) = epDuration - watchDuration;
                watchDuration = 0;
            }
            // Daca episodul dureaza mai putin decat timpul de privit
            else
            {
                // Micsorez timpul de privire si setez durata episodului la 0
                watchDuration = watchDuration - epDuration;
                *((int*)(episode->info)) = 0;
            }
            // Inserez episodul in coada auxiliara pentru sezon
            InsertQ(episode, auxSEZ);
        }
        // Daca nu a fost parcurs tot sezonul, il parcurg pana la capat
        while (!VIDA(season))
        {
            TLista to_insert = ExtrQ(season);
            InsertQ(to_insert, auxSEZ);
        }
        // Resetez sezonul si il introduc in coada auxiliara pentru serial
        while (!VIDA(auxSEZ))
        {
            TLista to_insert = ExtrQ(auxSEZ);
            InsertQ(to_insert, season);
        }
        InsertQ(celToSeason, auxSRL);
        
        // Daca timpul de privit s-a epuizat, parcurg intregul serial si mut sezoanele in coada auxiliara
        if (!watchDuration)
        {
            TLista to_insert_season = ExtrQ(serial);
            InsertQ(to_insert_season, auxSRL);
        }  
    }
    // Resetez serialul initial
    while (!VIDA(auxSRL))
    {
        TLista to_insert_season = ExtrQ(auxSRL);
        InsertQ(to_insert_season, serial);
    }
    free(auxSEZ);
    free(auxSRL);
    
    TLista lastSeasonHolder = SC(serial);
    TCoada lastSeason = (TCoada)(lastSeasonHolder->info);
    TLista lastEpisode = SC(lastSeason);
    // Daca durata ultimului episod este 0 atunci serialul a fost vizionat complet
    if (*((int*)(lastEpisode->info)) == 0)
    {
        char* name = ((serialInfo*)(serial->info))->nume;
        fprintf(f, "Serialul %s a fost vizionat integral.\n", name);
        fclose(f);
        return 1;
    }
    else
    {
        fclose(f);
        return 0;
    }    
    
}
/**---------------------------Functii pentru comanda watch---------------------------------**/