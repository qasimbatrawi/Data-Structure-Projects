/*
 Qasim Batrawi
 1220204
 Section: 4
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>

typedef struct District District ;
typedef struct Town Town ;
typedef struct District Alphabetical ; // this is for the String radix sort
typedef struct District Numbers ; // this is for the Integer radix sort

#define MAX_LENGTH 50 // max length of the string.

District *lastDistrict = NULL ; // this is global pointer which will be a pointer to the lastDistrict in the List.

struct District{

    char district[50] ;
    int population ;
    District *NextDistrict ;
    District *PrevDistrict ;
    Town *NextTown ;
    Town *lastTown ; // pointer to the last town in each district.
    int sortedTowns ; // this is for the radix sort for population to check if it is sorted or not. we will reduce the time complexity with this.

};

struct Town{

    char town[50] ;
    int population ;
    Town *NextTown ;
    Town *PrevTown ;

};

////*********************************************************************LIST*********************************************************************////

District *MakeEmpty(District *List);

District *MakeEmptyTempList(District *List); // we have built another makeEmpty to use it in the radix sort and for creating a copyList, so the global lastDistrict will not change in this function.

void PrintAllData(District *List);

void DeleteAllData(District *List);

int sizeOfList(District *List);

District *copyList(District *List);

////*********************************************************************DISTRICT*********************************************************************////

int hasDistricts(District *List);

int IsLastDistrict(District *district , District *List);

District *FindDistrict(char districtName[50] , District *List);

void InsertDistrict(char districtName[50] , District *p , District *List); // we will use this method to insert districts, in this project, i have built it in the way to insert in any place. but in this project, we will use it as insert last.

District *InsertAndReturnLastDistrict(char districtName[50] , District *tempLastDistrict , District *tempList); // we will use this method in the string radix sort and for creating a copy List.

void DeleteDistrict(District *district , District *List);

void DeleteAllDistricts(District *List);

void PrintDistricts(District *List);

////*********************************************************************TOWN*********************************************************************////

int hasTowns(District *district , District *List);

int hasTownsInList(District *List); // this function will check if there is a town in the List.

int IsLastTown(Town *town , District *district , District *List);

Town *FindTown(char townName[50] , District *district , District *List);

void InsertTown(char townName[50] , int populationCount , Town *p , District *district , District *List);

void InsertAllTowns(Town *town , District *district , District *List); // we will use this function while moving data in string radix sort and for creating a copy list.

void DeleteTown(Town *town , District *district , District *List);

void DeleteAllTowns(District *district , District *List);

int NumOfTowns(District *district , District *List); // the number of towns in a specific district.

void PrintTowns(District *district , District *List);

////*********************************************************************FILE*********************************************************************////

void PrintListAsFile(District *tempList);

void readInputFileAndInsert(District *List);

void insertInfoToList(District *List , char districtName[50] , char townName[50] , char population[50]);

void SaveToOutputFile(District *List);

////*********************************************************************STRING & INTEGER*********************************************************************////

int isdigit(char c);

int isalpha(char c);

int strLen(char str[100]); // I have built this method instead of using strlen(), because strlen() will read the last char ('\n') in each line of the file which will increase the size by one.

int getMaxChars(District *List);

int getMaxDigits(District *district , District *List);

////*********************************************************************SORTING*********************************************************************////

District *stringRadixSortForDistricts(District *List);

void populationRadixSortForTowns(District *List);

////*********************************************************************MENU*********************************************************************////

void displayMenu();

////*********************************************************************MAIN*********************************************************************////

