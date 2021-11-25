#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bn.h"

#define BASE 4294967296// 2^32
//const long long BASE = 4294967296;


/* Headers for helper functions */
/*----------------------------------------------------------------------------------------------------*/

// Change the number of digits
int bn_resize(bn* t, int new_size);

// Copy from number SRC to number DEST
int bn_copy(const bn* src, bn* dest);

// change all digits to zero
int bn_zero(bn *t);

// Compare absolute values of two numbers
// Returns:
// -1 if |left| < |right|
//  0 if |left| = |right|
//  1 if |left| > |right|
int bn_cmp_abs(bn const *left, bn const *right);

// Remove trailing zeros
int bn_normalize(bn* a);

// Multiply bignum A by integer B
int bn_mul_int(bn* a, int b);

// Divide bignum A by integer D
// and return the remainder
int bn_div_int(bn* a, int D);

/*----------------------------------------------------------------------------------------------------*/

struct bn_s{
    // array of digits in base BASE 
    unsigned int *digit;

    // Number of elements allocated
    // in the digits array
    int allocd;

    //number of digits in base BASE 
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

bn *bn_init(bn const *orig){
    bn* copy = bn_new();
    bn_copy(orig, copy);

    return copy;
}

int bn_init_string(bn *t, const char *init_string){
    return bn_init_string_radix(t, init_string, 10);
}

int bn_init_string_radix(bn *t, const char *init_string, int radix){
    unsigned char DigitValue[256] = {
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9,   0,  0,  0,  0,  0,  0,
         0, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,  0,  0,  0,  0,  0,
         0, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };

    int len = strlen(init_string), end = 0, sign = 1;

    bn_zero(t);
    bn* T = bn_new();
    bn_init_int(T, 1);

    if(init_string[0] == '-'){
        sign = -1;
        end = 1;
    }

    for(int i = len-1; i >= end; i--){
        bn* tmp = bn_init(T);
        bn_mul_int(tmp, DigitValue[(int)init_string[i]]);
        bn_add_to(t, tmp);
        bn_mul_int(T, radix);
        bn_delete(tmp);
    }
    t->sign = sign;

    bn_delete(T);
    return 0;
}

const char *bn_to_string(bn const *t, int radix){
    int size = t->sign <= 0;
    bn *a = bn_init(t);

    while(a->sign != 0){
        bn_div_int(a, radix);
        size++;
    }

    char charValue[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 
        'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    char* res = (char*)malloc((size+1) * sizeof(char));
    res[size] = '\0';
    if(t->sign < 0)
        res[0] = '-';
    bn_copy(t, a);

    int r, k = 0;
    do {
        r = bn_div_int(a, radix);
        res[size - 1 - k] = charValue[r];
        k++;
    } while(a->sign != 0);

    bn_delete(a);
    return res;
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

int bn_delete(bn *t){
    if(t == NULL)
        return 0;
    if(t->digit != NULL) 
        free(t->digit);
    free(t);
    t = NULL;
    return 0;
}

int bn_cmp(bn const *left, bn const *right){
    int sign1 = left->sign, sign2 = right->sign;
    int size1 = left->size, size2 = right->size;

    unsigned long long sign = size1 * sign1 - size2 * sign2;

    if(sign == 0){
        unsigned long long i = size1, diff;

        while(--i >= 0){
            diff = (unsigned long long)left->digit[i] - (unsigned long long)right->digit[i];
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



//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//*************************************************************************************************************************************************

int bn_resize(bn* t, int new_size){
    t->size = new_size;

    // If needed, reallocate
    // more memory for digits
    int allocd = t->allocd;
    if(new_size > allocd){
        allocd *= 2;
        allocd = new_size > allocd? new_size : allocd;
        t->digit = (unsigned int*)realloc(t->digit, 2 * allocd * sizeof(unsigned int));
        t->allocd = allocd;
    }
    return 0;
}

int bn_copy(const bn* src, bn* dest){
    dest->sign = src->sign;
    int size = src->size;
    bn_resize(dest, size);

    memcpy(dest->digit, src->digit, size*sizeof(unsigned int));

    return 0;
}

int bn_zero(bn *t){
    t->sign = 0;
    t->size = 1;
    int allocd = t->allocd;
    unsigned int* tmp = (unsigned int*)calloc(allocd, sizeof(unsigned int));
    memcpy(t->digit, tmp, allocd*sizeof(unsigned int));
    free(tmp);
    return 0;
}

int bn_cmp_abs(bn const *left, bn const *right){
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

int bn_mul_int(bn* a, int b){
    int size_a = a->size, i;
    unsigned long long tmp, carry = 0;

    if(b == 0){
        bn_zero(a);
        return 0;
    }

    if(b < 0){
        a->sign *= -1;
        b = -b;
    }

    for(i = 0; i < size_a; i++){
        tmp = (unsigned long long)a->digit[i] * (unsigned long long)b + carry;
        a->digit[i] = tmp;
        carry = tmp / BASE;
    }

    if(carry){
        bn_resize(a, size_a + 1);
        a->digit[size_a] = carry;
    }

    bn_normalize(a);
    return 0;
}

int bn_div_int(bn* a, int b){
    unsigned long long tmp;
    int remainder = 0;

    for(int i = a->size-1; i >= 0; i--){
        tmp = BASE * remainder + a->digit[i];
        a->digit[i] = tmp / b;
        remainder = tmp % b;
    }

    bn_normalize(a);
    return remainder;
}

//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//*************************************************************************************************************************************************



int bn_add_to(bn *t, bn const *right){
    bn *a = t; 
    const bn *b = right;

    if(a->sign == 0){
        bn_copy(b, a);
        return 0;
    }
    if(b->sign == 0)
        return 0;

    if(t->sign == right->sign){ // then add their absolute values
        int size1 = a->size, size2 = b->size;
        int size = size1 > size2 ? size1 : size2;

        if(a->size < size)
            bn_resize(a, size);

        unsigned long long carry = 0, tmp;
        for(int i = 0; i < size; i++){
            tmp = carry;
            tmp += i < size1? a->digit[i] : 0;
            tmp += i < size2? b->digit[i] : 0;
            a->digit[i] = tmp;
            carry = tmp/BASE;
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

    unsigned long long tmp, borrowed = 0, i;
    for(i = 0; i < size; i++){
        tmp = -borrowed;
        if(i < size1)
            tmp += cmp * (unsigned long long)a->digit[i];
        if(i < size2)
            tmp -= cmp * (unsigned long long)b->digit[i];
        borrowed = 0;

        if(tmp < 0){
            borrowed = 1;
            tmp += BASE;
        }

        a->digit[i] = tmp;
    }

    a->size = size;

    bn_normalize(a);

    a->sign = cmp*a->sign;
    return 0;
}

int bn_sub_to(bn *t, bn const *right){
    bn *a = t; 
    const bn *b = right;

    if(a->sign == 0){
        bn_copy(b, a);
        return 0;
    }
    if(b->sign == 0)
        return 0;

    if(t->sign != right->sign){ // then add their absolute values
        int size1 = a->size, size2 = b->size;
        int size = size1 > size2 ? size1 : size2;

        if(a->size < size)
            bn_resize(a, size);

        unsigned long long carry = 0, tmp;
        for(int i = 0; i < size; i++){
            tmp = carry;
            tmp += i < size1? a->digit[i] : 0;
            tmp += i < size2? b->digit[i] : 0;
            a->digit[i] = tmp%BASE;
            carry = tmp/BASE;
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

    unsigned long long tmp, borrowed = 0, i;
    for(i = 0; i < size; i++){
        tmp = -borrowed;
        if(i < size1)
            tmp += cmp * (unsigned long long)a->digit[i];
        if(i < size2)
            tmp -= cmp * (unsigned long long)b->digit[i];
        borrowed = 0;

        if(tmp < 0){
            borrowed = 1;
            tmp += BASE;
        }

        a->digit[i] = tmp;
    }

    a->size = size;

    bn_normalize(a);

    a->sign = cmp*a->sign;
    return 0;
}

int bn_mul_to(bn *a, bn const *b){
    bn* t = bn_mul(a, b);
    bn_copy(t, a);
    bn_delete(t);
    return 0;
}

int bn_div_to(bn *t, bn const *right){
    bn* a = t;
    bn const* b = right;
    int size_a = a->size, size_b = b->size;
    int sign_a = a->sign, sign_b = b->sign;

    if(sign_b == 0)
        return 3;

    int cmp = bn_cmp_abs(a, b);

    if(cmp < 0){
        bn_zero(t);
        t->sign = sign_a * sign_b;
        if(sign_a != sign_b){
            bn_init_int(t, -1);
        }

        return 0;
    }

    //TODO: COMPLETE THE METHOD IF abs(A) > abs(B) 

    return 0;
}

int bn_mod_to(bn *t, bn const *right){
    return 0;
}

bn* bn_add(bn const *left, bn const *right){
    bn* res = bn_new();
    bn_copy(left, res);
    bn_add_to(res, right);

    return res;
}

bn* bn_sub(bn const *left, bn const *right){
    bn* res = bn_new();
    bn_copy(left, res);
    bn_sub_to(res, right);

    return res;
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

        unsigned long long tmp, carry = 0;

        for(int i = 0; i < size_a; i++){
            tmp = (unsigned long long)b->digit[j] * (unsigned long long)a->digit[i];
            tmp += carry;
            t->digit[j + i] = tmp;
            carry = tmp / BASE;
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

bn* bn_div(bn const *left, bn const *right){
    return bn_new();
}

bn* bn_mod(bn const *left, bn const *right){
    return bn_new();
}

int bn_pow_to(bn *a, int n){
    bn* t = bn_init(a);
    bn_init_int(a, 1);

    while(n > 0){
        if(n%2 == 1)
            bn_mul_to(a, t);

        bn_mul_to(t, t);
        n /= 2;
    }

    bn_delete(t);
    return 0;
}

int bn_root_to(bn *t, int reciprocal){
    return 0;
}
