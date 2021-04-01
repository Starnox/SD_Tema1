#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic_double_list.h"

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

THashTablePointer InitialiseHashMap(int);
void DisplayHashTable(THashTablePointer, DisplayFunction, FILE*);
int DisplayBucket(THashTablePointer, DisplayFunction, int,  FILE*); // (1/0) contine elemente
int InsertElement(THashTablePointer, TPairPointer);
int DeleteElement(THashTablePointer, char *);
int FindElement(THashTablePointer, char *);
char* ExtractElement(THashTablePointer, char *);
int HashFunction(char *, int bucketSize);

void DestroyHashTable(THashTablePointer *);

void FreePair(void *);