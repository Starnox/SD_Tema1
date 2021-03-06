/* MIHAILESCU Eduard-Florin - 312CB */
#include <stdio.h>
#include <stdlib.h>

typedef struct cell
{
    void * info;
    struct cell *previous, *next;
} TCell, *TCellPointer;

typedef char* (*DisplayFunction) (void *);
typedef int (*CompareFunction) (void *, void *);
typedef void (*FreeInfoFunction) (void *);

int InsertCellOrdered(TCellPointer*, void *, CompareFunction); // insereaza la finalul listei o noua celula (1/0) reusita
void EliminateCell(TCellPointer*, TCellPointer, FreeInfoFunction);
void DestroyList(TCellPointer*, FreeInfoFunction);