int main(){

    District *List = NULL ;
    List = MakeEmpty(List) ;

    District *tempList = NULL ; // this is a copy from the original list, we will use it for option number 2 in the menu.

    printf("\nWelcome to the program.\n\n") ;

    int chose[14] ; // this is for the options of the menu, we will check if the option has been chosen using this array.
    for (int i = 0 ; i < 14 ; i++){
        chose[i] = 0 ;
    }

    int option ;

    displayMenu() ;
    printf("\nChoose one of the options above from 1-14: ") ;
    scanf("%d" , &option) ;
    getchar() ; // it will get the '\n' character from the buffer. So the buffer will be clear.
    printf("\n") ;

    while (option != 14){

        if (option < 1 || option > 14){
            printf("The option number is not in the menu.\n\n") ;
        }

        else if (option == 1){ // read file
            if (chose[option-1]){
                printf("Input file has been loaded recently. If you want to re-load the input file, please restart the program.\n\n") ;
            }
            else{
                readInputFileAndInsert(List) ;
                chose[option-1] = 1 ;
                printf("Input file has been loaded.\n\n") ;
                tempList = copyList(List) ;
                if (!hasDistricts(List)){
                    printf("The List is Empty. Input file is empty or it does not match the details of the program.\n\n") ;
                }
            }
        }
        else if (option == 2){ // print the list as a file.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else{
                // print tempList
                PrintListAsFile(tempList) ;
                printf("\n") ;
                chose[option-1] = 1 ;
            }
        }
        else if (option == 3){ // sort the districts alphabetically.
            if (!chose[0]){
                printf("The information has not been loaded yet\n\n") ;
            }
            else if (!hasDistricts(List)){
                printf("The List does not have any district.\n\n") ;
            }
            else if (chose[option-1]){
                printf("Districts have already been sorted alphabetically.\n\n") ;
            }
            else{
                // sort the list
                List = stringRadixSortForDistricts(List) ;
                printf("Districts have been sorted alphabetically.\n\n") ;
                chose[option-1] = 1 ;
            }
        }
        else if (option == 4){ // sort the towns based on population.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else if (!hasDistricts(List)){
                printf("The List does not have any district.\n\n") ;
            }
            else if (!hasTownsInList(List)){
                printf("The districts in the List do not have any town.\n\n") ;
            }
            else if (chose[option-1]){
                printf("Towns have already been sorted based on population.\n\n") ;
            }
            else{
                // sort the towns for each district
                populationRadixSortForTowns(List) ;
                printf("Towns have been sorted based on population.\n\n") ;
                chose[option-1] = 1 ;
            }
        }
        else if (option == 5){ // print sorted list.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else if (!chose[2] && hasDistricts(List)){ // if the list is empty, we will go to (else) and print Empty List.
                printf("Districts have not been sorted yet.\n\n") ;
                if (!chose[3] && hasTownsInList(List)){
                    printf("Towns have not been sorted yet.\n\n") ;
                }
            }
            else if (!chose[3] && hasTownsInList(List)){ // if the list does not have any town, we will not enter this statement.
                printf("Towns have not been sorted yet.\n\n") ;
            }
            else{
                PrintAllData(List) ;
                chose[option-1] = 1 ;
                printf("\n") ;
            }
        }
        else if (option == 6){ // add district.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else if (!chose[2] && hasDistricts(List)){ // the list  has districts and they are not sorted
                printf("Districts have not been sorted yet.\n\n") ;
            }
            else{ // we can add districts to an empty list even if we have not sorted it
                char districtName[50] ;
                printf("Please enter the name of the district you want to insert: ") ;
                gets(districtName) ;
                if (FindDistrict(districtName , List) != NULL){
                    // the district exist
                    printf("\n%s district is already in the List.\n\n" , districtName) ;
                }
                else{
                    InsertDistrict(districtName , lastDistrict , List) ; // insert last and then sort.
                    List = stringRadixSortForDistricts(List) ; // sort the list
                    printf("\n%s district has been added and the Districts has been re-sorted alphabetically.\n\n" , districtName) ;
                    chose[option-1] = 1 ;
                    chose[3-1] = 1 ; // the list is sorted
                }
            }
        }
        else if (option == 7){ // add town to a specific district.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else if (!hasDistricts(List)){
                // the list is empty
                printf("The List does not have any district.\n\n") ;
            }
            else{
                char districtName[50] ;
                printf("Please enter the name of the district you want to add town for it: ") ;
                gets(districtName) ;
                District *district = FindDistrict(districtName , List) ;
                if (district == NULL){
                    // the district does not exist
                    printf("\n%s district is not in the List.\n\n" , districtName) ;
                }
                else{
                    char townName[50] ;
                    printf("Please enter the name of the town that you want to add to %s district: " , districtName) ;
                    gets(townName) ;
                    if (FindTown(townName , district , List) != NULL){
                        // the town exist in the district
                        printf("\n%s town is already in %s district.\n\n" , townName , districtName) ;
                    }
                    else{
                        int populationCount ;
                        printf("Please enter the population of %s town: " , townName) ;
                        scanf("%d" , &populationCount) ;
                        getchar() ;
                        if (populationCount < 0){
                            // undefined population
                            printf("\nThe population can not be less than zero.\n\n") ;
                        }
                        else {
                            InsertTown(townName, populationCount, district->lastTown, district, List); // insert the town
                            printf("\n%s town has been added to %s district.\n\n", townName, districtName);
                            district->sortedTowns = 0 ; // the towns in this district are not sorted here.
                            chose[4-1] = 0; // the towns in the list are not sorted, since we have added a new town.
                            chose[option - 1] = 1;
                        }
                    }
                }
            }
        }
        else if (option == 8){ // delete town.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else if (!hasDistricts(List)){ // the list does not have any district to delete town from it
                printf("The List does not have any district.\n\n") ;
            }
            else{
                char districtName[50] ;
                printf("Please enter the name of the district you want to delete town from it: ") ;
                gets(districtName) ;
                District *district = FindDistrict(districtName , List) ;
                if (district == NULL){ // the district does not exist
                    printf("\n%s district is not in the List.\n\n" , districtName) ;
                }
                else if (!hasTowns(district , List)){ // the district does not have any town to delete
                    printf("\n%s district does not have any town.\n\n", districtName) ;
                }
                else{
                    char townName[50] ;
                    printf("Please enter the name of the town that you want to delete from %s district: " , districtName) ;
                    gets(townName) ;
                    Town *town = FindTown(townName , district , List) ;
                    if (town == NULL){ // the town does not exist
                        printf("\n%s town is not in %s district.\n\n" , townName , districtName) ;
                    }
                    else{
                        DeleteTown(town , district , List) ; // delete the town
                        printf("\n%s town has been deleted from %s district.\n\n" , townName , districtName) ;
                        chose[option-1] = 1 ;
                    }
                }
            }
        }
        else if (option == 9){ // delete district.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else if (!hasDistricts(List)){
                // list is empty
                printf("The List does not have any district.\n\n") ;
            }
            else{
                char districtName[50] ;
                printf("Please enter the name of the district you want to delete: ") ;
                gets(districtName) ;
                District *district = FindDistrict(districtName , List) ;
                if (district == NULL){ //district does not exist
                    printf("\n%s district is not in the List.\n\n" , districtName) ;
                }
                else{
                    DeleteDistrict(district , List) ;
                    printf("\n%s district has been deleted.\n\n" , districtName) ;
                    chose[option-1] = 1 ;
                }
            }
        }
        else if (option == 10){ // calc the population.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else if (!hasDistricts(List)){
                printf("Total population of Palestine = 0.\n"
                       "The List does not have any district.\n\n") ;
            }
            else{
                int totalPopulation=0 , maxPopulation=-1 , minPopulation=1e9 ;
                // minPopulation is approximately the maximum integer, so any integer will be less than it. maxPopulation is -1 so any population will be greater than it.
                // if we set maxPopulation to 0, we will have a problem if the list has towns and there populations are 0, we will not be able to get the name of the maxDistrict.
                char maxTown[50] , minTown[50] , maxDistrict[50] , minDistrict[50] ;
                int townsExist = 0 ; // i didnt use the function hasTownsInList(), because this function contains the same loop below (so we will reduce the time).
                District *district = List->NextDistrict ;
                while (district != NULL){
                    int currentPopulation = district->population ;
                    totalPopulation+=currentPopulation ;
                    Town *town = district->NextTown ;
                    while (town != NULL){
                        townsExist = 1 ;
                        if (town->population > maxPopulation){
                            maxPopulation = town->population ;
                            strcpy(maxTown , town->town) ;
                            strcpy(maxDistrict , district->district) ;
                        }
                        if (town->population < minPopulation){
                            minPopulation = town->population ;
                            strcpy(minTown , town->town) ;
                            strcpy(minDistrict , district->district) ;
                        }
                        town = town->NextTown ;
                    }
                    district = district->NextDistrict ;
                }
                if (totalPopulation == 0 && townsExist == 0){
                    printf("Total population of Palestine = 0.\n"
                           "The districts in the List do not have any town.\n\n") ;
                }
                else{
                    printf("Total population of Palestine = %d.\n"
                           "The maximum population of a town in Palestine = %d. (%s town in %s district).\n"
                           "The minimum population of a town in Palestine = %d. (%s town in %s district).\n\n"
                            , totalPopulation , maxPopulation , maxTown , maxDistrict , minPopulation , minTown , minDistrict) ;
                }
                chose[option-1] = 1 ;
            }
        }
        else if (option == 11){ // print the districts with its population. (without towns)
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else{ // it is not necessary to the districts to be sorted.
                PrintDistricts(List) ;
                printf("\n") ;
                chose[option-1] = 1 ;
            }
        }
        else if (option == 12){ // change the population of a town.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else if (!hasDistricts(List)){ // list is empty
                printf("The List does not have any district.\n\n") ;
            }
            else{
                char districtName[50] ;
                printf("Please enter the name of the district for the town you want to change its population: ") ;
                gets(districtName) ;
                District *district = FindDistrict(districtName , List) ;
                if (district == NULL){ // district does not exist
                    printf("\n%s district is not in the List.\n\n" , districtName) ;
                }
                else if (!hasTowns(district , List)){ // district does not have any town
                    printf("\n%s district does not have any town.\n\n") ;
                }
                else{
                    char townName[50] ;
                    printf("Please enter the name of the town you want to change its population in %s district: " , districtName) ;
                    gets(townName) ;
                    Town *town = FindTown(townName , district , List) ;
                    if (town == NULL){
                        printf("\n%s town is not in %s district.\n\n" , townName , districtName) ;
                    }
                    else{
                        int populationCount ;
                        printf("Please enter the new population of %s town: ", townName) ;
                        scanf("%d" , &populationCount) ;
                        getchar() ;
                        if (populationCount < 0){
                            printf("\nThe population can not be less than zero.\n\n") ;
                        }
                        else{
                            district->population-=town->population ;
                            town->population = populationCount ;
                            district->population+=populationCount ;
                            printf("\nThe population of %s town in %s district has been changed.\n\n" , townName , districtName) ;
                            district->sortedTowns = 0 ; // the towns in this district are not sorted now.
                            chose[option-1] = 1 ;
                            chose[4-1] = 0 ; // towns are not sorted now.
                        }
                    }
                }
            }
        }
        else{ // Save to output file.
            if (!chose[0]){
                printf("The information has not been loaded yet.\n\n") ;
            }
            else{
                if (!hasDistricts(List)){ // we will print to the user on the console that the list is empty, also same thing on the output file.
                    printf("The List is empty.\n\n") ;
                }
                else{
                    // we will do an auto Sort for the districts and towns if they are not sorted, since the output file must be sorted.
                    if (!chose[2]){
                        List = stringRadixSortForDistricts(List) ;
                        printf("Districts have been sorted alphabetically\n\n") ;
                        chose[3-1] = 1 ;
                    }
                    // also we will do an auto sort to the towns. Output file must be sorted
                    if (!chose[3] && hasTownsInList(List)){
                        populationRadixSortForTowns(List) ;
                        printf("Towns have been sorted based on population.\n\n") ;
                        chose[4-1] = 1 ;
                    }
                }

                SaveToOutputFile(List) ;
                chose[option-1] = 1 ;
            }
        }

        displayMenu() ;
        printf("\nChoose one of the options above from 1-14: ") ;
        scanf("%d" , &option) ;
        getchar() ;
        printf("\n") ;

    }

    // if we exit the program, we will do an auto save.
    // Also, the information on the output file must be sorted.

    if (!chose[0]){
        printf("The information has not been loaded. The List is empty.\n\n") ;
    }
    else{
        if (!hasDistricts(List)){
            printf("The List is empty.\n\n") ;
        }
        else{
            if (!chose[2]){
                List = stringRadixSortForDistricts(List) ;
                printf("Districts have been sorted alphabetically.\n\n") ;
            }
            if (!chose[3] && hasTownsInList(List)){
                populationRadixSortForTowns(List) ;
                printf("Towns have been sorted based on population.\n\n") ;
            }
        }
        DeleteAllData(tempList) ; // we cant delete the tempList outside this else statement, since the tempList may be not created.
    }


    SaveToOutputFile(List) ;
    printf("Thank you for using the program. GoodBye.\n") ;

    DeleteAllData(List) ;

}

