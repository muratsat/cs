#include <stdio.h>

int foo(char *a, char *b);
// int foo();

int main(){
    char a[] = {1, 3, 0, 0};
    char b[] = {4, 0, 1, 1};

    printf("%d \n", foo(a, b));
    int n = 4;

    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    for(int i = 0; i < n; i++)
        printf("%d ", b[i]);
    printf("\n");

}