/*
Description
The problem is to multiply two positive big integers X, Y. (X, Y >= 0, Integer)
Requirement: Test data is very big, therefore you must use a linked list to store an any big integer.

Input
The input contains 2n+1 lines.
The first line contains the number of the case n.
Then, the input will consist of a set of pairs of lines. Each line in pair contains one multiple.

Output
For each input pair of lines the output line should consist one integer the product.

Sample Input
3
12
12
2
222222222222222222222222
987654321123456789
2

Sample Output
144
444444444444444444444444
1975308642246913578
*/


#include <stdio.h>
#include <stdbool.h>

struct digit
{
    int n;
    struct DIGIT* nextPtr;
    struct DIGIT* previousPtr;
};
typedef struct digit DIGIT;
typedef DIGIT* DIGITPTR;

DIGITPTR insert(DIGITPTR*, DIGITPTR*, DIGITPTR, int);
void add(DIGITPTR*, DIGITPTR*, DIGITPTR, DIGITPTR);
DIGITPTR add_single(DIGITPTR*, DIGITPTR*, DIGITPTR, int);
void add_carry(DIGITPTR);
void print(DIGITPTR);

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 1; i <= n; i++) {
        //Initialization
        int count1 = 0, count2 = 0;
        DIGITPTR startPtr1 = NULL, startPtr2 = NULL, endPtr1 = NULL, endPtr2 = NULL, currentPtr = NULL;
        currentPtr = startPtr1;

        //read the first big integer
        char c = getchar();
        while (c != '\n') {
            currentPtr = insert(&startPtr1, &endPtr1, currentPtr, c - '0');
            count1++;
            c = getchar();
        }

        //read the second big integer
        currentPtr = startPtr2;
        c = getchar();
        while (c != '\n') {
            currentPtr = insert(&startPtr2, &endPtr2, currentPtr, c - '0');
            count2++;
            c = getchar();
        }

        //add these two big integers
        DIGITPTR resSPtr = NULL, resEPtr = NULL;
        if (count1 >= count2)
            add(&resSPtr, &resEPtr, startPtr1, startPtr2);
        else
            add(&resSPtr, &resEPtr, startPtr2, startPtr1);

        //print the result
        print(resSPtr);
        printf("\n");
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
 * the first parameter is the address of the result's start pointer
 * the second parameter is the address of the result's end pointer
 * the third parameter is the first big integer's start pointer
 * the fourth parameter is the second big integer's start pointer
 *
 * this function multiply two big integers
 * this function has no return
 */
void add(DIGITPTR* resSPtr, DIGITPTR* resEPtr, DIGITPTR startPtr1, DIGITPTR startPtr2)
{
    DIGITPTR currentPtr = NULL, currentPtr1 = NULL, currentPtr2 = startPtr2, tempPtr = NULL;
    int mult1, mult2;
    while (currentPtr2 != NULL) {
        //I'm also confused
        mult2 = currentPtr2->n;
        currentPtr1 = startPtr1;
        tempPtr = currentPtr;
        tempPtr = add_single(resSPtr, resEPtr, tempPtr, 0);
        while (currentPtr1 != NULL) {
            mult1 = currentPtr1->n;
            tempPtr = add_single(resSPtr, resEPtr, tempPtr, mult1 * mult2);
            currentPtr1 = currentPtr1->nextPtr;
        }
        if (currentPtr == NULL)
            currentPtr = *resSPtr;
        else
            currentPtr = currentPtr->nextPtr;
        currentPtr2 = currentPtr2->nextPtr;
    }
    add_carry(*resEPtr);
}

/**
 * the first parameter is the address of the result's start pointer
 * the second parameter is the address of the result's end pointer
 * the third parameter is the pointer indicating where we are going to operate
 * the fourth parameter is the number we are going to operate
 *
 * this function is the cell of add function, it just add one number
 * this function return a new pointer indicating where we are going to operate next
 */
DIGITPTR add_single(DIGITPTR* resSPtr, DIGITPTR* resEPtr, DIGITPTR tempPtr,int result)
{
    //if it is at the end of the result list, we need to add another new node at the end of the list
    if (tempPtr == NULL || tempPtr->nextPtr == NULL)
        return insert(resSPtr, resEPtr, tempPtr, result);
    //otherwise it is simple
    else {
        DIGITPTR storePtr = tempPtr->nextPtr;
        storePtr->n += result;
        return tempPtr->nextPtr;
    }
}

/**
 * the only parameter is the result's end pointer
 *
 * this function keep every node's number n < 10, in order to print
 * this function has no return
 */
void add_carry(DIGITPTR resEPtr)
{
    DIGITPTR currentPtr = resEPtr;
    int carry = 0;
    //this condition means that we don't need to worry about whether the first node's n >= 10
    while (currentPtr->previousPtr !=NULL) {
        currentPtr->n += carry;
        carry = currentPtr->n / 10;
        currentPtr->n = currentPtr->n - 10 * carry;
        currentPtr = currentPtr->previousPtr;
    }
    //but there is still possible that the second node pass on a carry to the first node
    currentPtr->n += carry;
}

/**
 * the only parameter is the start pointer
 *
 * this function print every node's number from the start pointer to the end of the list
 * this function has no return
 */
void print(DIGITPTR startPtr)
{
    DIGITPTR currentPtr = startPtr;
    //just make sure 0 * 0 = 0 and 10 * 10 = 100 instead of 10 * 10 = 0100
    bool start = false;
    while (currentPtr != NULL) {
        if (currentPtr->nextPtr == NULL)
            printf("%d", currentPtr->n);
        else if (start || currentPtr->n) {
            printf("%d", currentPtr->n);
            start = true;
        }
        currentPtr = currentPtr->nextPtr;
    }
}
