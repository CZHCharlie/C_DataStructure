/*
Description
There is a famous railway station in PopPush City. Country there is incredibly hilly. The station was built in last century. Unfortunately, funds were extremely limited that time. It was possible to establish only a surface track. Moreover, it turned out that the station could be only a dead-end one (see picture) and due to lack of available space it could have only one track.
The local tradition is that every train arriving from the direction A continues in the direction B with coaches reorganized in some way. 
Assume that the train arriving from the direction A has N <= 100 coaches£¨³µÏá£©numbered in increasing order 1, 2, ..., N. Help him and write a program that decides whether it is possible to get the required order of coaches. 
You can assume that single coaches can be disconnected from the train before they enter the station and that they can move themselves until they are on the track in the direction B. You can also suppose that at any time there can be located as many coaches as necessary in the station. But once a coach has entered the station it cannot return to the track in the direction A and also once it has left the station in the direction B it cannot return back to the station.

Input
The input consists of blocks of lines. Each block except the last describes one train and possibly more requirements for its reorganization. In the first line of the block there is the integer N described above. In each of the next lines of the block there is a permutation of 1, 2, ..., N. The last line of the block contains just 0. 
The last block consists of just one line containing 0.

Output
The output contains the lines corresponding to the lines with permutations in the input. A line of the output contains Yes if it is possible to marshal the coaches in the order required on the corresponding line of the input. Otherwise it contains No. In addition, there is one empty line after the lines corresponding to one block of the input. There is no line in the output corresponding to the last "null" block of the input.

Sample Input
5
5 4 1 2 3
1 2 3 4 5
0
6
6 5 4 3 2 1
1 2 3 5 6 4
6 3 2 5 4 1
0
10
3 1 5 8 2 6 9 4 10 7
4 6 10 9 2 1 8 7 3 5
6 9 8 7 5 4 3 2 10 1
6 9 8 7 5 4 3 10 2 1
6 9 8 7 5 4 10 3 2 1
6 9 10 8 7 5 4 3 2 1
6 10 9 8 7 5 4 3 2 1
7 6 5 4 3 2 1 8 9 10
7 6 5 4 3 2 1 8 10 9
4 6 9 7 10 1 5 8 2 3
10 8 1 6 5 7 9 4 3 2
0
0

Sample Output
No
Yes
---
Yes
Yes
No
---
No
No
Yes
Yes
Yes
Yes
Yes
Yes
Yes
No
No
---
*/

#include <stdio.h>
#include <stdbool.h>
 
#define element_type int
 
typedef struct stackNode* STACKNODEPTR;
typedef struct stackNode{
    element_type number;
    STACKNODEPTR nextPtr;
    STACKNODEPTR previousPtr;
}STACKNODE;
 
void insertNode(STACKNODEPTR*, STACKNODEPTR*, element_type);
void deleteNode(STACKNODEPTR*, STACKNODEPTR*);
element_type lastNumber(STACKNODEPTR*);
 
int main()
{
    int n;
    bool flag;
    scanf("%d", &n);
    getchar();
    while (n != 0) {
        flag = true;
        while (flag) {
            STACKNODEPTR startPtr = NULL, endPtr = NULL;
            int OUT[100] = {0};
            scanf("%d", OUT);
            if (OUT[0] == 0) {
                printf("---\n");
                flag = false;
            }
            else {
                for (int i = 1; i <= n - 1; i++)
                    scanf("%d", OUT + i);
                int count_in = 1, count_out = 0;
                for (count_in = 1; count_in <= n; count_in++) {
                    insertNode(&startPtr, &endPtr, count_in);
                    while (OUT[count_out] == lastNumber(&endPtr) && count_out <= n - 1) {
                        deleteNode(&startPtr, &endPtr);
                        count_out++;
                    }
                }
                if (endPtr == NULL)
                    printf("Yes\n");
                else
                    printf("No\n");
            }
        }
        scanf("%d", &n);
        getchar();
    }
 
    return 0;
}
 
 
/**
 * the first parameter is the address of the start pointer
 * the second parameter is the address of the end pointer
 * the third parameter is the character we have read
 *
 * this function add a new node at the end of the list
 * this function has no return
 */
void insertNode(STACKNODEPTR* sPtr, STACKNODEPTR* ePtr, element_type n)
{
    STACKNODEPTR newPtr = malloc(sizeof(STACKNODE));
    if (newPtr != NULL){
        //if the list hasn't any node
        if (*sPtr == NULL) {
            (*sPtr) = newPtr;
            (*ePtr) = newPtr;
            newPtr->number = n;
            newPtr->nextPtr = NULL;
            newPtr->previousPtr = NULL;
        }
        //if the list has at least one node
        else {
            newPtr->number = n;
            newPtr->nextPtr = NULL;
            newPtr->previousPtr = (*ePtr);
            (*ePtr)->nextPtr = newPtr;
            (*ePtr) = newPtr;
        }
    }
}
 
/**
 * the first parameter is the address of the start pointer
 * the second parameter is the address of the end pointer
 *
 * this function delete the latest node at the end of the list
 * this function has no return
 */
void deleteNode(STACKNODEPTR* sPtr, STACKNODEPTR* ePtr)
{
    //if the list has just one node
    if ((*ePtr)->previousPtr == NULL) {
        (*ePtr)->number = 0;
        free(*ePtr);
        (*ePtr) = NULL;
        (*sPtr) = NULL;
    }
    //if the list has at least two nodes
    else {
        STACKNODEPTR currentPtr = (*ePtr);
        (*ePtr) = (*ePtr)->previousPtr;
        (*ePtr)->nextPtr = NULL;
        currentPtr->number = 0;
        currentPtr->previousPtr = NULL;
        free(currentPtr);
    }
}
 
/**
 * the only parameter is the address of end pointer
 *
 * this function return the last number
 */
element_type lastNumber(STACKNODEPTR* ePtr)
{
    if (*ePtr == NULL)
        return 0;
    else
        return (*ePtr)->number;
}