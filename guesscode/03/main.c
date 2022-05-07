#include <stdio.h>

int foo(int *a, int n);

void bits(int x){
    unsigned y = *(unsigned*)&x;
    for(int i = 1 ; i <= 32; i++){
        printf("%d", (y >> (32 - i))&1);
        if(i % 8 == 0)
            printf(" ");
    }
    printf("\n");
}

int main(){
    int a[] = {1, 2, 3, 4};
    int n = 4;
    printf("%d\n", foo(a, n));
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}