District *MakeEmpty(District *List){

    if (List != NULL){
        DeleteAllData(List) ;
    }

    List = (District*)malloc(sizeof(District)) ;

    if (List == NULL){
        printf("Out of memory!\n") ;
        return NULL ;
    }

    List->NextDistrict = NULL ;
    List->NextTown = NULL ;
    lastDistrict = List ; // the global.

    return List ;

}

District *MakeEmptyTempList(District *List){

    if (List != NULL){
        DeleteAllData(List) ;
    }

    List = (District *)malloc(sizeof(District)) ;

    if (List == NULL){
        printf("Out of memory!\n") ;
        return NULL ;
    }

    List->NextDistrict = NULL ;
    List->NextTown = NULL ;

    return List ;

}

void PrintAllData(District *List){

    if (!hasDistricts(List)){
        printf("Empty List.\n") ;
    }
    else{
        District *temp = List->NextDistrict ;
        while (temp != NULL){
            // Print the district and its population
            printf("%s District, Population = %d\n" , temp->district , temp->population) ;
            // print its towns
            PrintTowns(temp , List) ;
            temp = temp->NextDistrict ;
        }
    }

}

void DeleteAllData(District *List){

    DeleteAllDistricts(List) ;
    free(List) ;

}

int sizeOfList(District *List){

    int size=0 ;
    District *p = List->NextDistrict ;

    while (p != NULL){
        size++ ;
        p = p->NextDistrict ;
    }

    return size ;

}

