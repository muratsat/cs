#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bn.h"

#define MOD 4294967296 // 2^32

struct bn_s{
    unsigned int *digit;
    int size;
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