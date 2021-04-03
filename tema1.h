/* MIHAILESCU Eduard-Florin - 312CB */
#include <string.h>
#include "hashtable.h"


int Put(THashTablePointer, char *, char *); // (1/0) reusita
char* Find(THashTablePointer, char *); 
char* Get(THashTablePointer, char *);
void Remove(THashTablePointer, char *);
void Print(THashTablePointer, FILE*);
void PrintBucket(int indexBucket, THashTablePointer, FILE*);

void MyDisplayAddressAndIp();