District *copyList(District *List){

    District *tempList = NULL ;
    tempList = MakeEmptyTempList(tempList) ;

    District *district = List->NextDistrict ;
    District *tempLastDistrict = tempList ; // pointer to insert last in the tempList

    while (district != NULL){
        tempLastDistrict = InsertAndReturnLastDistrict(district->district , tempLastDistrict , tempList) ;
        Town *town = district->NextTown ;
        if (tempLastDistrict != NULL){
            InsertAllTowns(town , tempLastDistrict , tempList) ;
        }
        district = district->NextDistrict ;
    }

    return tempList ;

}

int hasDistricts(District *List){

    return List->NextDistrict != NULL ;

}

int IsLastDistrict(District *district , District *List){

    return district->NextDistrict == NULL ;

}

District *FindDistrict(char districtName[50] , District *List){

    // two pointers to search
    District *pFront = List->NextDistrict , *pBack = lastDistrict ;

    // n/2
    while (pFront != pBack && pBack->NextDistrict != pFront && strcmp(pFront->district , districtName) && strcmp(pBack->district , districtName)){
        pFront = pFront->NextDistrict ;
        pBack = pBack->PrevDistrict ;
    }

    if (pFront != NULL && !strcmp(pFront->district , districtName)){
        return pFront ;
    }
    else if (pBack != List && !strcmp(pBack->district , districtName)){
        return pBack ;
    }

    return NULL ; // district does not exist

}

void InsertDistrict(char districtName[50] , District *p , District *List){ // insert after district p

    District *temp = (District*)malloc(sizeof(District)) ;

    if (temp != NULL){ // it may be NULL because of out of memory
        strcpy(temp->district , districtName) ;
        temp->population = 0 ;
        temp->NextDistrict = p->NextDistrict ;
        if (p->NextDistrict != NULL){ // if we insert after the lastDistrict, we will not enter this if statement
            p->NextDistrict->PrevDistrict = temp ;
        }
        temp->PrevDistrict = p ;
        p->NextDistrict = temp ;
        temp->NextTown = NULL ;
        temp->lastTown = NULL ;
        temp->sortedTowns = 0 ;
        if ((IsLastDistrict(temp , List))){ // update the global pointer if temp is last
            lastDistrict = temp ;
        }
    }
    else{
        printf("Out of memory!\n") ;
    }

}

