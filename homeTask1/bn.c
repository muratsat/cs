#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bn.h"

//#define MOD 4294967296 // 2^32
const long long MOD = 1000000000;

struct bn_s{
    // array of digits in base MOD
    unsigned int *digit;

    // Number of elements allocated
    // in the digits array
    int allocd;

    //number of digits in base MOD
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
    bignum->allocd = 2048;
    bignum->digit = (unsigned int*)calloc(bignum->allocd, sizeof(unsigned int));
    bignum->digit[0] = 0;
    return bignum;
}

// Change the number of digits
int bn_resize(bn* t, int new_size){
    t->size = new_size;

    // If needed, reallocate
    // more memory for digits
    if(new_size > t->allocd){
        t->digit = (unsigned int*)realloc(t->digit, 2 * t->allocd * sizeof(unsigned int));
        t->allocd *= 2;
    }
    return 0;
}

// Copy from number SRC to number DEST
int bn_copy(const bn* src, bn* dest){
    dest->sign = src->sign;
    int size = src->size;
    bn_resize(dest, size);

    memcpy(dest->digit, src->digit, size*sizeof(unsigned int));

    return 0;
}

bn *bn_init(bn const *orig){
    bn* copy = bn_new();
    bn_copy(orig, copy);

    return copy;
}

int bn_delete(bn *t){
    if(t == NULL)
        return 0;
    if(t->digit != NULL) 
        free(t->digit);
    free(t);
    t = NULL;
    return 0;
}

