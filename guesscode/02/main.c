#include <stdio.h>
// int foo( long long rdi,  long long rsi,  long long rdx,  long long rcx);
int foo(int *rdi,  int esi);

int main(){
    long long rsi, rdx, rcx;
    //                 0  1  2
    int rdi[] = {1, 2, 3}; 
    int esi;
    // scanf("%lld%d%lld", &rdi, &esi, &rdx);
    // scanf("%lld%lld%lld%lld", &rdi, &rsi, &rdx, &rcx);


    printf("%d\n", foo(rdi, 3));
}