/*
 Qasim Batrawi
 1220204
 sec: 4
 */

#include <stdlib.h>
#include <stdio.h>
#include<string.h>

typedef struct AVLNode AVLNode;

struct AVLNode {
    char word[50] ;
    int frequency ;
    AVLNode *Left;
    AVLNode *Right;
    int Height;
};

AVLNode *MakeEmpty( AVLNode *T ) ;

AVLNode *FindInTree( char str[50] , AVLNode *T ) ;

AVLNode *FindMinInTree( AVLNode *T ) ;

int Height( AVLNode *P ) ;

int Max( int Lhs, int Rhs ) ;

AVLNode *SingleRotateWithLeft( AVLNode *K2 ) ;

AVLNode *SingleRotateWithRight( AVLNode *K1 ) ;

AVLNode *DoubleRotateWithLeft( AVLNode *K3 ) ;

AVLNode *DoubleRotateWithRight( AVLNode *K1 ) ;

AVLNode *InsertToTree(char str[50] , AVLNode *T ) ;

AVLNode *DeleteFromTree(char str[50] , AVLNode *Tree) ;

int numOfNodes(AVLNode *Tree) ;

void PrintInOrder( AVLNode *Tree) ;

typedef struct HashTable HashTable ;

struct HashTable{

    char *Array[100] ; // array of words
    int *frequency ; // array for frequencies
    int tableSize ; // size of the table (prime)
    int emptyCells ; // number of empty cells in the table

};

HashTable *CreateTable(int size) ;

int hash(char str[50] , HashTable *Table) ;

void InsertToHashTable(char str[50] , HashTable *Table) ;

void InsertToHashTableWithFrequency(char str[50] , int frequency , HashTable *Table) ;

int FindInHashTable(char str[50] , HashTable *Table) ;

void RemoveFromTable(int ind , HashTable *Table) ;

int FindNextPrime(int x) ;

void DeleteTable(HashTable *Table) ;

HashTable *updateTable(HashTable *Table) ;

int nearlyFullTable(HashTable *Table) ;

int isAlphaChar(char c) ;

int isAlphaString(char str[50]) ;

char *readInputFile() ;

AVLNode *CreateAVLTree(char str[200] , AVLNode *T) ;

void InsertFromTreeToTable(AVLNode *Tree , HashTable *Table) ;

void displayMenu() ;

void clearBuffer() ;

void thresholdFrequency (int freq , HashTable *Table) ;

void mostFrequent(HashTable *Table) ;

void numOfUnique(HashTable *Table) ;

