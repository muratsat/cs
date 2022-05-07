void foo(double* rdi, double* rsi){
    double x1 = *rsi;
    double x0 = 0;
    if(x1 <= x0)
        goto L3;
    rsi++;
L2:
    x1 += *rdi;
    *rdi = x1;
    x1 = *rsi;
    rsi++;
    if(x1 > x0)
        goto L2;
L3:
    return;

}
