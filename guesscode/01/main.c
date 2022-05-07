#include <stdio.h>

int foo(int* a, int i);

int main(){
    int a[] = {0xffffffff, 2, 3};
    while(1){
        int t;
        scanf("%d", &t);
        a[0] = t;
        printf("%d", foo(a, 1));
    }
}