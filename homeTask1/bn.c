#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bn.h"

#define BASE 4294967296 // 2^32

struct bn_s{
    // Array of digits in base 2^32
    unsigned int *digit;

    // Number of digits allocated 
    // in digits array
    int allocd;

    // Number of actual digits 
    // in base 2^32
    int size;

    // Sign of the number:
    // 1 if positive
    // 0 if zero
    // -1 if negative
    int sign;
};
typedef struct bn_s bn;

/* Headers for helper functions */

// Assign new size to bignum A
int bn_resize(bn* a, int new_size);

// Copy a bignum from SRC to DEST
int bn_copy(bn const *src, bn *dest);

// Remove trailing zeros
int bn_normalize(bn* a);

// Multiply bignum A by int B
int bn_mul_int(bn* a, int b);

// Dibide bignum A by int B
// and return the remainder
int bn_div_int(bn* a, int b);

// Compare absolute values of A and B
int bn_cmp_abs(bn const *a, bn const *b);

// add absolute values 
// |a| = |a| + |b|
int bn_add_abs(bn* a, bn const *b);

// subtract absolute values
// |a| = |a| - |b|
int bn_sub_abs(bn* a, bn const *b);

// Set number to zero
void bn_zero(bn* a);

void bn_debug(bn* a){
    printf("\nsize: %d, sign: %d\n", a->size, a->sign);
    for(int i = a->size - 1; i >= 0; i--)
        printf("%u ", a->digit[i]);
    
    printf("\n");
}

/*******************************************************************************************************************************************/

int bn_resize(bn* a, int new_size){
    if(a->allocd < new_size){
        a->digit = (unsigned int*)realloc(a->digit, new_size * sizeof(unsigned int));
        a->allocd = new_size;
    }

    a->size = new_size; 
    return 0;
}

int bn_copy(bn const *src, bn *dest){
    dest->sign = src->sign;
    bn_resize(dest, src->size);
    memcpy(dest->digit, src->digit, src->size * sizeof(unsigned int));
    return 0;
}

int bn_normalize(bn* a){
    int new_size = a->size - 1;

    while(new_size > 0){
        if(a->digit[new_size] != 0)
            break;
        new_size--;
    }

    bn_resize(a, new_size + 1);
    if(a->size == 1 && a->digit[0] == 0)
        a->sign = 0;

    return 0;
}

int bn_mul_int(bn* a, int b){
    if(b < 0){
        a->sign *= -1;
        b = -b;
    }

    int size_a = a->size;
    unsigned long long tmp, carry = 0;

    for(int i = 0; i < size_a; i++){
        tmp = carry + (unsigned long long)a->digit[i] * b;
        a->digit[i] = tmp;
        carry = tmp / BASE;
    }

    if(carry != 0){
        bn_resize(a, size_a + 1);
        a->digit[size_a] = carry;
    }

    bn_normalize(a);
    return 0;
}

int bn_div_int(bn* a, int b){
    if(b == 0)
        return 3;
    
    int size_a = a->size, remainder = 0;
    unsigned long long tmp;

    for(int i = size_a-1; i >= 0; i--){
        tmp = BASE * remainder + a->digit[i];
        a->digit[i] = tmp / b;
        remainder = tmp % b;
    }

    bn_normalize(a);
    return remainder;
}

int bn_cmp_abs(bn const *a, bn const *b){
    int size_a = a->size, size_b = b->size;

    if(size_a > size_b)
        return 1;
    if(size_a < size_b)
        return -1;
    
    long long diff = 0;
    for(int i = size_a - 1; i >= 0; i--){
        diff = (long long)a->digit[i] - (long long)b->digit[i];
        if(diff != 0)
            break;
    }

    if(diff > 0)
        return 1;
    if(diff < 0)
        return -1;
    return 0;
}

int bn_add_abs(bn* a, bn const *b){
    int size_a = a->size, size_b = b->size;

    int size = size_a > size_b? size_a : size_b;
    bn_resize(a, size);

    unsigned long long tmp, carry = 0;
    for(int i = 0; i < size; i++){
        tmp = carry;
        if(i < size_a)
            tmp += a->digit[i];
        if(i < size_b)
            tmp += b->digit[i];
        
        a->digit[i] = tmp;
        carry = tmp / BASE;
    }

    if(carry){
        bn_resize(a, size+1);
        a->digit[size] = carry;
    }

    bn_normalize(a);
    return 0;
}

int bn_sub_abs(bn* a, bn const *b){
    int size_a = a->size, size_b = b->size;

    int cmp = bn_cmp_abs(a, b);
    int size = size_a > size_b? size_a : size_b;
    bn_resize(a, size);

    long long tmp, borrowed = 0;
    for(int i = 0; i < size; i++){
        tmp = -borrowed;
        if(i < size_a)
            tmp += cmp * (long long)a->digit[i];
        if(i < size_b)
            tmp -= cmp * (long long)b->digit[i];
        
        borrowed = 0;
        if(tmp < 0){
            borrowed = 1;
            tmp += BASE;
        }
        
        a->digit[i] = tmp;
    }

    bn_normalize(a);
    return 0;
}

