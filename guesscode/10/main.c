#include <stdio.h>

int foo(double* a, double* b);

int main() {
    double b = 12;
    double a[] = {1., -1., 3., 4., 0.}; 

    foo(&b, a);
    for(int i = 0; i < 5; i++)
        printf("%lf ", a[i]);

    printf("\n%lf \n", b);
}