int main(){

    // declare each struct
    AVLNode *Tree = NULL ;
    HashTable *Table ;
    char *inputFile ;

    int option , loadedFile=0 , createdTree=0 , createdTable=0 ;

    printf("\nWelcome to our program.\n\n") ;
    displayMenu() ;
    printf("\nPlease chose one of the options from 1-11: ") ;
    scanf("%d" , &option) ;
    clearBuffer() ; // we will clear the buffer after each scnaf
    printf("\n") ;

    while (option != 11){
        if (option < 1 || option > 11){
            // undefined option
            printf("The option is not in the menu.\n\n") ;
        }
        else if (option == 1){ // read the file
            if (loadedFile == 1){ // file has been loaded before
                printf("Input file has been loaded recently.\n\n") ;
            }
            else{
                // read the file
                inputFile = readInputFile() ;
                printf("Input file has been loaded.\n\n") ;
                loadedFile = 1 ;
            }
        }
        else if (option == 2){ // create avl tree
            if (!loadedFile){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (createdTree){ // tree has been created before
                printf("AVL Tree has been created recently.\n\n") ;
            }
            else{
                // create the tree
                Tree = CreateAVLTree(inputFile , Tree) ;
                printf("AVL Tree has been created.\n\n") ;
                createdTree = 1 ;
            }
        }
        else if (option == 3){ // insert to avl tree
            if (!loadedFile){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (!createdTree){ // tree is not created
                printf("AVL Tree has not been created yet.\n\n") ;
            }
            else{
                printf("Enter the word you want to insert to the tree: ") ;
                char str[50] ;
                scanf("%s" , str) ; // read the word that we want to insert
                clearBuffer() ; // the user may enter more than one word, so we will take just the first word and clear the buffer from the remaining

                if (isAlphaString(str)){ // str contains only alpha chars, which is ok
                    strlwr(str) ; // convert all letters to small
                    AVLNode *node = FindInTree(str , Tree) ; // search in the tree

                    if (node != NULL){ // the node exist in the tree
                        node->frequency++ ; // update its frequency
                        printf("\n\"%s\" already exist in the tree. Frequency has been updated.\n\n" , str) ;
                    }
                    else{ // we will insert a new node
                        InsertToTree(str , Tree) ;
                        printf("\n\"%s\" has inserted to the tree.\n\n" , str) ;
                    }
                }
                else{ // str contains letters which are not alpha
                    printf("\n\"%s\" does not match the details of the program.\n\n" , str) ;
                }
            }
        }
        else if (option == 4){ // delete from avl tree
            if (!loadedFile){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (!createdTree){ // tree is not created
                printf("AVL Tree has not been created yet.\n\n") ;
            }
            else {
                printf("Enter the word you want to delete from the tree: ");
                char str[50];
                scanf("%s", str); // read the word we want to delete
                clearBuffer();

                if (isAlphaString(str)) { // str contains only alpha chars, which is ok
                    strlwr(str); // convert all letters to small
                    AVLNode *node = FindInTree(str, Tree); // search in the tree

                    if (node != NULL) { // the node is in the tree
                        Tree = DeleteFromTree(str, Tree); // delete it
                        printf("\n\"%s\" has been deleted from the tree.\n\n", str);
                    }
                    else { // the node does not exist
                        printf("\n\"%s\" is not in the tree.\n\n", str);
                    }
                }
                else { // str contains letters which are not alpha
                    printf("\n\"%s\" does not match the details of the program.\n\n" , str) ;
                }
            }
        }
        else if (option == 5){ // print the avl tree
            if (!loadedFile){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (!createdTree){ // tree is not created
                printf("AVL Tree has not been created yet.\n\n") ;
            }
            else{
                printf("The words and their frequency in the AVL tree (in-order): \n\n") ;
                PrintInOrder(Tree) ; // print the words (in-order traversal)(left root right)
                printf("\n\n") ;
            }
        }
        else if (option == 6){ // create hashtable
            if (!loadedFile){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (!createdTree){ // tree is not created
                printf("AVL Tree has not been created yet.\n\n") ;
            }
            else if (createdTable){ // table has been created before
                printf("Hash Table has been created recently.\n\n") ;
            }
            else{
                // create the table
                Table = CreateTable(numOfNodes(Tree)*2) ; // its size depends on the number of nodes in the tree
                InsertFromTreeToTable(Tree , Table) ; // copy the data from tree to hashtable
                printf("HashTable has been created.\n\n") ;
                createdTable = 1 ;
            }
        }
        else if (option == 7){ // insert to hashtable
            if (!loadedFile){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (!createdTable){ // table is not created
                printf("Hash Table has not been created yet.\n\n") ;
            }
            else{
                printf("Enter the word you want to insert to the table: ") ;
                char str[50] ;
                scanf("%s", str) ; // read the word we want to insert
                clearBuffer() ;

                if (isAlphaString(str)){ // the string contains only alpha chars, which is ok

                    if (nearlyFullTable(Table)){
                        // table is nearly full. update the size by creating new table and rehash the data
                        Table = updateTable(Table) ;
                        printf("Table size has been updated.\n") ;
                    }

                    strlwr(str) ; // convert str to small letters
                    InsertToHashTable(str, Table) ; // insert to the table
                }
                else{ // str contains letters which are not alpha
                    printf("\n\"%s\" does not match the details of the program.\n\n" , str) ;
                }
            }
        }
        else if (option == 8){ // delete from table
            if (!loadedFile){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (!createdTable){ // table is not created
                printf("Hash Table has not been created yet.\n\n") ;
            }
            else if (Table->emptyCells == Table->tableSize){ // table is empty. so we will not search for anything
                printf("Table is empty.\n\n") ;
            }
            else{
                printf("Enter the word you want to delete from the table: ") ;
                char str[50] ;
                scanf("%s", str) ; // read the word we want to delete
                clearBuffer() ;

                if (isAlphaString(str)){ // the string contains only alpha chars, which is ok
                    strlwr(str); // convert str to small letters

                    int ind = FindInHashTable(str , Table) ;

                    if (ind == -1){ // str does not exist in the table
                        printf("\n\"%s\" is not in the table.\n\n" , str) ;
                    }
                    else{
                        // remove str from the table. if its frequency is greater than one we will reduce it.
                        RemoveFromTable(ind , Table) ;
                        printf("\n\"%s\" has been removed form the table.\n\n" , str) ;
                    }
                }
                else{ // str contains letters which are not alpha
                    printf("\n\"%s\" does not match the details of the program.\n\n" , str) ;
                }
            }
        }
        else if (option == 9){ // search for a word in the hash table
            if (!loadedFile){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (!createdTable){ // table is not created
                printf("Hash Table has not been created yet.\n\n") ;
            }
            else if (Table->emptyCells == Table->tableSize){ // table is empty. we will not search for anything
                printf("Table is empty.\n\n") ;
            }
            else{
                printf("Enter the word you want to search for it in the table: ") ;
                char str[50] ;
                scanf("%s", str) ; // read the word we want to insert
                clearBuffer() ;

                if (isAlphaString(str)){
                    strlwr(str); // convert to lowercase

                    int ind = FindInHashTable(str , Table) ;

                    if (ind == -1){ // the word does not exist
                        printf("\n\"%s\" is not in the table.\n\n" , str) ;
                    }
                    else{ // print the word and it frequency
                        printf("\n%s: %d\n\n" , Table->Array[ind] , Table->frequency[ind]) ;
                    }
                }
                else{
                    printf("\n\"%s\" does not match the details of the program.\n\n" , str) ;
                }
            }
        }
        else if (option == 10){ // print some statics from the hashtable
            if (!loadedFile){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (!createdTable){ // table is not created
                printf("Hash Table has not been created yet.\n\n") ;
            }
            else if (Table->emptyCells == Table->tableSize){ // the table is empty. no statics
                printf("Table is empty.\n\n") ;
            }
            else{
                int freq ;
                printf("Please enter the threshold of the frequency: ") ;
                scanf("%d" , &freq) ;

                thresholdFrequency(freq , Table) ; // we will search for the words which their frequencies are greater than (freq)
                mostFrequent(Table) ; // we will search for the most frequent words
                numOfUnique(Table) ; // we will count the number of unique words
            }
        }

        displayMenu() ;
        printf("\nPlease chose one of the options from 1-11: ") ;
        scanf("%d" , &option) ;
        clearBuffer() ;
        printf("\n") ;
    }

    printf("Thank you for using our program. Goodbye.\n") ;

    if (loadedFile){
        free(inputFile) ;
    }

    if (createdTable){
        DeleteTable(Table) ;
    }

    MakeEmpty(Tree) ;

    return 0 ;
}

AVLNode *MakeEmpty( AVLNode *T ){
    if( T != NULL ){
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

AVLNode *FindInTree( char str[50] , AVLNode *T ){
    if( T == NULL )
        return NULL;

    int cmp = strcmp(str , T->word) ;

    if(cmp < 0)
        return FindInTree( str, T->Left );

    else if(cmp > 0)
        return FindInTree(str , T->Right );

    else
        return T;
}

AVLNode *FindMinInTree( AVLNode *T ){
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )
        return T;
    else
        return FindMinInTree( T->Left );
}

int Height( AVLNode *Tree ){
    if( Tree == NULL )
        return -1;
    else
        return Tree->Height;
}

int Max(int L , int R){

    return L > R ? L : R ;

}

AVLNode *SingleRotateWithLeft( AVLNode *K2 ){

    // single rotate to right

    AVLNode  *K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1 ;

}

AVLNode *SingleRotateWithRight( AVLNode *K1 ){

    // single rotate to left

    AVLNode *K2;

    K2 = K1->Right;

    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;

}

AVLNode *DoubleRotateWithLeft( AVLNode *K3 ){

    //double rotate, RL

    K3->Left = SingleRotateWithRight( K3->Left );

    return SingleRotateWithLeft( K3 );
}

AVLNode *DoubleRotateWithRight( AVLNode *K1 ){

    //double rotate, LR

    K1->Right = SingleRotateWithLeft( K1->Right );

    return SingleRotateWithRight( K1 );
}

AVLNode *InsertToTree(char str[50] , AVLNode *T ){

    if( T == NULL ){
        // insert new node
        T = (AVLNode*)(malloc(sizeof(AVLNode)));

        if( T == NULL ) {
            printf("Out of space.\n");
        }
        else{
            strcpy(T->word , str) ;
            T->Height = 0 ;
            T->frequency = 1 ;
            T->Left = T->Right = NULL ;
        }
    }
    else if(strcmp(T->word , str) > 0){
        T->Left = InsertToTree( str , T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if(strcmp(T->Left->word , str) > 0)
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
    }
    else if(strcmp(T->word , str) < 0){
        T->Right = InsertToTree( str, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
            if(strcmp(str , T->Right->word) > 0)
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }

    // node exist. we will do nothing
    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;

    return T;
}

AVLNode *DeleteFromTree(char str[50] , AVLNode *Tree){

    if (Tree == NULL){
        printf("The element does not exist.\n") ;
    }
    else if (strcmp(str , Tree->word) > 0){
        Tree->Right = DeleteFromTree(str , Tree->Right) ;
    }
    else if (strcmp(str , Tree->word) < 0){
        Tree->Left = DeleteFromTree(str , Tree->Left) ;
    }
    else{ // the element is found

        // reduce the frequency if it is greater than one. we will not remove the node
        if (Tree->frequency > 1){
            Tree->frequency-- ;
            return Tree ; // the tree will be the same, no change on the balance
        }

        AVLNode *tempCell ;

        if (Tree->Left && Tree->Right){ // it has 2 children

            tempCell = FindMinInTree(Tree->Right) ; // the min in the right subtree will be the new root
            strcpy(Tree->word , tempCell->word) ;
            Tree->frequency = tempCell->frequency ;
            Tree->Right = DeleteFromTree(Tree->word , Tree->Right) ; // delete the new root from the right subtree

        }

        else{ // it has one child or zero

            tempCell = Tree ;

            if (Tree->Left == NULL){
                Tree = Tree->Right ;
            }
            else if (Tree->Right == NULL){
                Tree = Tree->Left ;
            }
            else{
                free(tempCell) ;
                Tree = NULL ;
                return Tree ; // we will not check its balance since it is a leaf node
            }

            free(tempCell) ;

        }

    }

    //now we will check for balance starting from the deleted node, up to the root
    if (Tree != NULL){
        Tree->Height = Max(Height(Tree->Right) , Height(Tree->Left))+1 ;
        int balance = ((Height(Tree->Left) == -1)? 0 : Height(Tree->Left)) - ((Height(Tree->Right) == -1)? 0 : Height(Tree->Right)) ;

        if (balance > 1){
            if(strcmp(Tree->Left->word , str) > 0){
                Tree = SingleRotateWithLeft( Tree ) ;
            }
            else{
                Tree = DoubleRotateWithLeft( Tree ) ;
            }
        }
        else if (balance < -1){
            if(strcmp(Tree->Right->word , str) < 0){
                Tree = SingleRotateWithRight( Tree ) ;
            }
            else{
                Tree = DoubleRotateWithRight( Tree ) ;
            }
        }
    }

    return Tree ;

}

int numOfNodes(AVLNode *Tree){

    if (Tree == NULL){
        return 0 ;
    }
    // count the number of nodes in the tree
    return 1 + numOfNodes(Tree->Right) + numOfNodes(Tree->Left) ;

}

void PrintInOrder( AVLNode *Tree){

    // print the tree in-order traversal(left root right)
    if( Tree != NULL){
        PrintInOrder( Tree->Left ) ;
        printf("%s: %d    ", Tree->word , Tree->frequency) ;
        PrintInOrder( Tree->Right ) ;
    }

}

HashTable *CreateTable(int size){

    int tableSize = FindNextPrime(size+1) ; // the size must be prime

    HashTable *Table = NULL ;

    Table = (HashTable*)(malloc(sizeof(HashTable))) ;

    if (Table == NULL){
        printf("Out of memory.\n") ;
        return NULL ;
    }

    Table->frequency = (int*)(malloc(sizeof(int)*tableSize)) ;

    if (Table->frequency == NULL){
        printf("Out of memory.\n") ;
        return NULL ;
    }

    for (int i = 0 ; i < tableSize ; i++){
        Table->Array[i] = (char*)(malloc(sizeof(char)*50)) ; // 50 char for each string
        Table->frequency[i] = 0 ;
        if (Table->Array[i] == NULL){
            printf("Out of space.\n") ;
            return NULL ;
        }
    }

    Table->tableSize = Table->emptyCells = tableSize ;

    for (int i = 0 ; i < tableSize ; i++){
        strcpy(Table->Array[i] , "EmptyCell") ; // we will know that the cell is empty if its string is "EmptyCell"
    }

    return Table ;

}

int hash(char str[50] , HashTable *Table){

    // get the value of hashing the string
    int hashValue=0 ;

    for (int i = 0 ; str[i] != '\0' ; i++){
        hashValue = ((hashValue << 5) + str[i])%Table->tableSize ;
    }

    return hashValue ;

}

void InsertToHashTable(char str[50] , HashTable *Table){

    // more explanation will be in the discussion

    int hashValue = hash(str , Table) ;

    for (int i = 0 ; i <= Table->tableSize ; i++){

        // we will do quadratic hashing
        int ind = (hashValue + i*i)%Table->tableSize ;

        if (strcmp(Table->Array[ind] , "EmptyCell") == 0){ // empty cell. so we will insert
            strcpy(Table->Array[ind] , str) ;
            Table->emptyCells-- ;
            Table->frequency[ind] = 1 ;
            printf("\n\"%s\" has been inserted to the Hash Table.\n\n" , str) ;
            return ;
        }
        else if (strcmp(Table->Array[ind] , str) == 0){ // the word exist. update the frequency
            Table->frequency[ind]++ ;
            printf("\n\"%s\" is in the Hash Table. Frequency has been updated.\n\n" , str) ;
            return ;
        }
    }

}

void InsertToHashTableWithFrequency(char str[50] , int frequency , HashTable *Table){

    // we will use this function when we create the hashtable. also when the table is nearlyFull

    int hashValue = hash(str , Table) ;

    for (int i = 0 ; i <= Table->tableSize ; i++){

        // we will do quadratic hashing
        int ind = (hashValue + i*i)%Table->tableSize ;

        if (strcmp(Table->Array[ind] , "EmptyCell") == 0){ // empty cell
            strcpy(Table->Array[ind] , str) ;
            Table->emptyCells-- ;
            Table->frequency[ind] = frequency ;
            return ;
        }
    }

}

int FindInHashTable(char str[50] , HashTable *Table){

    // more explanation will be in the discussion

    int hashValue = hash(str , Table) ;

    for (int i = 0 ; i <= Table->tableSize ; i++){

        // we will do quadratic hashing
        int ind = (hashValue + i*i)%Table->tableSize ;

        if(strcmp(Table->Array[ind] , str) == 0){
            return ind ;
        }

    }

    return -1 ;

}

void RemoveFromTable(int ind , HashTable *Table){ // remove from certain index

    // just reduce the frequency if it is greater than one
    if (Table->frequency[ind] > 1){
        Table->frequency[ind]-- ;
        return ;
    }

    strcpy(Table->Array[ind] , "EmptyCell") ;
    Table->frequency[ind] = 0 ;
    Table->emptyCells++ ;

}

int FindNextPrime(int x){

    // find the size of the table

    while (1){

        int isPrime=1 ;

        for (int i = 2 ; i*i <= x ; i++){
            if (x%i == 0){
                isPrime=0 ;
                break ;
            }
        }

        if (isPrime){
            return x ;
        }

        x++ ;
    }

}

void DeleteTable(HashTable *Table){

    for (int i = 0 ; i < Table->tableSize ; i++){
        // free each string
        free(Table->Array[i]) ;
    }

    // free the array of frequency
    free(Table->frequency) ;

    // free the table
    free(Table) ;

}

HashTable *updateTable(HashTable *Table){

    HashTable *newTable = CreateTable(Table->tableSize*2) ;

    for (int i = 0 ; i < Table->tableSize ; i++){
        if (strcmp(Table->Array[i] , "EmptyCell") != 0){ // we will copy this word to the new table by rehashing it.
            InsertToHashTableWithFrequency(Table->Array[i] , Table->frequency[i] , newTable) ;
        }
    }
    printf("\n") ;

    DeleteTable(Table) ;

    return newTable ;

}

int nearlyFullTable(HashTable *Table){

    // we will check if the used cell in the table are more than 65% of its size

    return ((double)(Table->tableSize - Table->emptyCells))/((double)(Table->tableSize)) >= 0.65 ;

}

int isAlphaChar(char c){

    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ;

}

int isAlphaString(char str[50]){

    int strSize = strlen(str) ;

    for (int i = 0 ; i < strSize ; i++){
        if (!isAlphaChar(str[i])){
            return 0 ;
        }
    }

    return 1 ;

}

char *readInputFile(){

    FILE *fp = fopen("input.txt" , "r") ;

    if (fp == NULL){
        printf("Input file does not exist.\n") ;
        return NULL ;
    }

    char temp[100] , *str ; // we will read and save the text in temp. then we will copy the text from temp to str
    str = (char*)(malloc(sizeof(char)*200)) ;

    if (str == NULL){
        fclose(fp) ;
        printf("Out of memory.\n") ;
        return NULL ;
    }
    str[0] = '\0' ;

    while (fgets(temp , sizeof(temp) , fp)){

        char *token = strtok(temp , " ") ;
        while (token != NULL){

            int tokenSize = strlen(token) ;
            if (token[tokenSize-1] == '\n'){
                token[tokenSize-1] = '\0' ;
            }

            if (isAlphaString(token)){
                strlwr(token) ;
                strcat(str , token) ;
                strcat(str , " ") ;
            }
            // we will not read any word which contains letters that are not alpha

            token = strtok(NULL , " ") ;
        }
    }

    fclose(fp) ;

    return str ;

}

AVLNode *CreateAVLTree(char str[200] , AVLNode *T){

    // we will insert the read string from the file to the avl

    char *token = strtok(str , " ") ;

    while (token != NULL){

        AVLNode *temp = FindInTree(token , T) ; // search if token exist or not

        if (temp == NULL){ // insert a new node
            T = InsertToTree(token , T) ;
        }
        else{ // token is already in the tree. update its frequency
            temp->frequency++ ;
        }

        token = strtok(NULL , " ") ;
    }

    return T ;

}

void InsertFromTreeToTable(AVLNode *Tree , HashTable *Table){

    // copy the data from tree to hashtable

    if (Tree != NULL){
        InsertFromTreeToTable(Tree->Left , Table) ;
        InsertToHashTableWithFrequency(Tree->word , Tree->frequency , Table) ;
        InsertFromTreeToTable(Tree->Right , Table) ;
    }

}

void displayMenu(){

    printf("1- Load data from the file.\n"
           "2- Create AVL Tree.\n"
           "3- Insert a word to the AVL Tree.\n"
           "4- Delete a word from the AVL Tree.\n"
           "5- Print the words as sorted in the AVL Tree.\n"
           "6- Create the Hash Table.\n"
           "7- Insert a word to the Hash Table.\n"
           "8- Delete a word from the Hash Table.\n"
           "9- Search for a word in the Hash Table and print its frequency.\n"
           "10- Print words statistics.\n"
           "11- Exit the application.\n") ;

}

void clearBuffer(){

    char c = 'a' ; // any initial value

    while (c != '\n' && c != EOF){ // '\n' means that we have reached the last input. EOF means end of buffer
        c = getchar() ;
    }

}

void thresholdFrequency (int freq , HashTable *Table){

    int print=1 ;
    for (int i = 0 ; i < Table->tableSize ; i++){
        if (Table->frequency[i] > 0 && Table->frequency[i] > freq){
            if (print){
                printf("\nWords that have a frequency greater than %d are: " , freq) ;
                print=0 ;
            }
            printf("%s: %d   " , Table->Array[i] , Table->frequency[i]) ;
        }
    }

    if (print){
        printf("\nThere are no words with frequency greater than %d.\n\n" , freq) ;
    }
    else{
        printf("\n\n") ;
    }

}

void mostFrequent(HashTable *Table){

    printf("The most frequent words are: ") ;

    int max = -1 ;
    for (int i = 0 ; i < Table->tableSize ; i++){
        if (Table->frequency[i] > max){
            max = Table->frequency[i] ;
        }
    }

    for (int i = 0 ; i < Table->tableSize ; i++){
        if (Table->frequency[i] == max){
            printf("%s: %d   " , Table->Array[i] , Table->frequency[i]) ;
        }
    }
    printf("\n\n") ;

}

void numOfUnique(HashTable *Table){

    int num=0 ;
    for (int i = 0 ; i < Table->tableSize ; i++){
        if (Table->frequency[i] == 1){
            num++ ;
        }
    }

    printf("Total number of unique words are %d.\n\n" , num) ;

}
