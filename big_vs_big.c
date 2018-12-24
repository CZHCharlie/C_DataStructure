#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_EXPR 200

typedef struct listNode* LISTNODEPTR;
typedef struct listNode{
    LISTNODEPTR nextPtr;
    LISTNODEPTR previousPtr;
    double n;
    char OP;
}LISTNODE;

typedef struct stackOP* STACKOPPTR;
typedef struct stackOP{
    char OP;
    STACKOPPTR nextPtr;
    STACKOPPTR previousPtr;
}STACKOP;


//general functions
void initListNode(LISTNODEPTR);
void initStackNode(STACKOPPTR);
void readList(LISTNODEPTR*, LISTNODEPTR*, char*);
double calculate(LISTNODEPTR*, LISTNODEPTR*);
void print(double);

//functions about reading numbers
int readNUM(LISTNODEPTR*, LISTNODEPTR*, char*, int);
bool ISNegative(char*, int);

//functions about determining operation's order
void readOP(LISTNODEPTR*, LISTNODEPTR*, STACKOPPTR*, STACKOPPTR*, char);
void creatOP(LISTNODEPTR*, LISTNODEPTR*, char);
bool ISPOPOP(STACKOPPTR*, STACKOPPTR*, char);
int scoreOP(char);
void pushOP(STACKOPPTR*, STACKOPPTR*, char);
char popOP(STACKOPPTR*, STACKOPPTR*);
bool ISOP(char);


int main()
{
    bool quit = false;
    char expr[MAX_EXPR] = {0};
    scanf("%s", expr);
    if (expr[0] == '0' && expr[1] == '\0')
        quit = true;
    while (quit == false) {
        LISTNODEPTR sPtr = NULL, ePtr = NULL;
        readList(&sPtr, &ePtr, expr);
        //print(sPtr);
        print(calculate(&sPtr, &ePtr));

        for (int i = 0; i <= MAX_EXPR - 1; i++)
            expr[i] = '\0';
        scanf("%s", expr);
        if (expr[0] == '0' && expr[1] == '\0')
            quit = true;
    }
    return 0;
}

void initListNode(LISTNODEPTR targetPtr)
{
    targetPtr->n = 0;
    targetPtr->OP = '\0';
    targetPtr->nextPtr = NULL;
    targetPtr->previousPtr = NULL;
}

void initStackNode(STACKOPPTR targetPtr)
{
    targetPtr->OP = '\0';
    targetPtr->nextPtr = NULL;
    targetPtr->previousPtr = NULL;
}


//read everything and create the polish notation expression list
void readList(LISTNODEPTR* sPtr, LISTNODEPTR* ePtr, char* expr)
{
    int pos = 0;
    STACKOPPTR sOPPtr = NULL, eOPPtr = NULL;

    while (expr[pos] != '\n' && expr[pos] != '\0') {
        LISTNODEPTR newListNode = malloc(sizeof(LISTNODE));
        if (ISOP(expr[pos]) == true && ISNegative(expr, pos) == false)
            readOP(sPtr, ePtr, &sOPPtr, &eOPPtr, expr[pos++]);
        else
            pos = readNUM(sPtr, ePtr, expr, pos);
    }
    while (eOPPtr != NULL)
        creatOP(sPtr, ePtr, popOP(&sOPPtr, &eOPPtr));
    //add two nodes: 0 + at the end of the list
    LISTNODEPTR newNodePtr = malloc(sizeof(LISTNODE));
    initListNode(newNodePtr);
    newNodePtr->previousPtr = (*ePtr);
    (*ePtr)->nextPtr = newNodePtr;
    (*ePtr) = newNodePtr;

    newNodePtr = malloc(sizeof(LISTNODE));
    initListNode(newNodePtr);
    newNodePtr->OP = '+';
    newNodePtr->previousPtr = (*ePtr);
    (*ePtr)->nextPtr = newNodePtr;
    (*ePtr) = newNodePtr;
}

//deal with the expression established by polish notation
double calculate(LISTNODEPTR* sPtr, LISTNODEPTR* ePtr)
{
    LISTNODEPTR currentPtr = (*sPtr);
    while (currentPtr != NULL) {
        while (currentPtr->OP == '\0')
            currentPtr = currentPtr->nextPtr;

        LISTNODEPTR tempPtr = currentPtr->previousPtr;
        switch (currentPtr->OP) {
        case '+':
            tempPtr->previousPtr->n += tempPtr->n;
            break;
        case '-':
            tempPtr->previousPtr->n -= tempPtr->n;
            break;
        case '*':
            tempPtr->previousPtr->n *= tempPtr->n;
            break;
        case '/':
            tempPtr->previousPtr->n /= tempPtr->n;
        default:
            break;
        }
        //delete the second number node
        tempPtr->previousPtr->nextPtr = currentPtr;
        currentPtr->previousPtr = tempPtr->previousPtr;
        initListNode(tempPtr);
        free(tempPtr);
        //delete the OP node
        if (currentPtr->nextPtr == NULL) {
            (*ePtr) = currentPtr->previousPtr;
            (*ePtr)->nextPtr = NULL;
            initListNode(currentPtr);
            free(currentPtr);
            currentPtr = NULL;
        }
        else {
            currentPtr->previousPtr->nextPtr = currentPtr->nextPtr;
            currentPtr->nextPtr->previousPtr = currentPtr->previousPtr;
            tempPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
            initListNode(tempPtr);
            free(tempPtr);
        }
    }
    return (*sPtr)->n;
}

