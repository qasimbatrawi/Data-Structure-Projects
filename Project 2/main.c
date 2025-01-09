/*
    Qasim Batrawi
    1220204
    section: 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////**************************************Global*********************************************////

char *Text ; // a global array of characters which represents the array that we will save the words in it
int textSize ; // size of this array

////**********************************************STACK**************************************////

typedef struct Stack Stack ;
typedef struct Stack PtrToNode ;

struct Stack{

    char Word[50] ;
    char Operation[10] ; // insert or remove
    int Index ;
    int Type ; // if 1 then it's a word(so we will remove or insert a space), if 2 then it's a char(so we will not remove or insert space)
    PtrToNode *Next ;

};

int IsEmptyStack(Stack *S);

void Pop(Stack *S);

void MakeEmptyStack(Stack *S);

Stack *CreateStack(); // declare stack

void Push(char word[] , char operation[] , int index , int type , Stack *S);

char *TopOperation(Stack *S); // return the name of the operation from the top of the stack

char *TopWord(Stack *S); // return the inserted or removed word from the top of the stack

int TopIndex(Stack *S); // return the index of the word from the top of the stack

int TopType(Stack *S); // return the name of the operation from the top of the stack

void DisposeStack(Stack *S); // free nodes and free the head

Stack *copyStack(Stack *S); // create a copy stack from stack S

////**********************************************QUEUE*****************************************////

#define MinQueueSize 2 // minimum possible size for the Queue

typedef struct QueueRecord Queue ;

struct QueueRecord{

    int Capacity ;
    int Front ;
    int Rear ;
    int Size ;
    char *Word[30] ; // array of strings

};

int IsEmptyQueue(Queue *Q);

void MakeEmptyQueue (Queue *Q);

Queue *CreateQueue (int MaxWords);

void DisposeQueue(Queue *Q);

int succ(int value , Queue *Q);

void Enqueue (char word[] , Queue *Q);

char *FrontAndDequeue(Queue *Q);

////***********************************************************************************************************************////

int isPunctual(char c); // check if the character is punctual or not

void readInputFile(); // load the input file and insert to Text(global)

char *declareText(int size , char *text); // we will use it while declaring an array of characters

int FindText(char word[]); // check if "word" is a substring of the Text(global) and return its index if exist

int FindCharsInWord(char word[] , char letters[]); // check if letters is a substring of word

void StringToUndoStack(char text[] , int index , int type , Stack *UndoStack); // we will use it when we remove a text in the menu

void StringToQueue(char text[] , Queue *Q); // split the text and enqueue to Q

void shiftTextToRight(int wordLength , int index); // shift the Text to write starting by "wordLength" bits starting from "index"

void RemoveWordAfter(int index , int wordLength); // remove a text with its previous space

void RemoveWordFirst(int index , int wordLength); // remove the first word in the Text with its next space(if exist).

void RemoveChar(int index , int wordLength); // remove chars from some word without any space

void InsertWordToText(char word[] , int wordLength , int index); // insert a word to the text with spaces

void InsertWordAfter(char text[] , int index , Queue *Q , Stack *UndoStack); // enqueue to Q & push to stack & insert to text.

void InsertWordFirst(char text[] , int index , Queue *Q , Stack *UndoStack); // enqueue to Q & push to stack & insert to text.

void InsertWordLast(char text[] , int index , Queue *Q , Stack *UndoStack); // enqueue to Q & push to stack & insert to text.

void InsertChar(char text[] , int index , Queue *Q , Stack *UndoStack); // insert chars for some word without any space(enqueue to Q then push to Undo the insert to text)

void UndoOperation(Stack *UndoStack , Stack *RedoStack); // to perform undo operation

void RedoOperation(Stack *UndoStack , Stack *RedoStack); // to perform redo operation

void printUndoRedoStacks(Stack *UndoStack , Stack *RedoStack); // printStacks

void displayMenu(); // print program menu

void displayInsertList(); // print insert menu

void displayRemoveList(); // print remove menu

void SaveToOutputFile(); // save the Text to the output file.

////**************************************************************main & functions***************************************************////

