int foo(char *a, char* b){
    b[0] = a[0];
    if(b[0] == 0)
        return 0;
    
    int i = 0;
    do {
        b[i + 1] = a[i + 1];
        i++;
    } while(b[i] != 0);

    return i;
}
