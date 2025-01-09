/*
    Qasim Batrawi
    1220204
    sec: 4
 */

#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>

#define INFINITY 1e9 ;

typedef struct LinkedListNode List ;

struct LinkedListNode{

    char word[50] ;
    int inDegree ; // this will be used in the Course graph in the topological sort
    int distance ; // this will be used in the Building graph in dijkstra
    List *Next ;

};

typedef struct Graph CourseGraph ;
typedef struct Graph BuildingGraph ;
typedef struct Graph Graph ;

struct Graph{

    int vertex ; // number of vertices on the graph
    List *AdjList[20] ;

};

Graph *MakeEmptyGraph(Graph *graph) ;

void InsertToGraph(char word[50] , Graph *graph) ;

int FindInGraph(char word[50] , Graph *graph) ;

void DeleteGraph(Graph *graph) ;

List *FindInList(char word[50] , List *L , Graph *graph) ;

void InsertToList(char word[50] , int distance , List *p , List *L , Graph *graph) ;

void DeleteList(List *L , Graph *graph) ;

List *MakeEmptyList(List *L) ;

#define MinQueueSize 5

typedef struct QueueRecord Queue ;

struct QueueRecord{

    int Capacity ;
    int Front ;
    int Rear ;
    int Size ;
    char *Array[50] ;

};

int IsEmptyQueue(Queue *Q) ;

void MakeEmptyQueue(Queue *Q) ;

Queue *CreateQueue (int MaxElements) ;

void DisposeQueue(Queue *Q) ;

int succ(int value , Queue *Q) ;

void Enqueue (char word[50] , Queue *Q) ;

char *FrontAndDequeue(Queue *Q) ;

void readCoursesFile(CourseGraph *CourseGraph) ;

void FindLeastInDegree(int degree , CourseGraph *Graph , Queue *Q) ;

void RemoveOutgoingEdges(char vertex[50] , CourseGraph *CourseGraph) ;

void topologicalSort(Queue *SortedCourses , CourseGraph *CourseGraph) ;

typedef struct Table Table ;

struct Table{

    int *distance ;
    char *previous[50] ;
    char *building[50] ;
    int size ;
    int *visited ;

};

Table *creatTable(int vertex , Table *T) ;

void MakeEmptyTable(Table *T , BuildingGraph *BuildingGraph) ;

void DeleteTable(Table *T) ;

int UpdateTable(char building[50] , char previous[50] , int distance , Table *T) ;

int FindInTable(char building[50] , Table *T) ;

void readBuildingsFile(BuildingGraph *BuildingGraph) ;

typedef struct MinBinaryHeap HeapArray ;

struct MinBinaryHeap{

    char *building[100] ;
    int *distance ;
    int rear ; // pointer to the last empty cell
    int capacity ;
    int size ; // current size

};

HeapArray *createHeapArray(int size) ;

void CheckForPriority(int child , HeapArray *Array) ;

void InsertToArray(char building[50] , int distance , HeapArray *Array) ;

int IsEmptyArray(HeapArray *Array) ;

char *FirstBuilding(HeapArray *Array) ;

int FirstDistance(HeapArray *Array) ;

void RemoveFromArray(int father , HeapArray *Array) ;

void dijkstra(char source[50] , char destination[50] , Table *T , BuildingGraph *BuildingGraph) ;

void shortestRoute(int destinationInd , char source[50] , char destination[50] , Table *T) ;

void displayMenu() ;

