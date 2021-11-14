#include <stdio.h>
#include "bn.c"

void print(bn* a){
    for(int i = 0; i < a->size; i++)
        printf("%u ", a->digit[i]);
    printf("\n");
}

int bn_init_string_to10e9(bn *res, const char *init_string){
    int n = strlen(init_string);
    if(n > 1 && init_string[n-1] == '\n'){
        init_string[n-1] == '\0';
        n--;
    }
    int size = n/9 + (n%9 != 0);
    bn_resize(res, size);
    res->sign = 1;

    int end = 0, k = 0;
    if(init_string[0] == '-'){
        end = 1;
        res->sign = -1;
    }

    for(int i = n-1; i >= end; i -= 9){
        int digit = 0, ten = 1;
        for(int j = 0; j < 9 && i-j >= end; j++){
            digit += ten*(init_string[i-j] - '0');
            ten *= 10;
        }

        res->digit[k] = digit;
        k++;
    }

    bn_normalize(res);
    return 0;
}

int main(){
    printf("\n\n\n\n-------------------------------------- \n");
    bn* a = bn_new();
    bn_init_string_radix(a, "AAAA", 16);
    const char *r1 = bn_to_string(a,16); // r1 -> "111"
    printf("a=%s\n", r1);
    free(r1);
    bn_print(a);
    printf("-------------------------------------- \n\n\n\n\n");
    bn_delete(a);

    return 0;
}