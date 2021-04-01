#include "hashtable.h"

THashTablePointer InitialiseHashMap(int bucketSize)
{
    THashTablePointer hashTable = (THashTablePointer) malloc(sizeof(THashTable));

    if(!hashTable)
    {
        printf("Eroare alocare hash\n");
        return NULL;
    }

    
    hashTable->buckets = (TCellPointer *) calloc(bucketSize, sizeof(TCellPointer));

    if(!hashTable->buckets)
    {
        printf("Eroare alocare vectori de lista");
        free(hashTable);
        return NULL;
    }

    hashTable->bucketSize = bucketSize;

    return hashTable;
}

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
    int code = HashFunction(info->key, hashTable->bucketSize);
    TCellPointer bucket = hashTable->buckets[code];
    TCellPointer element = bucket;
  
    if(!bucket) // primul element din lista
    {
        int result = InsertCellEnd(hashTable->buckets+code, info);
        return result;
    }

    if(strcmp(((TPairPointer)element->info)->key , info->key) == 0)
    {
        return 0;
    }
    for(; element->next != bucket; element = element->next)
    {
        if(strcmp(((TPairPointer)element->next->info)->key , info->key) == 0)
            return 0;
    }
    int result = InsertCellEnd(hashTable->buckets+code, info);
    return result;
}

void DisplayHashTable(THashTablePointer hashTable, DisplayFunction displayFunc, FILE *outputFile)
{
    TCellPointer bucket, element;

    for(int i = 0; i< hashTable->bucketSize; ++i)
    {
        bucket = hashTable->buckets[i];
        if(bucket)// daca bucketul contine ceva
        {
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
        fprintf(outputFile, "%d: ", index);
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
    int code = HashFunction(key, hashTable->bucketSize);
    TCellPointer bucket = hashTable->buckets[code];
    TCellPointer element = bucket;

    if(!bucket)
    {
        return 0;
    }

    if(strcmp(((TPairPointer)element->info)->key, key) == 0)
    {
        EliminateCell(&bucket,bucket, FreePair); // elimina prima celula
        hashTable->buckets[code] = bucket;
        return 1;
    }

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

    if(strcmp(((TPairPointer)element->info)->key, key) == 0)
    {
        return 1;
    }

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
    TCellPointer *p, el, aux;

    for(p = (*hashTable)->buckets; p < (*hashTable)->buckets + (*hashTable)->bucketSize; p++)
    {
        DestroyList(p, FreePair);
    }
    free((*hashTable)->buckets);
    free(*hashTable);
    *hashTable = NULL;
}