void bn_zero(bn* a){
    memset(a->digit, 0, a->allocd * sizeof(unsigned int));
    bn_resize(a, 1);
    a->sign = 0;
}

/*******************************************************************************************************************************************/


bn *bn_new(){
    bn* a = (bn*)malloc(sizeof(bn));

    int default_size = 2048;

    a->digit = (unsigned int*)calloc(default_size, sizeof(unsigned int));
    a->allocd = default_size;

    // a = 0 by default
    a->sign = 0;
    a->size = 1;

    return a;
}

bn *bn_init(bn const *orig){
    bn* copy = bn_new();
    bn_copy(orig, copy);
    return copy;
}

int bn_init_string(bn *t, const char *init_string){
    bn_zero(t);
    bn* T = bn_new();
    bn_init_int(T, 1);

    int len = strlen(init_string), end = 0, sign = 1;
    if(init_string[0] == '-'){
        sign = -1;
        end = 1;
    }

    for(int i = len-1; i >= end; i--){
        bn* addend = bn_init(T);
        int digit = init_string[i] - '0';
        bn_mul_int(addend, digit);
        bn_add_abs(t, addend);
        bn_mul_int(T, 10);
        bn_delete(addend);
    }

    t->sign = sign;
    bn_delete(T);
    bn_normalize(t);
    return 0;
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

    bn_zero(t);
    bn* T = bn_new();
    bn_init_int(T, 1);

    int len = strlen(init_string), end = 0, sign = 1;
    if(init_string[0] == '-'){
        sign = -1;
        end = 1;
    }

    for(int i = len-1; i >= end; i--){
        bn* addend = bn_init(T);
        int digit = DigitValue[(int)init_string[i]];
        bn_mul_int(addend, digit);
        bn_add_abs(t, addend);
        bn_mul_int(T, radix);
        bn_delete(addend);
    }

    t->sign = sign;
    bn_delete(T);
    bn_normalize(t);
    return 0;
}


int bn_init_int(bn *t, int init_int){
    t->sign = init_int > 0;
    if(init_int < 0){
        t->sign = -1;
        init_int *= -1;
    }

    bn_resize(t, 1);
    t->digit[0] = init_int;
    return 0;
}

int bn_delete(bn *t){
    free(t->digit);
    t->digit = NULL;
    free(t);
    t = NULL;
    return 0;
}

int bn_add_to(bn *a, bn const *b){
    if(a->sign == b->sign)
        bn_add_abs(a, b);

    else{
        int cmp = bn_cmp_abs(a, b);
        bn_sub_abs(a, b);
        a->sign = cmp < 0? b->sign : a->sign;
    }

    return 0;
}

int bn_sub_to(bn *a, bn const *b){
    if(a->sign != b->sign){
        bn_add_abs(a, b);
        if(a->sign == 0)
            a->sign = -b->sign;
    }

    else{
        int cmp = bn_cmp_abs(a, b);
        bn_sub_abs(a, b);
        a->sign = a->sign * cmp;
    }

    return 0;
}

int bn_mul_to(bn *t, bn const *right){
    return 0;
}

int bn_div_to(bn *t, bn const *right){
    return 0;
}

int bn_mod_to(bn *t, bn const *right){
    return 0;
}


int bn_pow_to(bn *t, int degree){
    return 0;
}


int bn_root_to(bn *t, int reciprocal){
    return 0;
}


bn* bn_add(bn const *left, bn const *right){
    bn* res = bn_init(left);
    bn_add_to(res, right);
    return res;
}

bn* bn_sub(bn const *left, bn const *right){
    bn* res = bn_init(left);
    bn_sub_to(res, right);
    return res;
}

bn* bn_mul(bn const *left, bn const *right){
    bn* res = bn_new();
    return res;
}

bn* bn_div(bn const *left, bn const *right){
    bn* res = bn_new();
    return res;
}

bn* bn_mod(bn const *left, bn const *right){
    bn* res = bn_new();
    return res;
}


const char *bn_to_string(bn const *t, int radix){
    char charValue[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 
        'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    int size = t->sign <= 0;
    bn *a = bn_init(t);

    while(a->sign != 0){
        bn_div_int(a, radix);
        size++;
    }


    char* res = (char*)malloc((size+1) * sizeof(char));
    res[size] = '\0';
    if(t->sign < 0)
        res[0] = '-';
    bn_copy(t, a);

    int r, i = 0;
    do {
        r = bn_div_int(a, radix);
        res[size - 1 - i] = charValue[r];
        i++;
    } while(a->sign != 0);

    bn_delete(a);
    return res;
}


int bn_cmp(bn const *left, bn const *right){
    if(left->sign < right->sign)
        return -1;
    if(left->sign > right->sign)
        return 1;

    int cmp = bn_cmp_abs(left, right);
    return left->sign * cmp;
}

int bn_neg(bn *t){
    t->sign *= -1;
    return 0;
}

int bn_abs(bn *t){
    t->sign *= t->sign;
    return 0;
}

int bn_sign(bn const *t){
    return t->sign;
}
