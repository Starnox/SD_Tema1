# Tema 1 SD
## Elev: Mihailescu Eduard-Florin
## Grupa: 312CB

### Descriere generala
Codul a fost impartit in 3 fisiere sursa si 3 fisiere header aferente.
Astfel in 'tema1.c' se afla functia `main()` si reprezinta punctul de plecare al programului.
In fisierul 'hashtable.c' este implementata tabela hash care apeleaza functii
din fisierul 'generic_double_list.c' care contine functiile de gestionare 
a listelor generice dublu inlantuite circulare

### Functia main
*   `main()` - se realizeaza parsarea datelor de intrare si se apeleaza functiile de baza
corespunzatoare comenzilor din fisierul de intrare

### Functii din tema1.c
*   `int Put(THashTablePointer hashTable ,char *address, char *ip)` - plaseaza in structura hashTable, perechea {address,ip},
apeland functia `InsertElement()` din 'hashtable.c'. 

*   `char* Find(THashTablePointer hashTable, char *toFind)` 
- Verifica daca in `hashTable` se regaseste key-ul 'toFind'
apeland functia `FindElement()`

*   `char* Get(THashTablePointer hashTable, char *toGet)` - functia returneaza valoarea corespunzatoare key-ului dat prin
parametrul `toGet` -> apeleaza `ExtractElement()`

*   `void Remove(THashTablePointer hashTable, char *toRemove)`
- sterge elementul cu key-ul `toRemove` din tabela hash ->
apeleaza `DeleteElement()`

*   `void Print(THashTablePointer hashMap, FILE* outputFile)`
- afiseaza tabela hash -> apeleaza `DisplayHashTable()`

*   `void PrintBucket(int indexBucket, THashTablePointer hashMap, FILE* outputFile)` - afiseaza un singur bucket din tabela hash -> apeleaza `DisplayBucket()`

### Implementarea Structurilor
A fost realizata comform laboratoarelor la care s-a adaugat lista dubla inlantuita circulara. In mod notabil, functiile ce au prezentat o dificultate mai ridicata au fost functiile de insertie si de stergere
a elementelor dintr-o lista, deoarece apar mai multe cazuri particulare.

### Functia de inserare element
*   `int InsertCellOrdered(TCellPointer* root, void * info, CompareFunction cmpFunction)` - se verifica initial daca lista primita este goala, iar in caz afirmativ se creeaza cele 2 legaturi necesare(elementul pointeaza catre sine si pe cale "ascendenta" si pe cale "descendenta") si se actualizeaza inceputul listei `root`, care a fost transmis sub forma unui dublu pointer.
In caz contrar, se cauta in lista pozitia corecta a elementului folosind functia de comparare. In acest caz, mai intervin 3 situatii:
- elementul trebuie introdus la inceput, caz in care se modifica si inceputul liste
- elementul trebuie introdus la sfarsit
- elementul este introdus oriunde altundeva in lista.
Fiecare caz este tratat separat

### Functia de eliminare element
*   `void EliminateCell(TCellPointer* root, TCellPointer toEliminate, FreeInfoFunction freeFunc)` - se verifica in primul rand daca elementul ce trebuie eliminat este inceputul listei. In caz afirmativ, acesta 
trebuie inlocuit cu urmatorul element si refacute legaturile. In caz contrar, se cauta in lista pana se ajunge la elementul trimis, se produc schimbarile de legaturi si se elibereaza memeoria in ordinea in care a fost alocata (mai intai informatia din celula prin functia `freeFunc()`, dupa care celula in sine cu `free()`)







