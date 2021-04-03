#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic_double_list.h"

/* MIHAILESCU Eduard-Florin - 312CB */
#define MAX_LENGTH 1000

typedef int (*THashFunction)(void *);
typedef void (*TFreeInfo)(void *);

typedef struct 
{
    char *key;
    char *value;
}TPair, *TPairPointer;


typedef struct
{
    size_t bucketSize; // numarul de bucketuri
    TCellPointer *buckets; // vector de liste duble inlantuite

}THashTable, *THashTablePointer;

THashTablePointer InitialiseHashMap(int); // initializeaza tabela
void DisplayHashTable(THashTablePointer, FILE*); // afiseaza tabela hash
int DisplayBucket(THashTablePointer, DisplayFunction, int,  FILE*); // (1/0) contine elemente
int InsertElement(THashTablePointer, TPairPointer); // insereaza un element in tabela
int DeleteElement(THashTablePointer, char *); // sterge elementul ce are cheia respectiva
int FindElement(THashTablePointer, char *); // cauta un element
char* ExtractElement(THashTablePointer, char *);// extrage un element
int HashFunction(char *, int bucketSize); // Functia de hash

void DestroyHashTable(THashTablePointer *); // Elibereaza memoria pentru tabela
int MyCompareFunction(void *, void *); // Functia ce compara cheile

void FreePair(void *);