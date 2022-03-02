/*CODREANU DAN 311CB*/
#include "lists.h"



// Functia de introducere sortata in lista unei categorii in baza informatiilor primite la functia add 
int push_in(TLista* head, void* serialQueue, TFComp compare, char* numeFisierOut, char* name)
{
    FILE *f;
    //deschiderea fisierului cu optiunea append
    f = fopen(numeFisierOut, "at");
    if (f == NULL)
        return -1;
    
    // Contor pentru pozitia la care a fost inserat un element
    int position = 1;
    // Alocarea si initializarea unei celule ce contine in informatie un serial 
    TLista current = malloc(sizeof(TCelula));
    if (!current)
        return 0;
    current->info = serialQueue;
    current->next = NULL;

    TLista aux = *head, ant = NULL;
    // In cazul unei liste vide se insereaza pe prima pozitie
    if (*head == NULL)
    {
        *head = current;
        fprintf(f, "Serialul %s a fost adaugat la pozitia %d.\n", name, 1);
    }
    else
    {
        // In cazul in care sunt deja elemente in lista, fiecare serial este examinat pana la gasirea serialului inaintea caruia
        // trebuie inserat noul serial in functie de rating sau nume
        while (aux != NULL)
		{
            // Se compara elementul curent din lista cu elementul pentru inserare 
			if(compare(aux->info,serialQueue))
				break;
			
			ant = aux;
			aux = aux->next;
            position++;
		}
        // In cazul inserarii inaintea primului element
        if (ant == NULL)
		{
			current->next = *head;
			*head = current;
            fprintf(f, "Serialul %s a fost adaugat la pozitia %d.\n", name, 1);
		}
        else
        {
            // Inserarea inaintea elementului gasit
			current->next = aux;
			ant->next = current;
            fprintf(f, "Serialul %s a fost adaugat la pozitia %d.\n", name, position);
		}		
    }
    fclose(f);
    return position;
}

// Functia de introducere a unui serial in top pe pozitia potrivita
void push_inTop(TLista* head, void* serialQueue, TFComp comparePosition)
{
    // Alocarea si initializarea unei celule ce contine in informatie un serial 
    TLista current = malloc(sizeof(TCelula));
    if (!current)
        return;
    current->info = serialQueue;
    current->next = NULL;

    TLista aux = *head, ant = NULL;
    // In cazul unei liste vide se insereaza pe prima pozitie
    if (*head == NULL)
    {
        *head = current;
    }
    else
    {
        while (aux != NULL)
		{
            // Se compara elementul curent din lista cu elementul pentru inserare
            // Aux va fi elementul inaintea caruia se va face inserarea 
			if(comparePosition(aux->info,serialQueue))
				break;
			
			ant = aux;
			aux = aux->next;
        }

        // In cazul inserarii inaintea primului element
        if (ant == NULL)
		{
			current->next = *head;
			*head = current;
		}
        else
        {
            // Inserarea inaintea elementului gasit
			current->next = aux;
			ant->next = current;
		}
    }
}



