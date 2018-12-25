/*
Description
You will be given a number of test cases. 
Each case is given with a line containing a list of words separated by a space, and each word contains only uppercase and lowercase letters.

Input
The first line contains the number of cases as a positive integer. 
Each case is given with a line containing a list of words separated by a space, and each word contains only uppercase and lowercase letters.

Output
For each test case, output the result.

Sample Input
3
I am good
You are OK
nice char

Sample Output
I ma doog
uoY era KO
ecin rahc
*/

#include <stdio.h>
#include <string.h>
 
int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 1; i <= n; i++) {
        char input[200] = {0};
        char *p;
        int length;
 
        int k = 0;
        int c = getchar();
        while (c != '\n' && c != EOF) {
            input[k++] = c;
            c = getchar();
        }
 
        p = strtok(input, " ");
        length = strlen(p);
        for (int i = length - 1; i >= 0; i--) {
            printf("%c", p[i]);
        }
        p = strtok(NULL, " ");
        while (p) {
            printf(" ");
            length = strlen(p);
            for (int i = length - 1; i >= 0; i--) {
                printf("%c", p[i]);
            }
            p = strtok(NULL, " ");
        }
 
        printf("\n");
 
    }
 
    return 0;
}