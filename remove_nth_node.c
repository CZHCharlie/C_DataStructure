/*
Description
Given a linked list, remove the nth node from the end of list and return its head. (0 <= n <= list length)

Input
You will have several groups of input. The first line indicates the number of inputs.
Each line of inputs contains a string of number, and an index of number need to remove, seperated by a space.

Output
Please output the sting after removing the required number.

Sample Input
2
20171128 4
515021910497 5

Sample Output
2017128
51502190497
*/

#include <stdio.h>
#include <stdbool.h>
 
typedef struct digit* DIGITPTR;
typedef struct digit{
    char n;
    DIGITPTR nextPtr;
    DIGITPTR previousPtr;
}DIGIT;
 
DIGITPTR insert(DIGITPTR*, DIGITPTR*, DIGITPTR, int);
void removeDigit(DIGITPTR*, DIGITPTR*, int, int);
void print(DIGITPTR);
void freeList(DIGITPTR);
 
int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 1; i <= n; i++) {
        //Initialization
        DIGITPTR startPtr = NULL, endPtr = NULL, currentPtr = NULL;
 
        //read the integer
        int count = 0;
        char c = getchar();
        while (c != ' ') {
            currentPtr = insert(&startPtr, &endPtr, currentPtr, c - '0');
            count++;
            c = getchar();
        }
 
        //remove the kth number
        int k;
        scanf("%d", &k);
        getchar();
        //n = 0 means we just print it out
        if (k != 0)
            removeDigit(&startPtr, &endPtr, k, count);
        print(startPtr);
        freeList(startPtr);
    }
 
    return 0;
}
 
/**
 * the first parameter is the address of the start pointer
 * the second parameter is the address of the end pointer
 * the third parameter is the pointer indicating where we are going to add a new node
 * the fourth parameter is the character we have read
 *
 * this function add a new node at this end of the list
 * this function return the a new current pointer indicating where we are going to add a new node next
 */
DIGITPTR insert(DIGITPTR* sPtr, DIGITPTR* ePtr, DIGITPTR currentPtr, int n)
{
    DIGITPTR newPtr = malloc(sizeof(DIGIT));
    if (newPtr != NULL){
        //if the list hasn't any node
        if (*sPtr == NULL) {
            *sPtr = newPtr;
            *ePtr = newPtr;
            newPtr->n = n;
            newPtr->nextPtr = NULL;
            newPtr->previousPtr = NULL;
        }
        //if the list has at least one node
        else {
            currentPtr->nextPtr = newPtr;
            *ePtr = newPtr;
            newPtr->n = n;
            newPtr->nextPtr = NULL;
            newPtr->previousPtr = currentPtr;
        }
        return newPtr;
    }
}
 
/**
 * the first parameter is the address of the start pointer
 * the second parameter is the address of the end pointer
 * the third parameter is the position of which node we are going to delete
 * the fourth parameter is the long of the integer
 *
 * this function delete the k-th node from the end of the list
 * this function has no return
 */
void removeDigit(DIGITPTR* sPtr, DIGITPTR* ePtr, int k, int count)
{
    //the list has just one node
    if (count == 1) {
        free(*sPtr);
        (*sPtr) = NULL;
        (*ePtr) = NULL;
    }
    //we delete the last node
    else if (k == 1) {
        (*ePtr) = (*ePtr)->previousPtr;
        (*ePtr)->nextPtr = NULL;
    }
    //we delete the first node
    else if (k == count) {
        (*sPtr) = (*sPtr)->nextPtr;
        (*sPtr)->previousPtr = NULL;
    }
    //we compare k with count / 2 in order to delete the k-th node faster (k >= 3)
    else if (k <= count / 2) {
        DIGITPTR currentPtr1 = (*ePtr);
        for (int i = 1; i <= k - 1; i++) {
            currentPtr1 = currentPtr1->previousPtr;
        }
        currentPtr1->previousPtr->nextPtr = currentPtr1->nextPtr;
        currentPtr1->nextPtr->previousPtr = currentPtr1->previousPtr;
    }
    else {
        DIGITPTR currentPtr2 = (*sPtr);
        for (int i = 1; i <= count - k; i++) {
            currentPtr2 = currentPtr2->nextPtr;
        }
        currentPtr2->nextPtr->previousPtr = currentPtr2->previousPtr;
        currentPtr2->previousPtr->nextPtr = currentPtr2->nextPtr;
    }
}
 
/**
 * the only parameter is the start pointer
 *
 * this function print every node's number from the start pointer to the end of the list
 * this function has no return
 */
void print(DIGITPTR startPtr)
{
    if (startPtr == NULL)
        printf("0\n");
    else {
        bool start = false;
        DIGITPTR currentPtr = startPtr;
        while (currentPtr != NULL) {
            printf("%d", currentPtr->n);
            currentPtr = currentPtr->nextPtr;
        }
        printf("\n");
    }
}
 
/**
 * the only parameter is the start pointer
 *
 * this function initialize every node's data in order to avoid wild pointer,
 * as well as free their memory space
 * this function has no return
 */
void freeList(DIGITPTR startPtr)
{
    DIGITPTR tempPtr1 = startPtr, tempPtr2 = NULL;
    while (tempPtr1 != NULL) {
        tempPtr2 = tempPtr1->nextPtr;
        tempPtr1->n = 0;
        tempPtr1->nextPtr = NULL;
        tempPtr1->previousPtr = NULL;
        free(tempPtr1);
        tempPtr1 = tempPtr2;
    }
}