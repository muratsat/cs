int foo(char* s){
    int res = 0;
    while(*s){
        char c = *s - '0';
        if(c > 9 || c < 0)
            return 0;
        res = res*10 + c;
        s++;
    }
    return res;
}