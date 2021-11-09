#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bn.h"

//#define MOD 4294967296 // 2^32
const long long MOD = 4294967296;

struct bn_s{
    // array of digits in base 2^32
    unsigned int *digit;

    //number of digits in base 2^32
    int size;

    // sign=-1 if bn < 0; sign=1 if bn > 0; sign=0 if bn=0 
    int sign;
};
typedef struct bn_s bn;

bn *bn_new(){
    bn* bignum = (bn*)malloc(sizeof(bn));
    bignum->size = 1;
    bignum->sign = 0;
    bignum->digit = NULL;
    bignum->digit = (unsigned int*)malloc(sizeof(unsigned int));
    bignum->digit[0] = 0;
    return bignum;
}

bn *bn_init(bn const *orig){
    bn* copy = bn_new();
    copy->sign = orig->sign;
    copy->size = orig->size;

    for(int i = 0; i < orig->size; i++)
        copy->digit[i] = orig->digit[i];

    return copy;
}

int bn_delete(bn *t){
    if(t == NULL)
        return 0;
    if(t->digit != NULL) 
        free(t->digit);
    free(t);
    return 0;
}

int bn_init_int(bn *t, int init_int){
    t->digit = (unsigned int*)realloc(t->digit, sizeof(unsigned int));
    t->size = 1;
    t->digit[0] = init_int;
    t->sign = 1;

    if(init_int == 0)
        t->sign = 0;

    if(init_int < 0){
        t->sign = -1;
        t->digit[0] = -init_int;
    }
    return 0;
}

int bn_cmp(bn const *left, bn const *right){
    int sign1 = left->sign, sign2 = right->sign;
    int size1 = left->size, size2 = right->size;

    long long sign = size1 * sign1 - size2 * sign2;

    if(sign == 0){
        long long i = size1, diff;

        while(--i >= 0){
            diff = (long long)left->digit[i] - (long long)right->digit[i];
            if(diff != 0)
                break;
        }

        sign = sign1 * diff;
    }

    if(sign < 0)
        return -1;
    if(sign > 0)
        return 1;
    return 0;
}