int main(){

    Text = declareText(1000 , Text) ; // initialize the global Text. array of 1000 character
    textSize = 0 ;
    Text[textSize] = '\0' ;

    char tempText[100] ; //this will save the initial text to use it in option 2 in the menu

    Queue *Q = CreateQueue(30) ; // declare Q. array of string (30 string)
    Stack *UndoStack = CreateStack() , *RedoStack = CreateStack() ; // declare stacks

    // option is to choose one of the options in the menu. loaded to check if the input file has been loaded before.
    int option , loaded=0 ;

    printf("Welcome to our program.\n\n") ;
    displayMenu() ;
    printf("Please chose one of the options from 1-9: ") ;
    scanf("%d" , &option) ;
    getchar() ; // to clear the buffer from '\n'. we will clear the buffer after each scanf
    printf("\n") ;

    while (option != 9){
        if (option < 1 || option > 9){
            printf("The option is not in the menu.\n\n") ;
        }
        else if (option == 1){ // load the file
            if (loaded){ // file has been loaded before
                printf("Input file has been loaded recently.\n\n") ;
            }
            else{
                readInputFile() ; // load the input file and insert it to text
                loaded = 1 ; // file is loaded now
                printf("Input file has been loaded.\n\n") ;
                strcpy(tempText , Text) ; // copy the initial Text to a tempText.
            }
        }
        else if (option == 2){ // print the loaded text
            if (!loaded){
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else{ // print the initial text that was loaded from the file.
                printf("%s\n\n" , tempText) ;
            }
        }
        else if (option == 3){ // insert to text
            if (!loaded){
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (textSize == 0){ // if the text is empty, then we will insert last
                char str[100] , temp[100] ; // temp will save the str before strtok
                printf("Please enter the text you want to insert: ") ;
                gets(str) ;
                strcpy(temp , str) ; // copy str to temp
                InsertWordLast(str , -1 , Q , UndoStack) ; // insert last to text
                printf("\n\"%s\" has been inserted to the text.\n\n" , temp) ; // print the inserted text
                printf("Text: \"%s\"\n\n" , Text) ; // print the updated text.
                MakeEmptyStack(RedoStack) ; // clear the redo stack.
                // we will clear the redo stack after each insert or remove operation
            }
            else{
                int choose; // choose one of  the insert options
                displayInsertList(); // insert list
                printf("\nChoose one of the insert options above from 1-4: ");
                scanf("%d", &choose);
                getchar();
                printf("\n");

                if (choose < 1 || choose > 4) {
                    printf("The option is not in the Insert list.\n\n");
                }
                else if (choose == 1) { // insert first
                    char str[100], temp[100]; // temp will save str before strtok

                    printf("Please enter the string you want to insert at the beginning of the text: ");
                    gets(str);
                    strcpy(temp, str); // copy str to temp

                    InsertWordFirst(str, 1, Q, UndoStack); // insert the word at the beginning

                    printf("\n\"%s\" has been inserted at the beginning of the text.\n\n", temp);
                    printf("Text: \"%s\"\n\n" , Text) ; // print the updated Text

                    MakeEmptyStack(RedoStack); // clear redo stack
                }
                else if (choose == 2) { // insert after
                    char word[100];
                    printf("Please enter the word that you want to insert after it: ");
                    gets(word);
                    int index = FindText(word);
                    // check if word is a substring
                    if (index == -1) { // the word does not exist
                        printf("\n\"%s\" is not in the text.\n\n", word);
                    }
                    else { // word is found
                        char str[100], temp[100];
                        printf("Please enter the string you want to insert after \"%s\": ", word);
                        gets(str);
                        strcpy(temp, str);

                        index = index + strlen(word); // to get the exact index of the word we want to insert
                        if (index == textSize + 1) { // if str is the last word in Text, we will insert last
                            InsertWordLast(str, -1, Q, UndoStack); // insert last
                        }
                        else {
                            InsertWordAfter(str, index , Q, UndoStack); // insert at index
                        }

                        printf("\n\"%s\" has been inserted after \"%s\".\n\n", temp, word);
                        printf("Text: \"%s\"\n\n" , Text) ; // print the updated Text
                        MakeEmptyStack(RedoStack); // clear the redo stack
                    }
                }
                else if (choose == 3) { // insert characters at the beginning of some word
                    char str[50];
                    printf("Enter the word you want to insert characters at the beginning of it: ");
                    gets(str);

                    int index = FindText(str);

                    if (index == -1) { // str does not exist in Text
                        printf("\"%s\" is not in the text.\n\n", str);
                    }
                    else {
                        char letters[50]; // the characters we want to add at the beginning of str
                        printf("Enter the characters you want to insert at the beginning of \"%s\": ", str);
                        gets(letters);

                        InsertChar(letters, index, Q, UndoStack); // insert the characters ate the beginning of str

                        printf("\n\"%s\" has been inserted at the beginning of \"%s\".\n\n" , letters , str) ;
                        printf("Text: \"%s\"\n\n" , Text) ; // print the updated Text
                        MakeEmptyStack(RedoStack); // clear the redo stack
                    }
                }
                else { // insert characters for some word(not at the beginning)
                    char str[50];
                    printf("Enter the word you want to insert characters for it: ");
                    gets(str);

                    int index = FindText(str);
                    // check if str is a substring
                    if (index == -1) { // str does not exist in Text
                        printf("\"%s\" is not in the text.\n\n", str);
                    }
                    else { // str is a substring
                        char c[30] ; // c are the characters in str that we will insert after it
                        printf("Enter the characters you want to insert after it in \"%s\": ", str);
                        gets(c);

                        int pos = FindCharsInWord(str, c); // pos will be the index of c in str

                        if (pos == -1) { // c does not exist in str
                            printf("\n\"%s\" does not exist in \"%s\".\n\n", c, str);
                        }
                        else {
                            char letters[30]; // letters we want to insert after c in str
                            printf("Enter the characters you want to insert after \"%s\" in \"%s\": ", c, str);
                            gets(letters);

                            InsertChar(letters, index - 1 + pos + strlen(c), Q, UndoStack); // insert the letters after c in str

                            printf("\n\"%s\" has been inserted after \"%s\" in \"%s\".\n\n" , letters , c , str) ;
                            printf("Text: \"%s\"\n\n" , Text) ; // print the updated Text.
                            MakeEmptyStack(RedoStack); // clear redo stack
                        }
                    }
                }
            }
        }
        else if (option == 4){ // remove from Text.
            if (!loaded){
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (textSize == 0){ // we will not ask the user to remove some word if the text is empty
                printf("Text is empty. There is nothing to remove.\n\n") ;
            }
            else{
                int choose ; // choose one of the remove options
                displayRemoveList() ; // display the remove list
                printf("\nChoose one of the remove options above from 1-2: ") ;
                scanf("%d" , &choose) ;
                getchar() ;

                if (choose < 1 || choose > 2){
                    printf("The option is not in the remove list.\n\n") ;
                }

                else if (choose == 1){ // remove text(type 1).
                    char str[100], temp[100]; // str is the text that we want to remove, temp will be the same as text before strtok
                    printf("Please enter the string you want to remove from the text: ");
                    gets(str);
                    strcpy(temp, str); // copy str to temp

                    int index = FindText(str) ;

                    if (index == -1){ // the text does not exist
                        printf("\n\"%s\" is not in the text.\n\n", str);
                    }
                    else{
                        if (index == 1){ // if the text is at the beginning of the Text
                            RemoveWordFirst(index , strlen(str)) ;
                        }
                        else{
                            RemoveWordAfter(index , strlen(str)) ;
                        }
                        StringToUndoStack(str , index , 1 , UndoStack) ; // split the string and push it to the undo stack

                        printf("\n\"%s\" has been removed from the text.\n\n", temp);
                        printf("Text: \"%s\"\n\n" , Text) ; // print the updated Text
                        MakeEmptyStack(RedoStack); // clear the redo stack
                    }
                }
                else{ // choose 2. remove characters from some word.(type 2)
                    char str[50];
                    printf("Enter the word you want to remove characters from it: ");
                    gets(str);

                    int index = FindText(str);
                    // check if the str is a substring
                    if (index == -1){ // str does not exist.
                        printf("\n\"%s\" is not in the text.\n\n", str);
                    }
                    else{
                        char letters[30];
                        printf("Enter the characters you want to remove from \"%s\": ", str);
                        gets(letters);

                        int pos = FindCharsInWord(str, letters);

                        if (pos == -1){ // the characters are not found in str
                            printf("\n\"%s\" does not exist in \"%s\".\n\n", letters, str);
                        }
                        else{
                            if (strcmp(letters , str) == 0){ // the characters that we want to remove are all the characters of str. ex: remove "Hello" from "Hello". here we will remove a complete word
                                if (index == 1){ // if the characters are at the beginning of str
                                    RemoveWordFirst(index , strlen(str)) ;
                                }
                                else{
                                    RemoveWordAfter(index , strlen(str)) ;
                                }
                                StringToUndoStack(letters , index , 1 , UndoStack) ; // push the letters to the undo

                                printf("\n\"%s\" has been removed from the text.\n\n" , str) ;
                                printf("Text: \"%s\"\n\n", Text) ; // print the updated Text
                                MakeEmptyStack(RedoStack); // clear the redo stack
                            }
                            else{ // remove some characters from str
                                RemoveChar(pos+index-1 , strlen(letters)) ;
                                StringToUndoStack(letters , pos+index-1 , 2 , UndoStack) ;

                                printf("\n\"%s\" has been removed from \"%s\".\n\n" , letters , str) ;
                                printf("Text: \"%s\"\n\n" , Text) ; // print the updated Text
                                MakeEmptyStack(RedoStack); // clear the redo stack
                            }
                        }
                    }
                }
            }
        }
        else if (option == 5){ // perform undo
            if (!loaded){
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (IsEmptyStack(UndoStack)){ // the undo stack is empty
                printf("Cant perform undo operation.\n\n") ;
            }
            else{
                UndoOperation(UndoStack , RedoStack) ;
                printf("Undo has been performed. Text has been updated.\n\n") ;
                printf("Text: \"%s\"\n\n" , Text) ; // print the updated Text
            }
        }
        else if (option == 6){ // perform redo
            if (!loaded){
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (IsEmptyStack(RedoStack)){ // redo is empty
                printf("Cant perform redo operation.\n\n") ;
            }
            else{
                RedoOperation(UndoStack , RedoStack) ;
                printf("Redo has been performed. Text has been updated.\n\n") ;
                printf("Text: \"%s\"\n\n" , Text) ; // print the updated Text
            }
        }
        else if (option == 7){ // print undo redo stacks
            if (!loaded){
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else {
                printUndoRedoStacks(UndoStack, RedoStack) ;
            }
        }
        else{ // option 8. save Text to file
            if (!loaded){
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else {
                // save to output file and clear both stacks
                SaveToOutputFile() ;
                MakeEmptyStack(UndoStack) ;
                MakeEmptyStack(RedoStack) ;
            }
        }

        displayMenu() ;
        printf("Please chose one of the options from 1-9: ") ;
        scanf("%d" , &option) ;
        getchar() ;
        printf("\n") ;
    }

    SaveToOutputFile() ; // auto save when exit

    printf("Thank you for using our program. Goodbye.\n") ;

    // free everything
    free(Text) ;
    DisposeQueue(Q) ;
    DisposeStack(UndoStack) ;
    DisposeStack(RedoStack) ;

}

int IsEmptyStack(Stack *S){

    return S->Next == NULL ;

}

void Pop(Stack *S){

    if (IsEmptyStack(S)){
        printf("Empty Stack\n") ;
    }
    else{
        PtrToNode *firstCell = S->Next ;
        S->Next = S->Next->Next ;
        free(firstCell) ;
    }

}

void MakeEmptyStack(Stack *S){

    while (!IsEmptyStack(S)){
        Pop(S) ;
    }

}

Stack *CreateStack(){

    Stack *S = NULL ;

    S = (Stack*)(malloc(sizeof(Stack))) ;

    if (S == NULL){
        printf("Out of memory!\n") ;
    }
    else{
        S->Next = NULL ;
        MakeEmptyStack(S) ;
    }

    return S ;

}

void Push(char word[] , char operation[] , int index , int type , Stack *S){

    PtrToNode *temp = (Stack*)(malloc(sizeof(Stack))) ;

    if (temp == NULL){
        printf("Out of memory\n") ;
    }
    else{
        strcpy(temp->Word , word) ;
        strcpy(temp->Operation , operation) ;
        temp->Index = index ;
        temp->Type = type ;
        temp->Next = S->Next ;
        S->Next = temp ;
    }
}

char *TopOperation(Stack *S){

    if (IsEmptyStack(S)){
        printf("Empty Stack\n") ;
        return NULL ;
    }

    return S->Next->Operation ;

}

char *TopWord(Stack *S){

    if (IsEmptyStack(S)){
        printf("Empty Stack\n") ;
        return NULL ;
    }

    return S->Next->Word ;

}

int TopIndex(Stack *S){

    if (IsEmptyStack(S)){
        printf("Empty Stack\n") ;
        return -99 ;
    }

    return S->Next->Index ;

}

int TopType(Stack *S){

    if (IsEmptyStack(S)){
        printf("Empty Stack\n") ;
        return -99 ;
    }

    return S->Next->Type ;

}

void DisposeStack(Stack *S){

    MakeEmptyStack(S) ;
    free(S) ;

}

Stack *copyStack(Stack *S){
    // tempStack to save the data of Stack S
    Stack *tempStack = CreateStack() , *CopyStack = CreateStack() ;

    while (!IsEmptyStack(S)){
        Push(TopWord(S) , TopOperation(S) , TopIndex(S) , TopType(S) , tempStack) ; // it will save the nodes reversely
        Pop(S) ;
    }
    // reverse the nodes in the tempStack and save it in the copStack
    while (!IsEmptyStack(tempStack)){
        Push(TopWord(tempStack) , TopOperation(tempStack) , TopIndex(tempStack) , TopType(tempStack) , S) ;
        Push(TopWord(tempStack) , TopOperation(tempStack) , TopIndex(tempStack) , TopType(tempStack) , CopyStack) ;
        Pop(tempStack) ;
    }

    return CopyStack ;

}

int IsEmptyQueue(Queue *Q){

    return Q->Size == 0 ;

}

void MakeEmptyQueue (Queue *Q){

    Q->Rear = 0 ;
    Q->Front = 1 ;
    Q->Size = 0 ;

}

Queue *CreateQueue (int MaxWords){

    if (MaxWords < MinQueueSize){
        printf("Queue size is too small!\n") ;
        return NULL ;
    }

    Queue *Q = NULL ;

    Q = (Queue*)(malloc(sizeof(Queue))) ;

    if (Q == NULL){
        printf("Out of memory!\n") ;
        return NULL ;
    }

    for (int i = 0 ; i < MaxWords ; i++){
        Q->Word[i] = (char*)(malloc(sizeof(char)*50)) ; // each string have at most 50 character.
        if (Q->Word[i] == NULL){
            printf("Out of memory!\n") ;
            return NULL ;
        }
    }

    Q->Capacity = MaxWords ;
    MakeEmptyQueue(Q) ;

    return Q ;

}

void DisposeQueue(Queue *Q){

    if (Q != NULL){
        for (int i = 0 ; i < Q->Capacity ; i++){
            free(Q->Word[i]) ; // free each string
        }
        free(Q) ;
    }

}

int succ(int value , Queue *Q){

    if (++value == Q->Capacity){
        value=0 ;
    }

    return value ;

}

void Enqueue (char word[] , Queue *Q){

    if (Q->Size == Q->Capacity){
        printf("Full Queue.\n") ;
    }
    else{
        Q->Size++ ;
        Q->Rear = succ(Q->Rear , Q) ;
        strcpy(Q->Word[Q->Rear] , word)  ;
    }

}

char *FrontAndDequeue(Queue *Q){

    if (IsEmptyQueue(Q)){
        printf("Empty Queue\n") ;
        return NULL ;
    }

    Q->Size-- ;
    char *Front = Q->Word[Q->Front] ;
    Q->Front = succ(Q->Front , Q) ;

    return Front ; // we will free the elements when we dispose the queue at the end of the program

}

int isPunctual(char c){

    return c == '.' || c == ',' || c == '!' || c == '?' || c == ':' || c == ';' ;

}

void readInputFile(){

    FILE *fp = fopen("InputFile.txt" , "r") ;

    if (fp == NULL){
        printf("File does not exist.\n\n") ;
        return ;
    }

    char str[1000] ;
    while (fgets(str , sizeof(str) , fp)){

        int lengthOfStr = strlen(str) ;

        if (str[lengthOfStr-1] == '\n'){ // the last char maybe '\n' so we will set it to null
            str[lengthOfStr-1] = '\0' ;
            lengthOfStr-- ;
        }

        strcat(Text , str) ;
        textSize+=lengthOfStr ;

        Text[textSize++] = ' ' ; // the file may have more than one line, so we will merge these lines and insert spaces between them
        Text[textSize] = '\0' ;
    }

    if (textSize > 0){ // remove the last space
        Text[--textSize] = '\0' ;
    }

    fclose(fp) ;

}

char *declareText(int size , char *text){

    text = (char*)(malloc(sizeof(char)*size)) ; // size is the maximum number of characters for the Text

    if (text == NULL) {
        printf("Out of memory.\n");
    }

    return text ;

}

int FindText(char word[]){

    int wordLength = strlen(word) ;

    // initialize two pointers
    int front=0 , back=wordLength-1 ;

    // loop through the Text
    while (back < textSize){
        // check if the first and last char of word are the same as the two chars of the pointers
        if (Text[front] == word[0] && Text[back] == word[wordLength-1]){
            char temp[wordLength+1] ;
            strncpy(temp , Text+front , wordLength) ; // copy the substring to the temp
            temp[wordLength] = '\0' ;
            if (strcmp(temp , word) == 0){ // check if temp is the same as the word
                return front+1 ; // return the position of the first char
            }
        }

        back++ ; front++ ;
    }

    return -1 ; // return -1 if the word is not a substring

}

int FindCharsInWord(char word[] , char letters[]){

    int wordLength=strlen(word) , lettersSize = strlen(letters) ;
    // two pointers
    int i=0 , j=lettersSize-1 ;

    // loop through the word
    while (j < wordLength){
        if (word[i] == letters[0] && word[j] == letters[lettersSize-1]){
            char temp[lettersSize+1] ;
            strncpy(temp , word+(i) , lettersSize) ;
            temp[lettersSize] = '\0' ;
            if (strcmp(temp , letters) == 0){
                return i+1 ;
            }
        }
        i++ ; j++ ;
    }

    return -1 ;

}

void StringToUndoStack(char text[] , int index , int type , Stack *UndoStack){
    // this function is used when removing a text
    if (type == 2){
        // the text will only be one word(without spaces) which contains the characters of some word.
        Push(text , "Remove" , index , type , UndoStack) ;
        return ;
    }

    char *token = strtok(text , " ") ;
    Stack *tempStack = CreateStack() ; // tempStack which will be used to save the words (nodes will be in reverse here)

    // split the text and push each string to a tempStack
    while (token != NULL){
        Push(token , "Remove" , index , type , tempStack) ;
        if (index != -1){
            index+=(strlen(token))+1 ; // update the index to the next word.(+1 for the added space)
        }
        token = strtok(NULL , " ") ;
    }

    // reverse the elements in the tempStack by pushing its element to another stack
    while (!IsEmptyStack(tempStack)){
        Push(TopWord(tempStack) , "Remove" , TopIndex(tempStack) , type , UndoStack) ;
        Pop(tempStack) ;
    }

    DisposeStack(tempStack) ;

}

void StringToQueue(char text[] , Queue *Q){

    // split the string and enqueue each word to the queue
    char *token = strtok(text , " ") ;
    while (token != NULL){
        Enqueue(token , Q) ;
        token = strtok(NULL , " ") ;
    }

}

void shiftTextToRight(int wordLength , int index){

    // shift the text to the right based on "wordLength". start shifting from "index".
    for (int i = textSize ; i >= index-1 ; i--){
        Text[i+wordLength] = Text[i] ;
    }

    textSize+=(wordLength) ;

}

void RemoveWordAfter(int index , int wordLength){ // the index of the first char of the word.

    // remove a text starting from "index" to "index+wordLength".
    int start = index-2 ;
    textSize-=(wordLength+1) ; // +1 for the deleted previous space.

    for (int i = (index-2)+wordLength+1 ; Text[i] != '\0' ; i++){
        Text[start++] = Text[i] ; // shift Text left.
    }

    Text[textSize] = '\0' ;

}

void RemoveWordFirst(int index , int wordLength){

    int start=0 , i ;

    // check if the first char after the word we want to delete is space or not
    if (Text[index+wordLength-1] != ' '){
        // we will not remove this char since it's not a space
        i = index+wordLength-1 ;
        textSize-=(wordLength) ;
    }
    else{
        // remove the next space
        i = index+wordLength ;
        textSize-=(wordLength+1) ;
    }

    while (Text[i] != '\0'){
        Text[start++] = Text[i++] ; // shift Text left.
    }

    Text[textSize] = '\0' ;

}

void RemoveChar(int index , int wordLength){

    // remove characters starting from "index" to "index+wordLength". without removing any next or previous space
    for (int i = index-1 , j = (index-1)+wordLength ; j < textSize ; i++ , j++){
        Text[i] = Text[j] ; // shift Text left
    }

    textSize-=wordLength ;

    Text[textSize] = '\0' ;

}

void InsertWordToText(char word[] , int wordLength , int index){

    // insert "word" to Text, starting from "index".
    // we must shift the Text right before calling this function
    for (int i=index-1 , j=0 ; j < wordLength ; j++ , i++){
        Text[i] = word[j] ;
    }

}

void InsertWordAfter(char text[] , int index , Queue *Q , Stack *UndoStack){ // insert to the queue then to the undo stack and to the text.

    StringToQueue(text , Q) ; // enqueue the text to Q

    //dequeue from queue and push to the UndoStack and insert to text.
    int QSize = Q->Size ;
    for (int i = 0 ; i < QSize ; i++){
        char str[50] ; strcpy(str , FrontAndDequeue(Q)) ; // get the first dequeue word
        Push(str , "Insert" , index+1 , 1 , UndoStack) ; // +1 to get the exact index of the word.

        int strLength = strlen(str) ;

        // Text[index-1] will be the previous char of the inserted text.
        if (!isPunctual(Text[index-1])){
            // Text[index-1] is a space
            shiftTextToRight(strLength+1 , index+1) ; // start shifting from Text[index] so we will keep the previous space
            InsertWordToText(str , strLength , index+1) ;
            Text[index+strLength] = ' ' ; // add space after the inserted text
        }
        else{
            shiftTextToRight(strLength+1 , index) ; // // start shifting from Text[index-1] so we will also shift the punctual mark
            InsertWordToText(str , strLength , index+1) ;
            Text[index-1] = ' ' ; // add space before the inserted text
        }

        index+=(strLength+1) ; // +1 for the added space

    }


}

void InsertWordFirst(char text[] , int index , Queue *Q , Stack *UndoStack){ // index=1 .

    StringToQueue(text , Q) ;

    int QSize = Q->Size ;

    for (int i = 0 ; i < QSize ; i++){
        char str[50] ; strcpy(str , FrontAndDequeue(Q)) ;
        Push(str , "Insert" , index , 1 , UndoStack) ;
        int strLength = strlen(str) ;

        if (i == QSize-1 && isPunctual(Text[index-1])){ // we will not add space if the last char is punctual
            // ex: the Text = ". my name is qasim.", insert first: "Hello everyone"
            shiftTextToRight(strLength , index) ;

            InsertWordToText(str , strLength , index) ;
        }
        else{
            shiftTextToRight(strLength+1 , index) ;

            InsertWordToText(str , strLength , index) ;

            Text[index-1+strLength] = ' ' ;
        }

        index+=(strLength+1) ;
    }

}

void InsertWordLast(char text[] , int index , Queue *Q , Stack *UndoStack){

    StringToQueue(text , Q) ;

    int QSize = Q->Size ;
    for (int i = 0 ; i < QSize ; i++){
        char str[50] ; strcpy(str , FrontAndDequeue(Q)) ;

        Push(str , "Insert" , -1 , 1 , UndoStack) ;

        Text[textSize++] = ' ' ; // add previous space
        Text[textSize] = '\0' ; // set to null, so strcat can operate

        strcat(Text , str) ;

        textSize+=strlen(str) ;

    }

}

void InsertChar(char text[] , int index , Queue *Q , Stack *UndoStack){

    Enqueue(text , Q) ; // enqueue the word to Q

    char str[50] ; strcpy(str , FrontAndDequeue(Q)) ;
    int strLength = strlen(str) ;

    Push(str , "Insert" , index , 2 , UndoStack) ;
    shiftTextToRight(strLength , index) ;
    InsertWordToText(str , strLength , index) ;

}

void UndoOperation(Stack *UndoStack , Stack *RedoStack){

    int index = TopIndex(UndoStack) ;
    char operation[10] ; strcpy(operation , TopOperation(UndoStack)) ;
    char word[50] ; strcpy(word , TopWord(UndoStack)) ;
    int type = TopType(UndoStack) ;

    if (type == 1){ // we need to add spaces here
        if (index == -1){ // insert or remove last
            if (strcmp(operation , "Insert") == 0){ // insert operation. we will remove the word.
                textSize-= strlen(word) ;
                if (textSize-1 >= 0 && Text[textSize-1] == ' '){
                    Text[--textSize] = '\0' ; // remove the previous space
                }
                else{ // if the last word is the only word in the string, we will enter this statement.
                    Text[textSize] = '\0' ;
                }
            }
            else{ // remove operation. we will insert the word.
                Text[textSize++] = ' ' ;
                Text[textSize] = '\0' ;
                strcat(Text , word) ;
                textSize+=strlen(word) ;
            }
        }
        else{ // index is not -1. insert or remove from beginning or middle
            if (strcmp(operation , "Insert") == 0){ // insert operation. we will remove the word.
                if (index == 1){ // remove first word
                    RemoveWordFirst(index , strlen(word)) ;
                }
                else{ // remove word from index to index+strLen(word)
                    RemoveWordAfter(index , strlen(word)) ;
                }
            }
            else{ // remove operation. we will insert the word.
                if (index == 1){ // insert first
                    int wordLength = strlen(word) ;

                    if (isPunctual(Text[index-1])){ // the first char maybe punctual mark, so we will not add space here
                        shiftTextToRight(wordLength , index) ;
                        InsertWordToText(word , wordLength , index) ;
                    }
                    else if (textSize == 0){
                        // the text may be empty, so we will not add space
                        InsertWordToText(word , wordLength , index) ;
                        textSize = wordLength ;
                        Text[textSize] = '\0' ;
                    }
                    else{ // add space after the inserted word
                        shiftTextToRight(wordLength+1 , index) ;
                        InsertWordToText(word , wordLength , index) ;
                        Text[wordLength] = ' ' ;
                    }
                }
                else{ // insert after some word
                    int wordLength = strlen(word) ;

                    shiftTextToRight(wordLength+1 , index-1) ;
                    Text[index-2] = ' ' ; // add space before the inserted word
                    InsertWordToText(word , wordLength , index) ;
                }
            }
        }
    }
    else{ // type 2. remove characters without spaces
        if (strcmp(operation , "Insert") == 0){ // we will remove the chars
            RemoveChar(index , strlen(word)) ;
        }
        else{ // we will insert the chars
            int wordLength = strlen(word) ;
            shiftTextToRight(wordLength , index) ;
            InsertWordToText(word , wordLength , index) ;
        }
    }

    Pop(UndoStack) ;
    Push(word , operation , index , type , RedoStack) ; // push to the redo

}

void RedoOperation(Stack *UndoStack , Stack *RedoStack){

    int index = TopIndex(RedoStack) ;
    char operation[10] ; strcpy(operation , TopOperation(RedoStack)) ;
    char word[50] ; strcpy(word , TopWord(RedoStack)) ;
    int type = TopType(RedoStack) ;

    if (type == 1){ // insert or remove words with spaces
        if (index == -1){ // insert or remove last
            if (strcmp(operation , "Insert") == 0){ // insert operation. we will insert the word.
                Text[textSize++] = ' ' ;
                Text[textSize] = '\0' ;
                strcat(Text , word) ;
                textSize+=strlen(word) ;
            }
            else{ // remove operation. we will remove the word.
                textSize-=strlen(word) ;
                if (textSize-1 >= 0 && Text[textSize-1] == ' '){
                    Text[--textSize] = '\0' ; // remove the previous space
                }
                else{ // if the last word is the only word in the string, we will enter this statement.
                    Text[textSize] = '\0' ;
                }
            }
        }
        else{ // index is not -1
            if (strcmp(operation , "Insert") == 0){ // insert operation. we will insert the word.
                if (index == 1){ // insert first
                    int wordLength = strlen(word) ;

                    if (isPunctual(Text[index-1])){ // if the text is like this: ". Hello welcome"
                        shiftTextToRight(wordLength , index) ; // we will shift starting from the punctual mark
                        InsertWordToText(word , wordLength , index) ; // insert the word to the text without adding space
                    }
                    else if (textSize == 0){
                        // empty text
                        InsertWordToText(word , wordLength , index) ;
                        textSize = wordLength ;
                        Text[textSize] = '\0' ;
                    }
                    else{ // insert after index
                        shiftTextToRight(wordLength+1 , index) ;
                        InsertWordToText(word , wordLength , index) ;
                        Text[wordLength] = ' ' ; // add space after the inserted word
                    }
                }
                else{ // index is not 1, so we will insert after some word
                    int wordLength = strlen(word) ;

                    shiftTextToRight(wordLength+1 , index-1) ;
                    Text[index-2] = ' ' ; // add space before the inserted word
                    InsertWordToText(word , wordLength , index) ;
                }
            }
            else{ // remove operation. we will remove the word.
                if (index == 1){ // remove first
                    RemoveWordFirst(index , strlen(word)) ;
                }
                else{ // remove from middle
                    RemoveWordAfter(index , strlen(word)) ;
                }
            }
        }
    }
    else{ // type 2. remove or insert characters without spaces
        if (strcmp(operation , "Insert") == 0){ // we will insert the chars
            int wordLength = strlen(word) ;
            shiftTextToRight(wordLength , index) ;
            InsertWordToText(word , wordLength , index) ;
        }
        else{
            RemoveChar(index , strlen(word)) ;
        }
    }

    Pop(RedoStack) ;
    Push(word , operation , index , type , UndoStack) ; // push to the undo

}

void printUndoRedoStacks(Stack *UndoStack , Stack *RedoStack){

    // creat temp stacks to print the stacks data
    Stack *tempUndo , *tempRedo ;
    tempUndo = copyStack(UndoStack) ;
    tempRedo = copyStack(RedoStack) ;

    if (IsEmptyStack(tempUndo)){ // undo is empty
        printf("UndoStack is empty.\n") ;
    }
    else{
        printf("UndoStack:\n") ;
        while (!IsEmptyStack(tempUndo)){
            printf("%s\t%s\t%d\n" , TopWord(tempUndo) , TopOperation(tempUndo) , TopIndex(tempUndo)) ;
            Pop(tempUndo) ;
        }
    }

    if (IsEmptyStack(tempRedo)){ // redo is empty.
        printf("\nRedoStack is empty.\n") ;
    }
    else{
        printf("\nRedoStack:\n") ;
        while (!IsEmptyStack(tempRedo)){
            printf("%s\t%s\t%d\n" , TopWord(tempRedo) , TopOperation(tempRedo) , TopIndex(tempRedo)) ;
            Pop(tempRedo) ;
        }
    }
    printf("\n") ;
    // free temp stacks
    DisposeStack(tempUndo) ;
    DisposeStack(tempRedo) ;

}

void displayMenu(){

    printf("1- Load input file.\n"
           "2- Print the loaded text.\n"
           "3- Insert strings to text.\n"
           "4- Remove strings from the text.\n"
           "5- Perform Undo operation.\n"
           "6- Perform Redo operation.\n"
           "7- Print the Undo stack and Redo Stack.\n"
           "8- Save the updated text to the output file.\n"
           "9- Exit.\n\n") ;

}

void displayInsertList(){

    printf("1- Insert text at the beginning of the Text.\n"
           "2- Insert text after some word in the Text.\n"
           "3- Insert characters at the beginning of some word in the Text.\n"
           "4- Insert characters for some word in the Text.\n") ;

}

void displayRemoveList(){

    printf("1- Remove a text.\n"
           "2- Remove characters from some word.\n") ;

}

void SaveToOutputFile(){

    FILE *fp = fopen("OutputFile.txt" , "w") ;

    if (fp == NULL){
        printf("File does not exist.\n\n") ;
        return ;
    }

    fprintf(fp , "%s\n" , Text) ;

    printf("Text has been saved to output file.\n\n") ;
    fclose(fp) ;

}