/* MIHAILESCU Eduard-Florin - 312CB */
#include "hashtable.h"

THashTablePointer InitialiseHashMap(int bucketSize)
{
    // alocare memorie tabela
    THashTablePointer hashTable = (THashTablePointer) malloc(sizeof(THashTable));

    if(!hashTable)
    {
        printf("Eroare alocare hash\n");
        return NULL;
    }

    //alocare memorie pentru fiecare bucket
    hashTable->buckets = (TCellPointer *) calloc(bucketSize, sizeof(TCellPointer));

    if(!hashTable->buckets)
    {
        printf("Eroare alocare vectori de lista");
        free(hashTable);
        return NULL;
    }

    // setare parametru
    hashTable->bucketSize = bucketSize;

    return hashTable;
}

// Functia hash data in enunt
int HashFunction(char *info, int bucketSize)
{
    int sum = 0;
    for(int i = 0; i < strlen(info); ++i)
    {
        sum += (int)info[i];
    }
    return (sum % bucketSize);
}


int InsertElement(THashTablePointer hashTable, TPairPointer info)
{
    // verific codul hash al cheii
    int code = HashFunction(info->key, hashTable->bucketSize);
    TCellPointer bucket = hashTable->buckets[code];
    TCellPointer element = bucket;
  
    if(!bucket) // primul element din lista
    {
        // inserez direct
        int result = InsertCellOrdered(hashTable->buckets+code, info, MyCompareFunction);
        return result;
    }


    // daca nu, verific daca elementul este deja in tabela
    // prima verificare o fac in afara instructiunii repetitive 
    // deoarece lista este circulara
    if(strcmp(((TPairPointer)element->info)->key , info->key) == 0)
    {
        return 0;
    }
    for(; element->next != bucket; element = element->next)
    {
        if(strcmp(((TPairPointer)element->next->info)->key , info->key) == 0)
            return 0;
    }
    // apelez functia de inserare specifica listei dublu inlantuite
    int result = InsertCellOrdered(hashTable->buckets+code, info, MyCompareFunction);
    return result;
}

void DisplayHashTable(THashTablePointer hashTable, FILE *outputFile)
{
    TCellPointer bucket, element;

    // iterez prin fiecare bucket
    for(int i = 0; i< hashTable->bucketSize; ++i)
    {
        bucket = hashTable->buckets[i];
        if(bucket)// daca bucketul contine ceva
        {
            // afisez in formatul specificat
            fprintf(outputFile,"%d: ", i);
            element = bucket;
            fprintf(outputFile,"%s ",((TPairPointer)element->info)->value);
            for(;element->next != bucket; element = element->next)
            {
                fprintf(outputFile,"%s ",
                        ((TPairPointer)element->next->info)->value);
            }
            fprintf(outputFile,"\n");
        }
    }
}

int DisplayBucket(THashTablePointer hashTable, DisplayFunction displayFunc, int index , FILE* outputFile)
{
    TCellPointer bucket = hashTable->buckets[index];
    
    if(bucket) // daca bucketul contine ceva
    {
        TCellPointer element = bucket;
        

        char *toDisplay = displayFunc(element->info);
        fprintf(outputFile, "%s ", toDisplay);
        free(toDisplay);

        for(; element->next != bucket; element = element->next)
        {
            toDisplay = displayFunc(element->next->info);
            fprintf(outputFile, "%s ", toDisplay);
            free(toDisplay);
        }
        fprintf(outputFile, "\n");
    }
    else
    {
        return 0;
    }
    return 1;

}

int DeleteElement(THashTablePointer hashTable, char *key)
{
    // iau codul hash
    int code = HashFunction(key, hashTable->bucketSize);
    TCellPointer bucket = hashTable->buckets[code];
    TCellPointer element = bucket;

    // daca bucketul e gol, elementul nu se afla aici
    if(!bucket)
    {
        return 0;
    }

    // verificare primul element
    if(strcmp(((TPairPointer)element->info)->key, key) == 0)
    {
        EliminateCell(&bucket,bucket, FreePair); // elimina prima celula
        hashTable->buckets[code] = bucket;
        return 1;
    }
    // verificare urmatoarele elemente
    for(; element->next != bucket; element = element->next)
    {
        if(strcmp(((TPairPointer)element->next->info)->key, key) == 0)
        {
            EliminateCell(&bucket, element->next, FreePair);
            hashTable->buckets[code] = bucket;
            return 1;
        }
    }

    return 0; // nu am gasit elementul
}

int FindElement(THashTablePointer hashTable, char *key)
{
    int code = HashFunction(key, hashTable->bucketSize);
    TCellPointer bucket = hashTable->buckets[code];

    if(!bucket)
    {
        return 0;
    }

    TCellPointer element = bucket;

    // verificare primul element
    if(strcmp(((TPairPointer)element->info)->key, key) == 0)
    {
        return 1;
    }

    // verificare urmatoarele elemente
    for(; element->next != bucket; element = element->next)
    {
        if(strcmp(((TPairPointer)element->next->info)->key, key) == 0)
        {
            return 1;
        }
    }
    return 0;
}

char* ExtractElement(THashTablePointer hashTable, char *key)
{
    int code = HashFunction(key, hashTable->bucketSize);
    TCellPointer bucket = hashTable->buckets[code];
    TCellPointer element = bucket;

    if(!bucket)
    {
        return NULL;
    }

    if(strcmp(((TPairPointer)element->info)->key, key) == 0)
    {
        return ((TPairPointer)element->info)->value;
    }

    for(; element->next != bucket; element = element->next)
    {
        if(strcmp(((TPairPointer)element->next->info)->key, key) == 0)
        {
            return ((TPairPointer)element->next->info)->value;
        }
    }
    return NULL;
}

void FreePair(void * info)
{
    // Eliberare memorie pentru o structura de tip TPairPointer
    TPairPointer pair = (TPairPointer) info;
    free(pair->key);
    free(pair->value);
    pair->key = NULL;
    pair->value = NULL;
    free(pair);
    pair = NULL;
}

void DestroyHashTable(THashTablePointer * hashTable)
{
    // Eliberare memorie pentru tabela hash
    TCellPointer *p, el, aux;

    // pentru fiecare bucket
    for(p = (*hashTable)->buckets; p < (*hashTable)->buckets + (*hashTable)->bucketSize; p++)
    {
        if(*p)
            DestroyList(p, FreePair); // eliberez lista aferenta bucketului
    }
    free((*hashTable)->buckets);
    free(*hashTable);
    *hashTable = NULL;
}

int MyCompareFunction(void * a, void * b)
{
    // functia de comparare a cheilor
    TPairPointer x = (TPairPointer) a;
    TPairPointer y = (TPairPointer) b;

    return strcmp(y->key, x->key);
}