//print the result
void print(double n)
{
    double absn;
    if (n < 0) {
        absn = fabs(n);
        printf("-");
    }
    else
        absn = n;
    int INT = floor(absn);
    if (INT == absn)
        printf("%d", INT);
    else {
        double DIC = absn - INT;
        printf("%d.", INT);
        //precision 10e-8
        int temp = floor(DIC * 1000000);
        while (temp % 10 == 0)
            temp /= 10;
        printf("%d", temp);
    }
    printf("\n\n");
}

//deal with a number
int readNUM(LISTNODEPTR* sPtr, LISTNODEPTR* ePtr, char* expr, int pos)
{
    double number = 0;
    double k = 0.1;
    bool decimal = false;
    int sign = 1;
    if (expr[pos] == '-') {
        sign = -1;
        pos++;
    }
    while ((expr[pos] - '0' >= 0 && expr[pos] - '9' <= 0) || expr[pos] == '.') {
        if (expr[pos] == '.') {
            decimal = true;
            pos++;
        }
        else if (decimal == false) {
            number *= 10;
            number += (expr[pos++] - '0');
        }
        else {
            number += (expr[pos++] - '0') * k;
            k /= 10;
        }
    }

    LISTNODEPTR newNodePtr = malloc(sizeof(LISTNODE));
    initListNode(newNodePtr);
    if ((*sPtr) == NULL) {
        newNodePtr->n = sign * number;
        (*sPtr) = newNodePtr;
        (*ePtr) = newNodePtr;
    }
    else {
        newNodePtr->previousPtr = (*ePtr);
        newNodePtr->n = sign * number;
        (*ePtr)->nextPtr = newNodePtr;
        (*ePtr) = newNodePtr;
    }
    return pos;
}

//if negative then true else false
bool ISNegative(char* expr, int pos)
{
    if (pos == 0 && expr[pos] == '-')
        return true;
    else if (expr[pos] == '-' && ISOP(expr[pos - 1]))
        return true;
    else
        return false;
}

//deal with an OP
void readOP(LISTNODEPTR* sPtr, LISTNODEPTR* ePtr, STACKOPPTR* sOPPtr, STACKOPPTR* eOPPtr, char OP)
{
    char c;
    if (OP == ')') {
        while ((*eOPPtr)->OP != '(') {
            c = popOP(sOPPtr, eOPPtr);
            creatOP(sPtr, ePtr, c);
        }
        popOP(sOPPtr, eOPPtr);
    }
    else {
        while(ISPOPOP(sOPPtr, eOPPtr, OP)) {
            c = popOP(sOPPtr, eOPPtr);
            creatOP(sPtr, ePtr, c);
        }
        pushOP(sOPPtr, eOPPtr, OP);
    }
}

//creat a listnode of OP
void creatOP(LISTNODEPTR* sPtr, LISTNODEPTR* ePtr, char OP)
{
    LISTNODEPTR newNodePtr = malloc(sizeof(LISTNODE));
    initListNode(newNodePtr);
    newNodePtr->previousPtr = (*ePtr);
    newNodePtr->OP = OP;
    (*ePtr)->nextPtr = newNodePtr;
    (*ePtr) = newNodePtr;
}

//if it needs pop then return true else false
bool ISPOPOP(STACKOPPTR* sOPPtr, STACKOPPTR* eOPPtr, char OP)
{
    if ((*eOPPtr) == NULL)
        return false;
    else if((*eOPPtr)->OP == '(')
        return false;
    else if (scoreOP(OP) > scoreOP((*eOPPtr)->OP))
        return false;
    else
        return true;
}

int scoreOP(char OP)
{
    switch (OP) {
    case '+':
    case '-':
        return 1;
        break;
    case '*':
    case '/':
        return 2;
        break;
    case '(':
        return 3;
        break;
    default:
        break;
    }
}

//push an OP into the stack
void pushOP(STACKOPPTR* sOPPtr, STACKOPPTR* eOPPtr, char OP)
{
    STACKOPPTR newOPPtr = malloc(sizeof(STACKOP));
    newOPPtr->OP = OP;
    if (*sOPPtr == NULL) {
        (*sOPPtr) = newOPPtr;
        (*eOPPtr) = newOPPtr;
        newOPPtr->nextPtr = NULL;
        newOPPtr->previousPtr = NULL;
    }
    else {
        (*eOPPtr)->nextPtr = newOPPtr;
        newOPPtr->previousPtr = (*eOPPtr);
        newOPPtr->nextPtr = NULL;
        (*eOPPtr) = newOPPtr;
    }
}

//delete an OP on the top of the stack
char popOP(STACKOPPTR* sOPPtr, STACKOPPTR* eOPPtr)
{
    char OP;
    if ((*eOPPtr)->previousPtr == NULL) {
        OP = (*eOPPtr)->OP;
        initStackNode(*eOPPtr);
        free(*eOPPtr);
        (*sOPPtr) = NULL;
        (*eOPPtr) = NULL;
    }
    else {
        STACKOPPTR tempPtr = (*eOPPtr)->previousPtr;
        OP = (*eOPPtr)->OP;
        initStackNode(*eOPPtr);
        free(*eOPPtr);
        (*eOPPtr) = tempPtr;
        (*eOPPtr)->nextPtr = NULL;
    }
    return OP;
}

//if OP then true else false
bool ISOP(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
        return true;
    else
        return false;
}