District *InsertAndReturnLastDistrict(char districtName[50] , District *tempLastDistrict , District *tempList){

    District *temp = (District*)malloc(sizeof(District)) ;

    if (temp != NULL){
        strcpy(temp->district , districtName) ;
        temp->population = 0 ;
        temp->NextDistrict = tempLastDistrict->NextDistrict ;
        temp->PrevDistrict = tempLastDistrict ;
        tempLastDistrict->NextDistrict = temp ;
        temp->NextTown = NULL ;
        temp->lastTown = NULL ;
        temp->sortedTowns = 0 ;
    }
    else{
        printf("Out of memory!\n") ;
    }

    return temp ;

}

void DeleteDistrict(District *district , District *List){

    // we will delete its towns first
    DeleteAllTowns(district , List) ;

    // update the global if it is last
    if (IsLastDistrict(district , List)){
        lastDistrict = district->PrevDistrict ;
    }

    district->PrevDistrict->NextDistrict = district->NextDistrict ;
    if (district->NextDistrict != NULL){
        district->NextDistrict->PrevDistrict = district->PrevDistrict ;
    }

    free(district) ;

}

void DeleteAllDistricts(District *List){

    District *district = List->NextDistrict , *temp ;

    while (district != NULL){
        temp = district->NextDistrict ;
        DeleteDistrict(district->district , List) ;
        district = temp ;
    }

}

void PrintDistricts(District *List){

    if (!hasDistricts(List)){
        printf("Empty List.\n") ;
    }
    else{
        District *p = List->NextDistrict ;
        while(p != NULL){
            printf("%s District, Population = %d.\n", p->district , p->population) ;
            p = p->NextDistrict ;
        }
    }
}

int hasTowns(District *district , District *List){

    return district->NextTown != NULL ;

}

int hasTownsInList(District *List){

    District *district = List->NextDistrict ;

    while (district != NULL){
        if (hasTowns(district , List)){
            return 1 ;
        }
        district = district->NextDistrict ;
    }

    return 0 ;

}

int IsLastTown(Town *town , District *district , District *List){

    return town->NextTown == NULL ;

}

Town *FindTown(char townName[50] , District *district , District *List){

    // two pointers to search from front and end
    Town *pFront = district->NextTown , *pBack = district->lastTown ;

    // n/2
    while (pFront != pBack && pBack->NextTown != pFront && strcmp(pFront->town , townName) && strcmp(pBack->town , townName)){
        pFront = pFront->NextTown ;
        pBack = pBack->PrevTown ;
    }

    if (pFront != NULL && !strcmp(pFront->town , townName)){
        return pFront ;
    }
    else if (pBack != NULL && pBack != district && !strcmp(pBack->town , townName)){
        return pBack ;
    }

    return NULL ; // town does not exist

}

void InsertTown(char townName[50] , int populationCount , Town *p , District *district , District *List){ // insert after town p in district

    Town *temp = (Town*)malloc(sizeof(Town)) ;

    if (temp != NULL){
        if (p == NULL){ // if the value of p is NULL (district->lastTown = NULL), then this district does not have any town, and we will insert the first town after district.
            strcpy(temp->town , townName) ;
            temp->population = populationCount ;
            district->population+=populationCount ;
            temp->NextTown = district->NextTown ;
            temp->PrevTown = district ;
            district->NextTown = temp ;
        }
        else{ // insert after town p
            strcpy(temp->town , townName) ;
            temp->population = populationCount ;
            district->population+=populationCount ;
            temp->NextTown = p->NextTown ;
            if (p->NextTown != NULL){ // if we insert after last node, we will not enter this if statement
                p->NextTown->PrevTown = temp ;
            }
            temp->PrevTown = p ;
            p->NextTown = temp ;
        }
        if (IsLastTown(temp , district , List)){
            district->lastTown = temp ;
        }
    }
    else{
        printf("Out of memory!\n") ;
    }

}

void InsertAllTowns(Town *town , District *district , District *List){

    while (town != NULL){
        InsertTown(town->town , town->population , district->lastTown , district , List) ; // insert last.
        town = town->NextTown ;
    }

}

void DeleteTown(Town *town , District *district , District *List){

    if (IsLastTown(town , district , List)){
        if (town->PrevTown == district){
            district->lastTown = NULL ;
        }
        else{
            district->lastTown = town->PrevTown ;
        }
    }

    district->population-=town->population ;

    if (town->PrevTown == district){
        district->NextTown = town->NextTown ;
    }
    else{
        town->PrevTown->NextTown = town->NextTown ;
    }

    if (town->NextTown != NULL) {
        town->NextTown->PrevTown = town->PrevTown ;
    }

    free(town) ;

}

void DeleteAllTowns(District *district , District *List){

    Town *temp = district->NextTown , *town ;

    while (temp != NULL){
        town = temp->NextTown ;
        DeleteTown(temp , district , List) ;
        temp = town ;
    }

}