int main(){

    CourseGraph *CourseGraph = MakeEmptyGraph(CourseGraph) ; // courseGraph
    BuildingGraph *BuildingGraph = MakeEmptyGraph(BuildingGraph) ; // buildingGraph

    Table *T = NULL ; // the table that will be used in dijkstra

    Queue *SortedCourses = CreateQueue(20) ; // the queue will save the answer of the topological sort for the courses

    int option , loadedFiles=0 , sorted=0 ;

    printf("\nWelcome to our program.\n\n") ;
    displayMenu() ;
    printf("\nPlease chose one of the options from 1-6: ") ;
    scanf("%d" , &option) ;
    printf("\n") ;

    while (option != 6){
        if (option < 1 || option > 6){
            printf("Option is not in the menu.\n\n") ;
        }
        else if (option == 1){ // load files
            if (loadedFiles){
                printf("Files has been loaded recently.\n\n") ;
            }
            else{
                readCoursesFile(CourseGraph) ; // load courseFile
                readBuildingsFile(BuildingGraph) ; // load buildingFile
                T = creatTable(BuildingGraph->vertex , T) ; // create the table
                loadedFiles = 1 ;
                printf("Input File has been loaded.\n\n") ;
            }
        }
        else if (option == 2){ // shortest distance between two buildings
            if (!loadedFiles){ // file is not loaded yet
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else{
                char source[50] , destination[50] ;
                printf("Please enter the name of the source building: ") ;
                scanf("%s" , source) ;

                int ind = FindInGraph(source , BuildingGraph) ;
                // check if the source exist
                if (ind == -1){
                    printf("\n\"%s\" building is not in the graph.\n\n" , source) ;
                }
                else{
                    printf("Please enter the name of the destination building: ") ;
                    scanf("%s" , destination) ;

                    ind = FindInGraph(destination , BuildingGraph) ;
                    // check if the destination exist
                    if (ind == -1){
                        printf("\n\"%s\" building is not in the graph.\n\n" , destination) ;
                    }
                    else{
                        dijkstra(source , destination , T , BuildingGraph) ; // find the shortest path and distance from the source to all nodes

                        ind = FindInTable(destination , T) ;

                        if (T->distance[ind] == 1e9){ // there is no path from the source to the destination
                            printf("\nThere is no path from \"%s\" to \"%s\"\n\n" , source , destination) ;
                        }
                        else{ // print the distance
                            printf("\nThe shortest distance between \"%s\" and \"%s\" is: %d\n\n" , source , destination , T->distance[ind]) ;
                        }
                    }
                }
            }
        }
        else if (option == 3){ // shortest path and distance between two buildings
            if (!loadedFiles){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else{
                char source[50] , destination[50] ;
                printf("Please enter the name of the source building: ") ;
                scanf("%s" , source) ;

                int ind = FindInGraph(source , BuildingGraph) ;
                // check if the source exist
                if (ind == -1){
                    printf("\n\"%s\" building is not in the graph.\n\n" , source) ;
                }
                else{
                    printf("Please enter the name of the destination building: ") ;
                    scanf("%s" , destination) ;

                    ind = FindInGraph(destination , BuildingGraph) ;
                    // check if the destination exist
                    if (ind == -1){
                        printf("\n\"%s\" building is not in the graph.\n\n" , destination) ;
                    }
                    else{
                        dijkstra(source , destination , T , BuildingGraph) ; // find the shortest path and distance between the source and all nodes

                        ind = FindInTable(destination , T) ;

                        if (T->distance[ind] == 1e9){ // there is no path between the source and the destination
                            printf("\nThere is no path from \"%s\" to \"%s\"\n\n" , source , destination) ;
                        }
                        else{
                            printf("\nThe shortest distance between \"%s\" and \"%s\" is: %d\n" , source , destination , T->distance[ind]) ;
                            shortestRoute(ind , source , destination , T) ; // print the path
                        }
                    }
                }
            }
        }
        else if(option == 4){ // do the topological sort for the courses and save the answer(without printing it)
            if (!loadedFiles){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (sorted){ // courses has been sorted before
                printf("Courses has been sorted recently.\n\n") ;
            }
            else{ // do the topological sort
                topologicalSort(SortedCourses , CourseGraph) ;
                printf("Courses has been sorted.\n\n") ;
                sorted = 1 ;
            }
        }
        else{
            if (!loadedFiles){ // file is not loaded
                printf("Input file has not been loaded yet.\n\n") ;
            }
            else if (!sorted){ // courses are not sorted yet
                printf("Courses has not been sorted yet.\n\n") ;
            }
            else{
                printf("The sorted courses are:  ") ;
                 // print the queue (dequeue then print then enqueue)
                int QSize = SortedCourses->Size ;
                for (int i = 0 ; i < QSize ; i++){
                    char course[50] ;
                    strcpy(course , FrontAndDequeue(SortedCourses)) ;

                    printf("%s  " , course) ;

                    Enqueue(course , SortedCourses) ;
                }
                printf("\n\n") ;
            }
        }

        displayMenu() ;
        printf("\nPlease chose one of the options from 1-6: ") ;
        scanf("%d" , &option) ;
        printf("\n") ;

    }

    printf("Thank you for using our program. Goodbye.\n") ;

    // delete and free all structs
    DeleteTable(T) ;
    DeleteGraph(CourseGraph) ;
    DeleteGraph(BuildingGraph) ;
    DisposeQueue(SortedCourses) ;

}

Graph *MakeEmptyGraph(Graph *graph){

    // create a graph

    graph = (struct CourseGraph*)(malloc(sizeof(struct Graph))) ;

    if (graph == NULL){
        printf("Out of memory.\n\n") ;
        return NULL ;
    }


    for (int i = 0 ; i < 20 ; i++){
        graph->AdjList[i] = NULL ;
        graph->AdjList[i] = MakeEmptyList(graph->AdjList[i]) ; //create list for the graph
        if (graph->AdjList[i] == NULL){
            printf("Out of memory.\n\n") ;
            return NULL ;
        }
    }

    graph->vertex = 0 ; // current size=0

    return graph ;

}

void InsertToGraph(char word[50] , Graph *graph){

    // insert last to the array

    strcpy(graph->AdjList[graph->vertex]->word , word) ;
    graph->vertex++ ;

}

int FindInGraph(char word[50] , Graph *graph){
    // find in the graph array
    for (int i =  0 ; i < graph->vertex ; i++){
        if (strcmp(graph->AdjList[i]->word , word) == 0){
            return i ;
        }
    }

    return -1 ; // word does not exist

}

void DeleteGraph(Graph *graph){ // free the graph data

    for (int i = 0 ; i < 20 ; i++){
        DeleteList(graph->AdjList[i] , graph) ;
    }

    free(graph) ;

}

List *FindInList(char word[50] , List *L , Graph *graph){

    // find in a specific list in the graph

    List *p = L->Next ; // pointer after the head

    while (p != NULL && strcmp(p->word , word) != 0){
        p = p->Next ;
    }

    return p ; // if DNE, return NULL

}

void InsertToList(char word[50] , int distance , List *p , List *L , Graph *graph){ // InsertToList after p. distance will be used only in the building graph, otherwise it will be 0

    // insert first to a specific list in the graph

    List *temp = (List*)malloc(sizeof(List)) ;

    if (temp != NULL){ // temp may be NULL because of Out of Memory
        strcpy(temp->word , word) ;
        temp->distance = distance ;
        temp->Next = p->Next ;
        p->Next = temp ;
    }

}

void DeleteList(List *L , Graph *graph){
    // free a specific list in the graph
    List *p = L->Next , *temp ;
    free(L) ;

    while (p != NULL){
        temp = p->Next ;
        free(p) ;
        p = temp ;
    }
}

List *MakeEmptyList(List *L){
    // create list
    L = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode)) ; // malloc function will return (void*), so we will cast it to (List*)

    if (L == NULL){
        printf("Out of memory!\n") ;
    }

    L->Next = NULL ;
    L->inDegree = 0 ;

    return L ;

}

int IsEmptyQueue(Queue *Q){

    return Q->Size == 0 ;

}

void MakeEmptyQueue(Queue *Q){

    Q->Rear = 0 ;
    Q->Front = 1 ;
    Q->Size = 0 ;

}

Queue *CreateQueue (int MaxElements){

    Queue *Q ;

    if (MaxElements < MinQueueSize){
        printf("Queue size is too small!\n") ;
        return NULL ;
    }

    Q = (Queue*)(malloc(sizeof(Queue))) ;

    if (Q == NULL){
        printf("Out of memory!\n") ;
        return NULL ;
    }

    for (int i = 0 ; i < MaxElements ; i++){
        Q->Array[i] = (char*)(malloc(sizeof(char)*50)) ;
        if (Q->Array[i] == NULL){
            printf("Out of memory!\n") ;
            return NULL ;
        }
    }

    Q->Capacity = MaxElements ;
    MakeEmptyQueue(Q) ;

    return Q ;

}

void DisposeQueue(Queue *Q){
    // free the queue data
    for (int i = 0 ; i < Q->Capacity ; i++){
        free(Q->Array[i]) ;
    }
    free(Q) ;

}

int succ(int value , Queue *Q){

    if (++value == Q->Capacity){
        value=0 ;
    }

    return value ;

}

void Enqueue (char word[50] , Queue *Q){

    if (Q->Size == Q->Capacity){
        printf("Full Queue\n") ;
    }
    else{
        Q->Size++ ;
        Q->Rear = succ(Q->Rear , Q) ;
        strcpy(Q->Array[Q->Rear] , word) ;
    }

}

char *FrontAndDequeue(Queue *Q){

    if (IsEmptyQueue(Q)){
        printf("Empty Queue\n") ;
        return NULL ;
    }

    Q->Size-- ;
    char *word = Q->Array[Q->Front] ;
    Q->Front = succ(Q->Front , Q) ;

    return word ;

}

void readCoursesFile(CourseGraph *CourseGraph){

    FILE *fp = fopen("input_courses.txt" , "r") ;

    if (fp == NULL){
        printf("File does not exist.\n\n") ;
        return ;
    }

    char str[100] ;

    while (fgets(str , sizeof(str) , fp)){

        int strLen = strlen(str) ;
        if (str[strLen-1] == '\n'){ // check if the last char is '\n' and delete it if true
            str[strLen-1] = '\0' ;
            strLen-- ;
        }

        if (strLen == 0){
            continue ; // empty line
        }

        char temp[50] ; // copy from str
        strcpy(temp , str) ;

        char *token = strtok(str , "#") ;

        while (token != NULL){ // we will insert all the courses to the graph array

            int ind = FindInGraph(token , CourseGraph) ;

            if (ind == -1){ // check if the course exist or not
                InsertToGraph(token , CourseGraph) ;
            }

            token = strtok(NULL , "#") ;

        }

        token = strtok(temp , "#") ;

        char course[50] ;
        strcpy(course , token) ;

        int ind = FindInGraph(course , CourseGraph) ;

        token = strtok(NULL , "#") ;
        while (token != NULL){ // we will insert the course to all its Prerequisites

            int tempInd = FindInGraph(token , CourseGraph) ;

            if (FindInList(course , CourseGraph->AdjList[tempInd] , CourseGraph) == NULL){
                InsertToList(course , 0 , CourseGraph->AdjList[tempInd] , CourseGraph->AdjList[tempInd] , CourseGraph) ; // 0 for the distance
                CourseGraph->AdjList[ind]->inDegree++ ;
            }

            token = strtok(NULL , "#") ;
        }
    }

    fclose(fp) ;

}

void FindLeastInDegree(int degree , CourseGraph *Graph , Queue *Q){
    // find the nodes that have zero in-degree and enqueue to queue
    for (int i = 0 ; i < Graph->vertex ; i++){
        if (Graph->AdjList[i]->inDegree == degree){
            Enqueue(Graph->AdjList[i]->word , Q) ;
            Graph->AdjList[i]->inDegree = -1 ; // this means that the node has been deleted
        }
    }

}

void RemoveOutgoingEdges(char vertex[50] , CourseGraph *CourseGraph){

    int ind  = FindInGraph(vertex , CourseGraph) ;

    List *node = CourseGraph->AdjList[ind]->Next ;

    while (node != NULL){ // remove all outgoing edges from a specific vertex by decreasing the in degree to its adjacent
        ind = FindInGraph(node->word , CourseGraph) ;
        CourseGraph->AdjList[ind]->inDegree-- ;

        node = node->Next ;
    }

}

void topologicalSort(Queue *SortedCourses , CourseGraph *CourseGraph){

    Queue *Q = CreateQueue(CourseGraph->vertex) ;

    for (int i = 0 ; i < CourseGraph->vertex ; i++){

        FindLeastInDegree(0 , CourseGraph , Q) ; // search for zero in degree

        while (!IsEmptyQueue(Q)){
            char vertex[50] ;
            strcpy(vertex , FrontAndDequeue(Q)) ;

            Enqueue(vertex , SortedCourses) ;

            RemoveOutgoingEdges(vertex , CourseGraph) ; // remove the outgoing edges
        }

    }

}

Table *creatTable(int vertex , Table *T){

    T = (struct Table*)(malloc(sizeof(struct Table))) ;

    if (T == NULL){
        printf("Out of memory.\n\n") ;
        return NULL ;
    }

    T->distance = (int*)(malloc(sizeof(int)*vertex)) ;
    if (T->distance == NULL){
        printf("Out of memory.\n\n") ;
        return NULL ;
    }

    T->visited = (int*)(malloc(sizeof(int)*vertex)) ;
    if (T->visited == NULL){
        printf("Out of memory.\n\n") ;
        return NULL ;
    }

    for (int i = 0 ; i < vertex ; i++){
        T->previous[i] = (char*)(malloc(sizeof(char)*50)) ;
        T->building[i] = (char*)(malloc(sizeof(char)*50)) ;
        if (T->previous[i] == NULL || T->building[i] == NULL){
            printf("Out of memory.\n\n") ;
            return NULL ;
        }
    }

    T->size = vertex ;

    return T ;

}

void MakeEmptyTable(Table *T , BuildingGraph *BuildingGraph){

    // the indices of the table will be the same as the indices of the graph array

    for (int i = 0 ; i < T->size ; i++){
        strcpy(T->building[i] , BuildingGraph->AdjList[i]->word) ;
        strcpy(T->previous[i] , "NONE") ;
        T->distance[i] = INFINITY ;
        T->visited[i] = 0 ;
    }

}

void DeleteTable(Table *T){

    // free the table

    if (T != NULL){
        for (int i = 0 ; i < T->size ; i++){
            free(T->previous[i]) ;
            free(T->building[i]) ;
        }

        free(T->distance) ;
        free(T->visited) ;

        free(T) ;
    }


}

int UpdateTable(char building[50] , char previous[50] , int distance , Table *T){

    // check if the distance is less than the current distance and update its distance and previous if it true

    for (int i = 0 ; i < T->size ; i++){
        if (strcmp(T->building[i] , building) == 0){
            if (T->distance[i] > distance){
                T->distance[i] = distance ;
                strcpy(T->previous[i] , previous) ;
            }
            return T->distance[i] ; // return the newDistance
        }
    }

    return -1 ;

}

int FindInTable(char building[50] , Table *T){

    for (int i = 0 ; i < T->size ; i++){
        if (strcmp(T->building[i] , building) == 0){
            return i ;
        }
    }

    return -1 ; // it is impossible to return -1

}

void readBuildingsFile(BuildingGraph *BuildingGraph){

    FILE *fp = fopen("input_buildings.txt" , "r") ;

    if (fp == NULL){
        printf("File does not exist.\n\n") ;
        return ;
    }

    char str[50] ;
    while (fgets(str , sizeof(str) , fp)){

        int strLen = strlen(str) ;
        if (str[strLen-1] == '\n'){
            str[strLen-1] = '\0' ;
            strLen-- ;
        }

        if (strLen == 0){
            continue ;
        }

        char temp[50] ;
        strcpy(temp , str) ;

        char *first = strtok(str , "#") , *second = strtok(NULL , "#") , *third = strtok(NULL , "#") ;

        int dist = atoi(third) ;
        if (dist < 0){
            continue ; // negative edge, so we will not insert it, since dijkstra will not work well
        }

        // insert the secondBuilding to the graph array
        int secondInd  = FindInGraph(second , BuildingGraph) ;
        if (secondInd == -1){
            InsertToGraph(second , BuildingGraph) ;
            secondInd = BuildingGraph->vertex-1 ;
        }

        // insert the firstBuilding to the graph array
        int firstInd = FindInGraph(first , BuildingGraph) ;
        if (firstInd == -1){
            InsertToGraph(first , BuildingGraph) ;
            firstInd = BuildingGraph->vertex-1 ;
        }

        List *node = FindInList(second , BuildingGraph->AdjList[firstInd] , BuildingGraph) ;
        if (node != NULL){
            if (node->distance > dist){
                node->distance = dist ; // if the node exist, we will set the its distance to the least
            }
        }
        else{
            // insert the secondBuilding to the graph array List in the index of the firstBuilding
            InsertToList(second , dist , BuildingGraph->AdjList[firstInd] , BuildingGraph->AdjList[firstInd] , BuildingGraph) ;
        }


    }

    fclose(fp) ;

}

HeapArray *createHeapArray(int size){

    HeapArray *Array = NULL ;

    Array = (struct MinBinaryHeap*)(malloc(sizeof(struct MinBinaryHeap))) ;

    if (Array == NULL){
        printf("Out of memory.\n\n") ;
        return NULL ;
    }

    Array->distance = (int*)(malloc(sizeof(int)*size)) ;

    if (Array->distance == NULL){
        printf("Out of memory.\n\n") ;
        return NULL ;
    }

    for (int i = 0 ; i < size ; i++){
        Array->building[i] = (char*)(malloc(sizeof(char)*50)) ;
        if (Array->building[i] == NULL){
            printf("Out of memory.\n\n") ;
            return NULL ;
        }
    }

    Array->capacity = size ;
    Array->rear = 1 ;
    Array->size = 0 ;

    return Array ;

}

void CheckForPriority(int child , HeapArray *Array){

    // check for the priority after inserting to the heap array

    if (child == 1){
        return ; // the element is in the root
    }

    int father = child/2 ;

    if (Array->distance[father] > Array->distance[child]){ // Q->distance[child] is the last inserted element. if they are equal, we will not do anything.

        // swap them
        char temp1[50] ;
        strcpy(temp1 , Array->building[child]) ;
        int temp2 = Array->distance[child] ;

        Array->distance[child] = Array->distance[father] ;
        strcpy(Array->building[child] , Array->building[father]) ;

        strcpy(Array->building[father] , temp1) ;
        Array->distance[father] = temp2 ;

        CheckForPriority(father , Array) ; // check the priority up to the first index(root)
    }

}

void InsertToArray(char building[50] , int distance , HeapArray *Array){

    // insert last and check for the priority up to the root

    strcpy(Array->building[Array->rear] , building) ;
    Array->distance[Array->rear] = distance ;

    CheckForPriority(Array->rear , Array) ;
    Array->rear++ ;
    Array->size++ ;

}

int IsEmptyArray(HeapArray *Array){

    return Array->size == 0 ;

}

char *FirstBuilding(HeapArray *Array){

    char *temp = Array->building[1] ;
    return temp ;

}

int FirstDistance(HeapArray *Array){

    return Array->distance[1] ;

}

void RemoveFromArray(int father , HeapArray *Array){

    // in this project, this function will be used only when the Queue is not empty, so there is no need to check if the queue is empty or not
    // also, in this project, we need this function to dequeue the first element

    int left = 2*father , right = 2*father + 1 ;

    if (left > Array->size){ // father is in the last level or in the before last level
        for (int i = Array->size ; i-1 >= father ; i--){ // we will shift all the remaining elements to the left
            Array->distance[i-1] = Array->distance[i] ;
            strcpy(Array->building[i-1] , Array->building[i]) ;
        }
        return ;
    }
    else if (right > Array->size){ // there is left but there is no right, which means that left is the last element
        Array->distance[father] = Array->distance[left] ;
        strcpy(Array->building[father] , Array->building[left]) ;
    }
    else{
        if (Array->distance[left] < Array->distance[right]){
            // swap then check the left
            Array->distance[father] = Array->distance[left] ;
            strcpy(Array->building[father] , Array->building[left]) ;
            RemoveFromArray(left , Array) ;
        }
        else{
            // swap then check the right
            Array->distance[father] = Array->distance[right] ;
            strcpy(Array->building[father] , Array->building[right]) ;
            RemoveFromArray(right , Array) ;
        }
    }

}

void dijkstra(char source[50] , char destination[50] , Table *T , BuildingGraph *BuildingGraph){

    HeapArray *Array = createHeapArray(BuildingGraph->vertex * BuildingGraph->vertex) ;

    MakeEmptyTable(T , BuildingGraph) ;

    InsertToArray(source , 0 , Array) ; // insert the source to the heap array with zero distance
    UpdateTable(source , source , 0 , T) ; // insert the source to the table with zero distance

    while (!IsEmptyArray(Array)){
        char building[50] ;
        strcpy(building , FirstBuilding(Array)) ;
        int distance = FirstDistance(Array) ;

        RemoveFromArray(1 , Array) ; // remove the root from the heap array( index 1)
        Array->size-- ; Array->rear-- ;

        int ind = FindInGraph(building , BuildingGraph) ;
        List *node = BuildingGraph->AdjList[ind]->Next ;

        if (T->visited[ind] == 1){ // the node has been visited before, so we will not continue
            continue ;
        }

        T->visited[ind] = 1 ;

        while (node != NULL){
            // insert all adjacent nodes to the table with its distance.
            int newDistance = UpdateTable(node->word , building , node->distance+distance , T) ;
            // insert to the heap array
            InsertToArray(node->word , newDistance , Array) ;
            node = node->Next ;
        }
    }

    // free the Heap
    for (int i = 0 ; i < Array->capacity ; i++){
        free(Array->building[i]) ;
    }
    free(Array->distance) ;
    free(Array) ;

}

void shortestRoute(int destinationInd , char source[50] , char destination[50] , Table *T){

    // shortest route from the source to the destination

    char *temp[50] ;

    int ind = destinationInd , j=0 ;

    temp[j] = (char*)(malloc(sizeof(char)*50)) ;
    strcpy(temp[j++] , T->building[ind]) ; // insert the destination to the array of strings

    while (strcmp(T->building[ind] , source) != 0){

        char previous[50] ;
        strcpy(previous , T->previous[ind]) ;

        temp[j] = (char*)(malloc(sizeof(char)*50)) ;
        strcpy(temp[j++] , previous) ; // insert the previous

        ind = FindInTable(previous , T) ; // find the previous

    }

    printf("\nThe shortest route between \"%s\" and  \"%s\" is:  "  , source , destination) ;
    // print the array of string reversely
    for (int i = j-1 ; i >= 0 ; i--){
        printf("%s" , temp[i]) ;
        if (i > 0){
            printf(" --> ") ;
        }
        free(temp[i]) ;
    }

    printf("\n\n") ;


}

void displayMenu(){

    printf("1- Load the two files.\n"
           "2- Calculate the shortest distance between two buildings.\n"
           "3- Print the shortest distance between two buildings and the total distance.\n"
           "4- Sort the courses using topological sort.\n"
           "5- print the sorted courses.\n"
           "6- Exit the application.\n") ;

}
