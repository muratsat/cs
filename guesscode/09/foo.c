int foo(int a, char *s){
    if(a == 0) return 0;
    *s = a%10 + '0';
    foo(a/10, s+1);
}