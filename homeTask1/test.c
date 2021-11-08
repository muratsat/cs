#include <stdio.h>
#include "bn.c"

unsigned int to_int(const char* s){
    int d = 1;
    unsigned int res = 0;
    for(int i = 31; i >= 0; i--){
        res += (s[i]-'0')*d;
        d *= 2;
    }
    return res;
}

bn *bn_init_bin(const char* bin){
    bn *a = bn_new();
    int n = strlen(bin); 
    int size = n/32 + (n%32 != 0);
    a->sign = 1;

    a->digit = (unsigned int*)realloc(a->digit, size*sizeof(unsigned int));
    a->size = size;

    int i = n-1, k = 0, end = 0;
    if(bin[0] == '-'){
        a->sign = -1;
        end = 1;
    }

    while(i >= end){
        char digit[] = "00000000000000000000000000000000";

        for(int j = 0; j < 32 && j <= i; j++)
            digit[31 - j] = bin[i-j];
        
        a->digit[k] = to_int(digit);

        k++;
        i -= 32;
    }
    if(a->size == 1 && a->digit[0] == 0)
        a->sign = 0;
    a->size = k;
    return a;
}

int main(int argc, char *argv[]) {

    bn *a = bn_init_bin(argv[1]);

    bn *b = bn_init_bin(argv[2]);

    long long compare = bn_cmp(a, b);
    printf("%lld \n", compare);

    bn_delete(b);
    bn_delete(a);
    return 0;
}