#include <stdio.h>
#include "bn.c"

/*
bn *bn_new();
bn *bn_init(bn const *orig);
int bn_init_string(bn *t, const char *init_string);
int bn_init_string_radix(bn *t, const char *init_string, int radix);
int bn_init_int(bn *t, int init_int);
int bn_delete(bn *t);
int bn_add_to(bn *t, bn const *right);
int bn_sub_to(bn *t, bn const *right);
int bn_mul_to(bn *t, bn const *right);
int bn_div_to(bn *t, bn const *right);
int bn_mod_to(bn *t, bn const *right);
int bn_pow_to(bn *t, int degree);
int bn_root_to(bn *t, int reciprocal);
bn* bn_add(bn const *left, bn const *right);
bn* bn_sub(bn const *left, bn const *right);
bn* bn_mul(bn const *left, bn const *right);
bn* bn_div(bn const *left, bn const *right);
bn* bn_mod(bn const *left, bn const *right);
const char *bn_to_string(bn const *t, int radix);
int bn_cmp(bn const *left, bn const *right);
int bn_neg(bn *t);
int bn_abs(bn *t);
int bn_sign(bn const *t);
*/

int main(){
    bn* a = bn_new();
    bn* b = bn_new();

    char A[100001];
    char op[100001];
    char B[100001];

    fgets(A, 100000, stdin);
    fgets(op, 100000, stdin);
    fgets(B, 100000, stdin);

    A[strlen(A)-1] = '\0';
    B[strlen(B)-1] = '\0';
    
    bn_init_string(a, A);
    bn_init_string(b, B);

    if(op[0] == '%')
        bn_mod_to(a, b);
    else if(op[0] == '/')
        bn_div_to(a, b);

    const char* s = bn_to_string(a, 10);
    printf("%s\n", s);

    free((void*)s);
    bn_delete(a);
    bn_delete(b);
    return 0;
}