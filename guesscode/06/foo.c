int foo(long long *a, long long *b){
    *a = 0;
    for(int i = 0; i != 10; i++){
        for(int j = 0; j != 10; j++){
            *a += b[j];
        }
        b += 10;
    }

    return 0;
}

/* 
    *rdi = 0;
    int rax = 0;
L1:
    int rcx = 0;
L2:
    int rdx = rsi[rcx * 8];
    *rdi += rdx;
    rcx += 1;
    if(rcx != 10)
        goto L2;
    rax += 1;
    rsi += 80;
    if(rax != 10)
        goto L1;
    rax = 0;
    return 0;
*/