int bn_init_int(bn *t, int init_int){
    bn_resize(t, 1);
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

// Compare absolute values of two numbers
// Returns:
// -1 if |left| < |right|
//  0 if |left| = |right|
//  1 if |left| > |right|
int bn_cmp_abs(const bn *left, bn const *right){
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
    return cmp;
}

// Remove trailing zeros
int bn_normalize(bn* a){
    int newsize = a->size-1;
    while(newsize > 0){
        if(a->digit[newsize] != 0)
            break;
        newsize--;
    }
    bn_resize(a, newsize + 1);
    if(a->size == 1 && a->digit[0] == 0)
        a->sign = 0;

    return 0;
}

bn* bn_add(bn const *left, bn const *right){
    bn* res = bn_new();
    bn_copy(left, res);
    bn_add_to(res, right);

    return res;
}

bn* bn_sub(bn const *left, bn const *right){
    bn* res = NULL;
    bn_copy(left, res);
    bn_sub_to(res, right);

    return res;
}

int bn_add_to(bn *t, bn const *right){
    bn *a = t; 
    const bn *b = right;

    if(t->sign == right->sign){ // then add their absolute values
        int size1 = a->size, size2 = b->size;
        int size = size1 > size2 ? size1 : size2;

        if(a->size < size)
            bn_resize(a, size);

        long long carry = 0, tmp;
        for(int i = 0; i < size; i++){
            tmp = carry;
            tmp += i < size1? a->digit[i] : 0;
            tmp += i < size2? b->digit[i] : 0;
            a->digit[i] = tmp%MOD;
            carry = tmp/MOD;
        }

        if(carry){
            size++;
            bn_resize(a, size);
            a->digit[size - 1] = carry;
        }

        if(size == 1 && a->digit[0] == 0)
            a->sign = 0;
        a->size = size;
        return 0;
    }

    // else subtract
    int cmp = bn_cmp_abs(a, b);
    if(cmp == 0){
        bn_resize(a, 1);
        a->digit[0] = 0;
        a->sign = 0;
        return 0;
    }
    int size1 = a->size, size2 = b->size;
    int size = size1 > size2? size1 : size2;

    if(size1 < size2)
        bn_resize(a, size);

    long long tmp, borrowed = 0, i;
    for(i = 0; i < size; i++){
        tmp = -borrowed;
        if(i < size1)
            tmp += cmp * (long long)a->digit[i];
        if(i < size2)
            tmp -= cmp * (long long)b->digit[i];
        borrowed = 0;

        if(tmp < 0){
            borrowed = 1;
            tmp += MOD;
        }

        a->digit[i] = tmp;
    }

    a->size = size;

    bn_normalize(a);

    a->sign = cmp;
    return 0;
}

int bn_sub_to(bn *t, bn const *right){
    bn *a = t; 
    const bn *b = right;

    if(t->sign != right->sign){ // then add their absolute values
        int size1 = a->size, size2 = b->size;
        int size = size1 > size2 ? size1 : size2;

        if(a->size < size)
            bn_resize(a, size);

        long long carry = 0, tmp;
        for(int i = 0; i < size; i++){
            tmp = carry;
            tmp += i < size1? a->digit[i] : 0;
            tmp += i < size2? b->digit[i] : 0;
            a->digit[i] = tmp%MOD;
            carry = tmp/MOD;
        }

        if(carry){
            size++;
            bn_resize(a, size);
            a->digit[size - 1] = carry;
        }

        if(size == 1 && a->digit[0] == 0)
            a->sign = 0;
        a->size = size;
        return 0;
    }

    // else subtract
    int cmp = bn_cmp_abs(a, b);
    if(cmp == 0){
        bn_resize(a, 1);
        a->digit[0] = 0;
        a->sign = 0;
        return 0;
    }
    int size1 = a->size, size2 = b->size;
    int size = size1 > size2? size1 : size2;

    if(size1 < size2)
        bn_resize(a, size);

    long long tmp, borrowed = 0, i;
    for(i = 0; i < size; i++){
        tmp = -borrowed;
        if(i < size1)
            tmp += cmp * (long long)a->digit[i];
        if(i < size2)
            tmp -= cmp * (long long)b->digit[i];
        borrowed = 0;

        if(tmp < 0){
            borrowed = 1;
            tmp += MOD;
        }

        a->digit[i] = tmp;
    }

    a->size = size;

    bn_normalize(a);

    a->sign = cmp;
    return 0;
}

void bn_print(const bn* f){
    //printf("\nsign: %d\nsize: %d\n", f->sign, f->size);
    if(f->sign < 0) printf("-");
    printf("%u", f->digit[f->size - 1]);
    for(int i = f->size - 2; i >= 0; i--)
        printf("%09u", f->digit[i]);
    printf("\n\n");
}

bn* bn_mul(const bn *a, const bn *b){
    int size_a = a->size, size_b = b->size;

    bn *res = bn_new(); 
    bn_resize(res, size_a + size_b);

    bn* t = bn_new();
    bn_resize(t, size_a + size_b);

    for(int j = 0; j < size_b; j++){
        memcpy(t->digit + j, a->digit, size_a * sizeof(unsigned int));
        if(j > 0)
            t->digit[j-1] = 0;

        long long tmp, carry = 0;

        for(int i = 0; i < size_a; i++){
            tmp = (long long)b->digit[j] * (long long)a->digit[i];
            tmp += carry;
            t->digit[j + i] = tmp % MOD;
            carry = tmp / MOD;
        }

        if(carry)
            t->digit[j + size_a] = carry;

        bn_add_to(res, t);
    }

    res->sign = a->sign * b->sign;

    bn_normalize(res);
    bn_delete(t);
    return res;
}

int bn_mul_to(bn *a, bn const *b){
    int size_a = a->size, size_b = b->size;

    bn* at = bn_init(a);
    bn* t = bn_new();
    t->sign = 1;
    bn_copy(t, a);

    for(int j = 0; j < size_b; j++){
        bn_resize(t, size_a + j);
        memcpy(t->digit + j, at->digit, size_a * sizeof(unsigned int));
        if(j > 0)
            t->digit[j-1] = 0;

        long long tmp, carry = 0;
        for(int i = 0; i < size_a; i++){
            tmp = (long long)b->digit[j] * (long long)at->digit[i];
            tmp += carry;
            t->digit[j + i] = tmp % MOD;
            carry = tmp / MOD;
        }

        if(carry){
            bn_resize(t, j + size_a + 1);
            t->digit[j + size_a] = carry;
        }

        bn_add_to(a, t);
    }

    bn_normalize(a);
    a->sign = at->sign * b->sign;

    bn_delete(at);
    bn_delete(t);
    return 0;
}