int NumOfTowns(District *district , District *List){

    int size=0 ;
    Town *p = district->NextTown ;

    while (p != NULL){
        size++ ;
        p = p->NextTown ;
    }

    return size ;

}

void PrintTowns(District *district , District *List){

    if (!hasTowns(district , List)){
        printf("%s does not have any town.\n" , district->district) ;
    }
    else{
        Town* p = district->NextTown ;
        while(p != NULL){
            printf("%s, %d\n", p->town , p->population) ;
            p = p->NextTown ;
        }
    }

}

void PrintListAsFile(District *tempList){

    District *district = tempList->NextDistrict ;

    if (district == NULL){
        printf("The List is Empty. Input file is empty or it does not match the details of the program.\n") ;
    }

    while (district != NULL){
        Town *town = district->NextTown ;
        while (town != NULL){
            // print the data as in the input file format
            printf("%s | %s | %d\n" , district->district , town->town , town->population) ;
            town = town->NextTown ;
        }
        district = district->NextDistrict ;
    }

}

void readInputFileAndInsert(District *List){

    FILE *fp = fopen("districts.txt" , "r") ;

    if (fp == NULL){
        printf("The file does not exist!\n") ;
        return ;
    }

    char str[100] ; int Line=1 ;
    while (fgets(str , sizeof(str) , fp)){

        int lengthOfStr = strLen(str) ;

        str[lengthOfStr] = '\0' ;

        if (lengthOfStr > MAX_LENGTH){
            printf("String %d does not match the details of program. Length must be less than or equal 50.\n" , Line++) ;
            continue ;
        }

        int i=0 ;
        while (i < lengthOfStr && str[i] == ' '){ // skip the spaces at the beginning of the string
            i++ ;
        }

        if (i == lengthOfStr){
            printf("String %d does not match the details of program. Empty Line.\n", Line++) ;
            continue ;
        }

        if (!isalpha(str[i])){
            printf("String %d does not match the details of program. Could not find a district.\n", Line++) ;
            continue ;
        }

        else{

            char district[50] , town[50] , population[50] ; int index=0 ;

            while (i < lengthOfStr && str[i] != '|'){ // read the name of district.
                if (index > 0 && district[index-1] == ' ' && str[i] == ' '){ // if the last char in district is space and the new char is also space, we will skip it.
                    while (i < lengthOfStr && str[i] == ' '){
                        i++ ;
                    }
                    continue ;
                }
                district[index++] = str[i++] ;
            }

            if (index > 0 && district[index-1] == ' '){ // the last char may be ' ' if there is a space before the first '|'
                district[index-1] = '\0' ;
            }
            else{
                district[index] = '\0' ;
            }

            i++ ; // to skip the first '|'

            while (i < lengthOfStr && str[i] == ' '){ // skip the spaces after the first '|'.
                i++ ;
            }

            if (i == lengthOfStr || !isalpha(str[i])){
                printf("String %d does not match the details of program. Could not find a town for district.\n", Line++) ;
                continue ;
            }

            index=0 ;
            while (i < lengthOfStr && str[i] != '|'){ //read the name of the town.
                if (index > 0 && town[index-1] == ' ' && str[i] == ' '){ // same as the name of the district.
                    while (i < lengthOfStr && str[i] == ' '){
                        i++ ;
                    }
                    continue ;
                }
                town[index++] = str[i++] ;
            }

            if (index > 0 && town[index-1] == ' '){ // the last char may be ' ' if there is a space after the name of the town
                town[index-1] = '\0' ;
            }
            else{
                town[index] = '\0' ;
            }

            i++ ; // to skip the '|'

            while (i < lengthOfStr && str[i] == ' '){ // skip the spaces after the second '|'.
                i++ ;
            }

            if (i == lengthOfStr || !isdigit(str[i])){
                printf("The string %d does not match the details of program. Could not find the population of a town.\n", Line++) ;
                continue;
            }

            index=0 ;
            while (i < lengthOfStr && isdigit(str[i])){
                population[index++] = str[i++] ;
            }
            population[index] = '\0' ;

            while (i < lengthOfStr && str[i] == ' '){ // skip the spaces after the number.
                i++ ;
            }

            if (i != lengthOfStr) { // if there is a text after the number(population).
                printf("The string %d does not match the details of program.\n", Line++) ;
                continue;
            }

            insertInfoToList(List , district , town , population) ; Line++ ;

        }
    }

    fclose(fp) ;

}

void insertInfoToList(District *List , char districtName[50] , char townName[50] , char population[50]){

    District *district = FindDistrict(districtName , List) ;

    int populationCount = atoi(population) ; // convert from string to int.

    if (district != NULL){ // the district is in the list
        Town *town = FindTown(townName , district , List) ;
        if (town != NULL){ // if there is a town with the same name in the same district in the input file, then we will delete it and insert the new one.
            DeleteTown(town , district , List) ;
        }

        InsertTown(townName , populationCount , district->lastTown , district , List) ;
    }

    else{
        InsertDistrict(districtName , lastDistrict , List) ; // insert last to the list
        InsertTown(townName , populationCount , lastDistrict->lastTown , lastDistrict , List) ; // insert the town
    }

}

