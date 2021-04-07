/* MIHAILESCU Eduard-Florin - 312CB */
#include "tema1.h"

int bucketSize;

int main(int argc, char *argv[])
{
    if(argc != 4){ // verific nr de parametri introdusi
        printf("Introdu numarul corect de parametri");
        return 1;
    }
    bucketSize = atoi(argv[1]); // extrag nr de bucketuri

    THashTablePointer hashTable = InitialiseHashMap(bucketSize);
    // declarare si intializare fisiere de intrare si iesire
    FILE *inputFile = fopen(argv[2], "r");
    FILE *outputFile = fopen(argv[3], "w");

    // citire linie cu linie
    char *line = NULL;
    size_t length = 0;
    while(getline(&line, &length, inputFile) != -1)
    {
        // se delimiteaza cuvintele cheie si se apeleaza functie corespunzatoare
        char *command = strtok(line, " ");
        if(command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0';

        if(strcmp(command, "put") == 0)
        {
            char *address = strtok(NULL, " ");
            char *ip = strtok(NULL, " ");
            if(ip[strlen(ip) - 1] == '\n')
                ip[strlen(ip) - 1] = '\0';

            Put(hashTable,address,ip);

        }
        else if(strcmp(command, "get") == 0)
        {
            char *address = strtok(NULL, " ");
            if(address[strlen(address) - 1] == '\n')
                address[strlen(address) - 1] = '\0';

            char *toPrint = Get(hashTable,address);
            fprintf(outputFile, "%s\n", toPrint);
            free(toPrint);

        }
        else if(strcmp(command, "remove") == 0)
        {
            char *address = strtok(NULL, " ");
            if(address[strlen(address) - 1] == '\n')
                address[strlen(address) - 1] = '\0'; 

            Remove(hashTable, address);

        }
        else if(strcmp(command, "find") == 0)
        {
            char *address = strtok(NULL, " ");
            if(address[strlen(address) - 1] == '\n')
                address[strlen(address) - 1] = '\0';
            

            char *toPrint = Find(hashTable,address);
            fprintf(outputFile,"%s\n", toPrint);
            free(toPrint);

        }
        else if(strcmp(command, "print") == 0)
        {
            Print(hashTable, outputFile);
        }
        else if(strcmp(command, "print_bucket") == 0)
        {
            char *bucketNumber = strtok(NULL, " ");
            if(bucketNumber[strlen(bucketNumber) - 1] == '\n')
                bucketNumber[strlen(bucketNumber) - 1] = '\0'; 
            
            int bucketIndex = atoi(bucketNumber);
            PrintBucket(bucketIndex, hashTable, outputFile);
        }
        
    }

    // Eliberare memorie
    free(line);
    DestroyHashTable(&hashTable);
    fclose(inputFile);
    fclose(outputFile);
}

char *MyDisplayFunction(void *info)
{
    // Functia de afisare a valorii din structura
    TPairPointer keyValuePair = (TPairPointer) info;
    char *result = malloc(MAX_LENGTH * sizeof(char));
    if(!result)
    {
        printf("eroare alocare");
        return NULL;
    }

    sprintf(result, "%s", keyValuePair->value);
    return result;
}


int Put(THashTablePointer hashTable ,char *address, char *ip)
{
    TPairPointer keyValuePair = (TPairPointer) malloc(sizeof(TPair));
    
    if(keyValuePair == NULL)
    {
        return 0;
    }
    keyValuePair->key = (char *) malloc(strlen(address)+1);
    keyValuePair->value = (char *) malloc(strlen(ip)+1);

    // aloc valorile
    strcpy(keyValuePair->key, address);
    strcpy(keyValuePair->value, ip);


    // apelez insert-ul din fisierul sursa corespunzator tabelei hash
    if(InsertElement(hashTable, keyValuePair) != 1)
    {
        free(keyValuePair->key);
        free(keyValuePair->value);
        free(keyValuePair);
        return 0;
    }

    return 1;
}

char* Find(THashTablePointer hashTable, char *toFind)
{
    // verific daca gasesc elementul cu cheia "toFind"
    char* result = (char *)malloc(MAX_LENGTH);

    if(result == NULL)
    {
        printf("Eroare alocare");
        return NULL;
    }

    if(FindElement(hashTable, toFind) == 1)
    {
        strcpy(result, "True");
    }
    else
        strcpy(result, "False");
    return result;

}

char* Get(THashTablePointer hashTable, char *toGet)
{
    char* result = (char *) malloc(MAX_LENGTH);
    
    if(ExtractElement(hashTable, toGet) == NULL)
    {
        strcpy(result, "NULL");
    }
    else
    {
        strcpy(result, ExtractElement(hashTable, toGet));
    }
}

void Remove(THashTablePointer hashTable, char *toRemove)
{
    DeleteElement(hashTable, toRemove);
}

void Print(THashTablePointer hashMap, FILE* outputFile)
{
    DisplayHashTable(hashMap, outputFile);
}

void PrintBucket(int indexBucket, THashTablePointer hashMap, FILE* outputFile)
{
    int result = DisplayBucket(hashMap, MyDisplayFunction, indexBucket, outputFile);
    if(result == 0)
    {
        fprintf(outputFile ,"VIDA\n");
    }
}

