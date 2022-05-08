void foo(double *x, double a[]){
    double prev = a[0];
    while(prev > 0){
        a++;
        prev += *x;
        *x = prev;
        prev = *a;
    }
}
