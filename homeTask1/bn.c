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

    copy->digit = (unsigned int*)realloc(copy->digit, copy->size*sizeof(unsigned int));
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

int bn_neg(bn *t){
    t->sign = -t->sign;
    return 0;
}

int bn_abs(bn *t){
    if(t->sign < 0)
        t->sign = -t->sign;
    return 0;
}

int bn_sign(bn const *t){
    return t->sign;
}

// Add absolute values of two big numbers
bn* bn_add_abs(bn const *left, bn const *right){
    int size1 = left->size, size2 = right->size;
    int size = size1 > size2? size1 : size2;

    bn* res = bn_new();
    res->digit = (unsigned int*)realloc(res->digit, size*sizeof(unsigned int));
    
    long long carry = 0, tmp;
    for(int i = 0; i < size; i++){
        tmp = carry;
        tmp += i < size1? left->digit[i] : 0;
        tmp += i < size2? right->digit[i] : 0;
        res->digit[i] = tmp%MOD;
        carry = tmp/MOD;
    }

    if(carry){
        size++;
        res->digit = (unsigned int*)realloc(res->digit, size*sizeof(unsigned int));
        res->digit[size-1] = carry;
    }

    res->size = size;
    //check if the result is zero
    res->sign = size == 1 && res->digit[0] == 0? 0 : 1;

    return res;
}

// Find difference of bignumbers' absolute values
// bn_sub_abs = abs(|left| - |right|)
bn* bn_sub_abs(const bn *left, bn const *right){
    int size1 = left->size, size2 = right->size;
    int cmp = size1 < size2? -1 : 1;

    if(size1 == size2){
        int i = size1-1;
        while(i >= 0 && left->digit[i] == right->digit[i])
            i--;

        if(i < 0)
            cmp = 0;
        else
            cmp = left->digit[i] < right->digit[i]? -1 : 1;
    }

    if(cmp == 0)
        return bn_new();


    bn *res = NULL; 
    const bn *sub = NULL;

    if(cmp > 0){
        res = bn_init(left);
        sub = right;
    }
    if(cmp < 0){ // if left < right, swap sizes
        res = bn_init(right);
        sub = left;
        int temp_size = size1;
        size1 = size2;
        size2 = temp_size;
    }

    long long tmp, i, borrowed = 0;
    for(i = 0; i < size2; i++){
        tmp = res->digit[i] - borrowed;
        borrowed = 0;

        if(tmp < sub->digit[i]){
            borrowed = 1;
            tmp += MOD;
        }

        tmp -= sub->digit[i];
        res->digit[i] = tmp;
    }
    if(borrowed)
        res->digit[i]--;
    
    // Remove traililng zeros
    int newsize = size1;
    while(res->digit[newsize-1] == 0)
        newsize--;

    if(newsize != size1){
        res->digit = (unsigned int*)realloc(res->digit, newsize*sizeof(unsigned int));
        res->size = newsize;
    }

    res->sign = 1;
    return res;
}
