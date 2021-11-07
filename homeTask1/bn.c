#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bn.h"

#define MAXSIZE 100000
#define MOD 4294967296

struct bn_s{
    unsigned int digit[MAXSIZE];
    int size;
    int sign;
};
typedef struct bn_s bn;

bn *bn_new(){
    bn* bignum = (bn*)malloc(sizeof(bn));
    bignum->size = 0;
    bignum->sign = 0;
    bignum->digit[0] = 0;
    return bignum;
}

bn *bn_init(bn const *orig){
    bn* copy = (bn*)malloc(sizeof(bn));
    *copy = *orig;
    return copy;
}

int bn_delete(bn *t){
    free(t);
    return 0;
}