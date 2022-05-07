#include <stdio.h>

void* foo(void* rdi, double a, double b, double c);

int main(){
    long long i = 0x4008000000000000; 
    i = 0x401c000000000000;
    double d = *(double*)(&i);
    printf("%lf \n", d);

    double a = 1, b = 2, c = 3;
    void* rdi;
    printf("%lf\n", *(double*)foo(rdi, a, b, c));
}