void SaveToOutputFile(District *List){

    FILE *fp = fopen("sorted_districts.txt" , "w") ;

    if (fp == NULL){
        printf("The file does not exist!\n") ;
        return ;
    }

    if (!hasDistricts(List)){
        fprintf(fp , "Empty List.") ;
    }
    else{
        District *district = List->NextDistrict ;
        while (district != NULL){

            fprintf(fp , "%s District, Population = %d.\n" , district->district , district->population) ;

            if (!hasTowns(district , List)){
                fprintf(fp , "%s does not have towns.\n" , district->district) ;
            }
            else{
                Town* town = district->NextTown ;
                while(town != NULL){
                    fprintf(fp , "%s, %d.\n", town->town , town->population) ;
                    town = town->NextTown ;
                }
            }

            district = district->NextDistrict ;
        }
    }

    printf("The List has been saved to the output file.\n\n") ;

    fclose(fp) ;

}

int isdigit(char c){

    return (c >= '0' && c <= '9') ;

}

int isalpha(char c){

    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ;

}

int strLen(char str[100]){

    int size=0 ;
    for (int i = 0 ; str[i] != '\0' && str[i] != '\n' ; i++){
        size++ ;
    }

    return size ;

}

int getMaxChars(District *List){

    District *temp = List->NextDistrict ;

    int maxChar=0 ;
    while (temp != NULL){
        char str[50] ;
        strcpy(str , temp->district) ;
        int size = strLen(str) ;
        if (size > maxChar){
            maxChar = size ;
        }
        temp = temp->NextDistrict ;
    }

    return maxChar ;

}

int getMaxDigits(District *district , District *List){ // get the maximum number of digits for the population of the towns

    int maxPopulation=0 ;

    Town *tempTown = district->NextTown ;

    // get the maximum population
    while (tempTown != NULL){
        if (tempTown->population > maxPopulation){
            maxPopulation = tempTown->population ;
        }
        tempTown = tempTown->NextTown ;
    }

    // get the number of the digits for the maximum population
    int counter = 0 ;
    while (maxPopulation != 0){
        maxPopulation/=10 ;
        counter++ ;
    }

    return counter ;

}

District *stringRadixSortForDistricts(District *List){

    int maxChars = getMaxChars(List) ;

    Alphabetical *alpha[55] ; // from index 0 to 54 as follows: ('\0' a A b B c C ...... y Y z Z ' ' '-'). the first index ('\0') is for the words which its size is less than the maxChars
    Alphabetical *lastDistrictInAlpha[55] ; // pointer to the lastDistrict in each alpha.

    for (int i = 0 ; i < 55 ; i++){
        alpha[i] = NULL ;
        alpha[i] = MakeEmptyTempList(alpha[i]) ;
        lastDistrictInAlpha[i] = alpha[i] ;
    }

    int Size = sizeOfList(List) ;
    while (maxChars != 0){
        District *district = List->NextDistrict ;

        for (int i = 0 ; i < Size ; i++){
            char str[50] ;
            strcpy(str , district->district) ;

            Town *tempTown = district->NextTown ;

            int sizeOfString = strLen(str) ;
            if (sizeOfString >= maxChars){
                char c = str[maxChars-1] ;

                if (c >= 'A' && c <= 'Z'){
                    int index = (c-'A')+(c-'A')+2 ; // the capital letters are in even indices, and this equation will get the index.

                    lastDistrictInAlpha[index] = InsertAndReturnLastDistrict(str , lastDistrictInAlpha[index] , alpha[index]) ; // insert the district to alpha (at last).
                    if (lastDistrictInAlpha[index] != NULL){ // it may be NULL because of out of memory.
                        lastDistrictInAlpha[index]->sortedTowns = district->sortedTowns ; // towns will stay sorted if they are sorted
                        InsertAllTowns(tempTown , lastDistrictInAlpha[index] , alpha[index]) ; // move all the towns of district to alpha.
                    }
                }
                else if (c >= 'a' && c <= 'z'){
                    int index = (c-'a')+(c-'a')+1 ; // the small letters are in odd indices, and this equation will get the index.

                    // insert last in alpha and return the inserted district
                    lastDistrictInAlpha[index] = InsertAndReturnLastDistrict(str , lastDistrictInAlpha[index] , alpha[index]) ;
                    if (lastDistrictInAlpha[index] != NULL){
                        lastDistrictInAlpha[index]->sortedTowns = district->sortedTowns ;
                        InsertAllTowns(tempTown , lastDistrictInAlpha[index] , alpha[index]) ;
                    }
                }
                else if(c == ' '){
                    lastDistrictInAlpha[53] = InsertAndReturnLastDistrict(str , lastDistrictInAlpha[53] , alpha[53]) ;

                    if (lastDistrictInAlpha[53] != NULL){
                        lastDistrictInAlpha[53]->sortedTowns = district->sortedTowns ;
                        InsertAllTowns(tempTown , lastDistrictInAlpha[53] , alpha[53]) ;
                    }
                }
                else{ // c will be '-'
                    lastDistrictInAlpha[54] = InsertAndReturnLastDistrict(str , lastDistrictInAlpha[54] , alpha[54]) ;

                    if (lastDistrictInAlpha[54] != NULL){
                        lastDistrictInAlpha[54]->sortedTowns = district->sortedTowns ;
                        InsertAllTowns(tempTown , lastDistrictInAlpha[54] , alpha[54]) ;
                    }
                }
            }
            else{ // the word is less than the max char
                lastDistrictInAlpha[0] = InsertAndReturnLastDistrict(str , lastDistrictInAlpha[0] , alpha[0]) ;

                if (lastDistrictInAlpha[0] != NULL){
                    lastDistrictInAlpha[0]->sortedTowns = district->sortedTowns ;
                    InsertAllTowns(tempTown , lastDistrictInAlpha[0] , alpha[0]) ;
                }
            }

            district = district->NextDistrict ;
        }

        // clear the original List
        DeleteAllDistricts(List) ;

        // now we will insert from alpha to the original List
        for (int i = 0 ; i < 55 ; i++){

            int sizeOfAlpha = sizeOfList(alpha[i]) ;
            Alphabetical *tempAlpha = alpha[i]->NextDistrict ;

            for (int j = 0 ; j < sizeOfAlpha ; j++){
                InsertDistrict(tempAlpha->district , lastDistrict , List) ; // insert last.

                lastDistrict->sortedTowns = tempAlpha->sortedTowns ; // it will stay sorted if the towns were sorted

                Town *tempTown = tempAlpha->NextTown ;
                InsertAllTowns(tempTown , lastDistrict , List) ;
                tempAlpha = tempAlpha->NextDistrict ;
            }
        }

        District *temp = lastDistrict ; // this temp will save the true value of the global lastDistrict.
        for (int i = 0 ; i < 55 ; i++){
            // clear each index in alpha
            DeleteAllDistricts(alpha[i]) ;
            lastDistrictInAlpha[i] = alpha[i] ;
        }
        lastDistrict = temp ;

        maxChars-- ;
    }

    for (int i = 0 ; i < 55 ; i++){
        free(alpha[i]) ;
    }

    return List ;

}

