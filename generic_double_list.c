/* MIHAILESCU Eduard-Florin - 312CB */
#include "generic_double_list.h"

int InsertCellOrdered(TCellPointer* root, void * info, CompareFunction cmpFunction)
{
    TCellPointer newCell = (TCellPointer) malloc(sizeof(TCell));

    if(!newCell)
    {
        printf("eroare alocare");
        return 0;
    }
    // Daca e primul element
    if(*root == NULL)
    {
        // creez legaturile aferente
        *root = newCell;
        (*root)->info = info;
        (*root)->next = *root;
        (*root)->previous = *root;
    }
    else
    {
        // caut pozitia
        TCellPointer aux = *root;
        while(cmpFunction(info, aux->info) < 0)
        {
            aux = aux->next;
            if(aux == *root)
            {
                // ultimul element din lista
                TCellPointer end = (*root)->previous;
                end->next = newCell;
                newCell->previous = end;
                (*root)->previous = newCell;
                newCell->next = *root;
                newCell->info = info;
                return 1;
            }
        }
        // fac inserare inainte de aux
        aux->previous->next = newCell;
        newCell->previous = aux->previous;
        newCell->next = aux;
        aux->previous = newCell;
        newCell->info = info;
        if(aux == *root)
            *root = newCell;
    }
    return 1;
}

void DestroyList(TCellPointer* root, FreeInfoFunction freeFunc)
{
    TCellPointer aux = *root, u;

    aux = (*root)->next;
    freeFunc((*root)->info);
    free(*root);

    while(aux != *root)
    {
        u = aux;
        aux = aux->next;
        freeFunc(u->info);
        free(u);
        u = NULL;
    }

    *root = NULL;
}

void EliminateCell(TCellPointer* root, TCellPointer toEliminate, FreeInfoFunction freeFunc)
{
    TCellPointer aux = *root;

    // daca e primul element

    if(*root == toEliminate)
    {
        // daca e singurul element
        if((*root)->next == *root)
        {
            (*root)->next = NULL;
            (*root)->previous = NULL;
            freeFunc((*root)->info);
            free(*root);
            *root = NULL;
        }// nu e singurul element
        else
        {
            *root = (*root)->next;
            (*root)->previous = aux->previous;
            aux->previous->next = *root;
            freeFunc(aux->info);
            free(aux);
            aux = NULL;
            if((*root)->next == NULL)
            {
                (*root)->next = *root;
            }
        }
        return;
    }

    while(aux != toEliminate) // caut elementul ce trebuie eliminat
    {
        aux = aux->next;
    }
    if(aux == *root) 
    {
        (*root) = (*root)->next;
    }
    TCellPointer prev = aux->previous;
    prev->next = aux->next;
    aux->next->previous = prev;
    aux->previous = NULL;
    aux->next = NULL;
    freeFunc(aux->info);
    free(aux);

}
