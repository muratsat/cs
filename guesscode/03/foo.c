int foo(int *a, int n){
    if(n < 2)
        return n;

    int i = 1;
    do {
        int t = a[i];
        a[i] = a[i-1];
        a[i-1] = t;
        i++;
    } while(i != n);

    return n;
}
/*

    eax = esi
    if esi is below 2
        return esi
    
    r8d = eax 
    edx = rdi[0]
    esi = 1

    do {
        ecx = rdi[rsi * 4]
        rdi[rsi * 4] = edx
        rdi[rsi * 4 - 4] = ecx
        rsi += 1
    } while rsi != r8(esi)

    return eax
*/