void populationRadixSortForTowns(District *List){

    int Size = sizeOfList(List) ;

    District *tempDistrict = List->NextDistrict , *tempLastDistrict = lastDistrict ; // the tempLastDistrict will save the ture value of the global lastDistrict.

    for (int i = 0 ; i < Size ; i++){

        if (tempDistrict->sortedTowns){ // continue, if the towns are sorted in this district.
            tempDistrict = tempDistrict->NextDistrict ;
            continue ;
        }

        int maxDigits = getMaxDigits(tempDistrict , List) , divideBy = 1 , maxDivide = pow(10 , maxDigits-1) ;

        int districtSize = NumOfTowns(tempDistrict , List) ;

        Numbers *number[10] ; // digits from 0 - 9
        for (int j = 0 ; j < 10 ; j++){
            number[j] = NULL ;
            number[j] = MakeEmptyTempList(number[j]) ;
            InsertDistrict(tempDistrict->district , number[j] , number[j]) ;
        }

        while (divideBy <= maxDivide){

            Town *tempTown = tempDistrict->NextTown ;

            for (int j = 0 ; j < districtSize ; j++){
                int digit = (tempTown->population/divideBy)%10 ;

                InsertTown(tempTown->town , tempTown->population , number[digit]->NextDistrict->lastTown , number[digit]->NextDistrict , number[digit]) ;
                tempTown = tempTown->NextTown ;
            }

            // clear the district from its towns
            DeleteAllTowns(tempDistrict , List) ;

            // move the towns from Number each district
            for (int j = 0 ; j < 10 ; j++){
                Numbers *tempDistrict2 = number[j]->NextDistrict ;
                Town *tempTown2 = tempDistrict2->NextTown ;
                int sizeOfNumber = NumOfTowns(tempDistrict2 , number[j]) ;
                for (int k = 0 ; k < sizeOfNumber ; k++) {
                    InsertTown(tempTown2->town, tempTown2->population, tempDistrict->lastTown, tempDistrict, List);
                    tempTown2 = tempTown2->NextTown ;
                }
            }

            for (int j = 0 ; j < 10 ; j++){
                DeleteAllTowns(number[j]->NextDistrict , number[j]) ;
            }
            divideBy*=10 ;
        }

        tempDistrict->sortedTowns = 1 ;

        tempDistrict = tempDistrict->NextDistrict ;

        for (int j = 0 ; j < 10 ; j++){
            DeleteAllData(number[j]) ;
        }

        lastDistrict = tempLastDistrict ;

    }

}

void displayMenu(){

    printf("1- Load the input file.\n"
           "2- Print the loaded information before sorting(as in the input file format).\n"
           "3- Sort the districts alphabetically.\n"
           "4- Sort the towns for each district based on population in ascending order.\n"
           "5- Print the sorted information.\n"
           "6- Add a new district to the list of sorted districts.\n"
           "7- Add a new town to a certain district.\n"
           "8- Delete a town from a specific district.\n"
           "9- Delete a complete district.\n"
           "10- Calculate the population of Palestine, the max and min town population.\n"
           "11- Print the districts and their total population (without towns details).\n"
           "12- Change the population of a town.\n"
           "13- Save to output file.\n"
           "14- Exit.\n") ;

}
