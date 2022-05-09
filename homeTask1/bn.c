#include "bn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 4294967296  // 2^32

struct bn_s {
    // массив цифр числа
    unsigned int* digit;

    // Количество выделенной памяти
    // для цифр числа
    int allocd;

    // Количество цифр числа
    int size;

    // Знак числа
    // 1, если положительное
    // 0, если число равно нулю
    // -1, если отрицательно
    int sign;
};
typedef struct bn_s bn;

/*******************************************************************************************************************************************/

int bn_resize(bn* a, int new_size) {
    int old_size = a->size;

    if (a->allocd < new_size) {
        // if(new_size < 2*a->allocd)
        //     new_size = 2*a->allocd;
        a->digit =
            (unsigned int*)realloc(a->digit, new_size * sizeof(unsigned int));
        a->allocd = new_size;
    }
    if (old_size < new_size)
        memset(a->digit + old_size, 0,
               (new_size - old_size) * sizeof(unsigned int));

    a->size = new_size;
    return 0;
}

int bn_copy(bn const* src, bn* dest) {
    dest->sign = src->sign;
    bn_resize(dest, src->size);
    memcpy(dest->digit, src->digit, src->size * sizeof(unsigned int));
    return 0;
}

int bn_normalize(bn* a) {
    int new_size = a->size - 1;

    while (new_size > 0) {
        if (a->digit[new_size] != 0) break;
        new_size--;
    }

    bn_resize(a, new_size + 1);
    if (a->size == 1 && a->digit[0] == 0) a->sign = 0;

    return 0;
}

int bn_mul_int(bn* a, long long b) {
    if (b < 0) {
        a->sign *= -1;
        b = -b;
    }

    int size_a = a->size;
    unsigned long long tmp, carry = 0;

    for (int i = 0; i < size_a; i++) {
        tmp = carry + (unsigned long long)a->digit[i] * b;
        a->digit[i] = tmp % BASE;
        carry = tmp / BASE;
    }

    if (carry != 0) {
        bn_resize(a, size_a + 1);
        a->digit[size_a] = carry;
    }

    bn_normalize(a);
    return 0;
}

int bn_div_int(bn* a, unsigned int b) {
    if (b == 0) return 3;

    int size_a = a->size, remainder = 0;
    unsigned long long tmp;

    for (int i = size_a - 1; i >= 0; i--) {
        tmp = BASE * remainder + a->digit[i];
        a->digit[i] = tmp / b;
        remainder = tmp % b;
    }

    bn_normalize(a);
    return remainder;
}

int bn_cmp_abs(bn const* a, bn const* b) {
    int size_a = a->size, size_b = b->size;

    if (size_a > size_b) return 1;
    if (size_a < size_b) return -1;

    long long diff = 0;
    for (int i = size_a - 1; i >= 0; i--) {
        diff = (long long)a->digit[i] - (long long)b->digit[i];
        if (diff != 0) break;
    }

    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

int bn_add_abs(bn* a, bn const* b) {
    int size_a = a->size, size_b = b->size;

    int size = size_a > size_b ? size_a : size_b;
    bn_resize(a, size);

    unsigned long long tmp, carry = 0;
    for (int i = 0; i < size; i++) {
        tmp = carry;
        if (i < size_a) tmp += a->digit[i];
        if (i < size_b) tmp += b->digit[i];

        a->digit[i] = tmp;
        carry = tmp / BASE;
    }

    if (carry) {
        bn_resize(a, size + 1);
        a->digit[size] = carry;
    }

    bn_normalize(a);
    return 0;
}

int bn_sub_abs(bn* a, bn const* b) {
    int size_a = a->size, size_b = b->size;

    int cmp = bn_cmp_abs(a, b);
    int size = size_a > size_b ? size_a : size_b;
    bn_resize(a, size);

    long long tmp, borrowed = 0;
    for (int i = 0; i < size; i++) {
        tmp = -borrowed;
        if (i < size_a) tmp += cmp * (long long)a->digit[i];
        if (i < size_b) tmp -= cmp * (long long)b->digit[i];

        borrowed = 0;
        if (tmp < 0) {
            borrowed = 1;
            tmp += BASE;
        }

        a->digit[i] = tmp;
    }

    bn_normalize(a);
    return 0;
}

void bn_zero(bn* a) {
    memset(a->digit, 0, a->allocd * sizeof(unsigned int));
    bn_resize(a, 1);
    a->sign = 0;
}

int bn_square(bn* a) {
    int size = a->size;
    int sign = a->sign * a->sign;

    unsigned int* arr = (unsigned int*)malloc(size * sizeof(unsigned int));
    memcpy(arr, a->digit, size * sizeof(unsigned int));

    bn_zero(a);
    bn_resize(a, size * 2);

    for (int i = 0; i < size; i++) {
        unsigned long long tmp, carry = 0;

        for (int j = 0; j < size; j++) {
            tmp = carry +
                  (unsigned long long)arr[i] * (unsigned long long)arr[j] +
                  (unsigned long long)a->digit[i + j];
            a->digit[i + j] = tmp;
            carry = tmp / BASE;
        }
        if (carry) a->digit[i + size] = carry;
    }

    a->sign = sign;
    bn_normalize(a);
    free(arr);
    return 0;
}

int bn_print(bn* a, int radix, int endl) {
    const char* s = bn_to_string(a, radix);
    printf("%s ", s);
    free((void*)s);
    if (endl) printf("\n");
    return 0;
}

void bn_debug(bn const* a) {
    printf("\nsize: %d, sign: %d\n", a->size, a->sign);
    for (int i = a->size - 1; i >= 0; i--) printf("%u ", a->digit[i]);

    printf("\n");
}

/*******************************************************************************************************************************************/

bn* bn_new() {
    bn* a = (bn*)malloc(sizeof(bn));

    int default_size = 100;

    a->digit = (unsigned int*)calloc(default_size, sizeof(unsigned int));
    a->allocd = default_size;

    // a = 0 by default
    a->sign = 0;
    a->size = 1;

    return a;
}

bn* bn_init(bn const* orig) {
    bn* copy = bn_new();
    bn_copy(orig, copy);
    return copy;
}

int bn_init_string(bn* t, const char* init_string) {
    bn_zero(t);
    bn* T = bn_new();
    bn_init_int(T, 1);

    int len = strlen(init_string), end = 0, sign = 1;
    if (init_string[0] == '-') {
        sign = -1;
        end = 1;
    }

    for (int i = len - 1; i >= end; i--) {
        int digit = init_string[i] - '0';

        bn *a = t, *b = T;
        int size_a = a->size, size_b = b->size;
        int size = size_a > size_b ? size_a : size_b;

        bn_resize(a, size);
        unsigned long long tmp, carry = 0;
        for (int i = 0; i < size; i++) {
            tmp = carry;
            if (i < size_a) tmp += a->digit[i];
            if (i < size_b) tmp += (unsigned long long)b->digit[i] * digit;

            a->digit[i] = tmp;
            carry = tmp / BASE;
        }
        if (carry) {
            bn_resize(a, size + 1);
            a->digit[size] = carry;
        }

        bn_mul_int(T, 10);
    }

    t->sign = sign;
    bn_delete(T);
    bn_normalize(t);
    return 0;
}

int bn_init_string_radix(bn* t, const char* init_string, int radix) {
    unsigned char DigitValue[256] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,
        6,  7,  8,  9,  0,  0,  0,  0,  0,  0,  0,  10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
        35, 0,  0,  0,  0,  0,  0,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,
    };

    bn_zero(t);
    bn* T = bn_new();
    bn_init_int(T, 1);

    int len = strlen(init_string), end = 0, sign = 1;
    if (init_string[0] == '-') {
        sign = -1;
        end = 1;
    }

    for (int i = len - 1; i >= end; i--) {
        int digit = DigitValue[(int)init_string[i]];

        bn *a = t, *b = T;
        int size_a = a->size, size_b = b->size;
        int size = size_a > size_b ? size_a : size_b;

        bn_resize(a, size);
        unsigned long long tmp, carry = 0;
        for (int i = 0; i < size; i++) {
            tmp = carry;
            if (i < size_a) tmp += a->digit[i];
            if (i < size_b) tmp += (unsigned long long)b->digit[i] * digit;

            a->digit[i] = tmp;
            carry = tmp / BASE;
        }
        if (carry) {
            bn_resize(a, size + 1);
            a->digit[size] = carry;
        }

        bn_mul_int(T, radix);
    }

    t->sign = sign;
    bn_delete(T);
    bn_normalize(t);
    return 0;
}

int bn_init_int(bn* t, int init_int) {
    t->sign = init_int > 0;
    if (init_int < 0) {
        t->sign = -1;
        init_int *= -1;
    }

    bn_resize(t, 1);
    t->digit[0] = init_int;
    return 0;
}

int bn_delete(bn* t) {
    free(t->digit);
    t->digit = NULL;
    free(t);
    t = NULL;
    return 0;
}

int bn_add_to(bn* a, bn const* b) {
    if (a->sign == b->sign) {
        int size_a = a->size, size_b = b->size;
        int size = size_a > size_b ? size_a : size_b;
        bn_resize(a, size);

        unsigned long long tmp, carry = 0;
        for (int i = 0; i < size; i++) {
            tmp = carry;
            if (i < size_a) tmp += a->digit[i];
            if (i < size_b) tmp += b->digit[i];

            a->digit[i] = tmp;
            carry = tmp / BASE;
        }
        if (carry) {
            bn_resize(a, size + 1);
            a->digit[size] = carry;
        }
        bn_normalize(a);
    }

    else {
        int cmp = bn_cmp_abs(a, b);
        int size_a = a->size, size_b = b->size;
        int size = size_a > size_b ? size_a : size_b;
        bn_resize(a, size);

        long long tmp, borrowed = 0;
        for (int i = 0; i < size; i++) {
            tmp = -borrowed;
            if (i < size_a) tmp += cmp * (long long)a->digit[i];
            if (i < size_b) tmp -= cmp * (long long)b->digit[i];

            borrowed = 0;
            if (tmp < 0) {
                borrowed = 1;
                tmp += BASE;
            }

            a->digit[i] = tmp;
        }
        bn_normalize(a);
        a->sign = cmp < 0 ? b->sign : a->sign;
    }

    return 0;
}

int bn_sub_to(bn* a, bn const* b) {
    if (a->sign != b->sign) {
        int size_a = a->size, size_b = b->size;
        int size = size_a > size_b ? size_a : size_b;
        bn_resize(a, size);

        unsigned long long tmp, carry = 0;
        for (int i = 0; i < size; i++) {
            tmp = carry;
            if (i < size_a) tmp += a->digit[i];
            if (i < size_b) tmp += b->digit[i];

            a->digit[i] = tmp % BASE;
            carry = tmp / BASE;
        }
        if (carry) {
            bn_resize(a, size + 1);
            a->digit[size] = carry;
        }
        bn_normalize(a);
        if (a->sign == 0) a->sign = -b->sign;
    }

    else {
        int cmp = bn_cmp_abs(a, b);
        int size_a = a->size, size_b = b->size;
        int size = size_a > size_b ? size_a : size_b;
        bn_resize(a, size);

        long long tmp, borrowed = 0;
        for (int i = 0; i < size; i++) {
            tmp = -borrowed;
            if (i < size_a) tmp += cmp * (long long)a->digit[i];
            if (i < size_b) tmp -= cmp * (long long)b->digit[i];

            borrowed = 0;
            if (tmp < 0) {
                borrowed = 1;
                tmp += BASE;
            }

            a->digit[i] = tmp % BASE;
        }
        bn_normalize(a);
        a->sign = a->sign * cmp;
    }

    return 0;
}

int bn_mul_to(bn* a, bn const* b) {
    int size_a = a->size, size_b = b->size;
    int sign = a->sign * b->sign;

    unsigned int* arr = (unsigned int*)malloc(size_a * sizeof(unsigned int));
    memcpy(arr, a->digit, size_a * sizeof(unsigned int));

    bn_zero(a);
    bn_resize(a, size_a + size_b);

    for (int i = 0; i < size_b; i++) {
        unsigned long long tmp, carry = 0;

        for (int j = 0; j < size_a; j++) {
            tmp = carry +
                  (unsigned long long)b->digit[i] * (unsigned long long)arr[j] +
                  (unsigned long long)a->digit[i + j];
            a->digit[i + j] = tmp;
            carry = tmp / BASE;
        }
        if (carry) a->digit[i + size_a] = carry;
    }

    a->sign = sign;
    bn_normalize(a);
    free(arr);
    return 0;
}

unsigned int bn_div_bin(bn* a, bn* b) {
    long long int l = 0, r = BASE - 1, m;

    bn* tmp = bn_new();
    while (l <= r) {
        m = (r + l) / 2;
        bn_copy(b, tmp);
        bn_mul_int(tmp, m);
        int cmp = bn_cmp_abs(tmp, a);

        if (cmp < 0)
            l = m + 1;
        else if (cmp > 0)
            r = m - 1;
        else
            break;
    }
    m = (r + l) >> 1;

    bn_delete(tmp);
    return m;
}

int bn_div_to(bn* divident, bn const* divisor) {
    bn* N = bn_init(divident);
    bn_abs(N);
    bn* D = bn_init(divisor);
    bn_abs(D);

    int sign = divident->sign * divisor->sign;

    if (bn_cmp_abs(N, D) < 0) {
        bn_zero(divident);
    }

    else {
        // size of divisor
        int div_size = divisor->size;
        int size_N = N->size, size_d = D->size;
        int size_q = size_N - size_d + 1;
        bn_resize(divident, size_q);

        bn* estimate = bn_new();

        for (int i = size_q - 1; i >= 0; i--) {
            bn_resize(D, i + div_size);
            memcpy(D->digit + i, divisor->digit,
                   div_size * sizeof(unsigned int));
            if (i > 0) memset(D->digit, 0, i * sizeof(unsigned int));

            bn_copy(D, estimate);
            unsigned int digit = bn_div_bin(N, D);
            bn_mul_int(estimate, digit);

            bn_sub_to(N, estimate);
            divident->digit[i] = digit;
        }

        bn_delete(estimate);
    }
    bn_normalize(divident);

    divident->sign = sign;
    if (sign < 0 && N->sign != 0) {
        bn* one = bn_new();
        bn_init_int(one, 1);
        bn_sub_to(divident, one);
        bn_delete(one);
    }

    bn_delete(N);
    bn_delete(D);
    return 0;
}

int bn_mod_to(bn* divident, bn const* divisor) {
    bn* Q = bn_init(divident);
    bn_div_to(Q, divisor);
    bn_mul_to(Q, divisor);

    bn_sub_to(divident, Q);

    bn_delete(Q);
    return 0;
}

int bn_pow_to(bn* a, int n) {
    bn* t = bn_init(a);
    bn_init_int(a, 1);

    while (n > 0) {
        if (n % 2 == 1) bn_mul_to(a, t);

        bn_square(t);
        n /= 2;
    }

    bn_delete(t);
    return 0;
}

int bn_init_ll(bn* a, long long x) {
    bn_resize(a, 1);
    a->digit[0] = x % BASE;
    if (x / BASE > 0) {
        bn_resize(a, 2);
        a->digit[1] = x / BASE;
    }

    if (x < 0)
        a->sign = -1;
    else if (x > 0)
        a->sign = 1;
    else
        a->sign = 0;

    return 0;
}

int bn_sqrt(bn* a) {
    int size_a = a->size;

    // Intermediate divident
    bn* divident = bn_new();
    divident->sign = 1;
    bn_resize(divident, 2 - size_a % 2);

    if (size_a % 2 == 1)
        divident->digit[0] = a->digit[size_a - 1];
    else {
        divident->digit[0] = a->digit[size_a - 2];
        divident->digit[1] = a->digit[size_a - 1];
    }

    // the middle number for binary search
    bn* m = bn_new();
    m->sign = 1;

    long long l = 1, r = BASE - 1, mid = BASE / 2;
    while (l <= r) {
        mid = (l + r) / 2;
        bn_init_ll(m, mid);
        bn_square(m);

        int cmp = bn_cmp_abs(m, divident);
        if (cmp > 0)
            r = mid - 1;
        else if (cmp < 0)
            l = mid + 1;
        else
            break;
    }

    unsigned int first_digit = (l + r) / 2;
    bn_init_ll(m, first_digit);
    bn_square(m);
    bn_sub_to(divident, m);

    // intermediate divisor
    bn* divisor = bn_new();
    divisor->sign = 1;

    // the result number where we
    // write all calculated digits
    bn* res = bn_new();
    res->sign = 1;
    int size = (size_a - 2 + size_a % 2) / 2 + 1;
    bn_resize(res, size);
    res->digit[size - 1] = first_digit;

    // index of current digit of result
    // id = size - 2
    //
    // (subtract 2 because we already
    // know the first digit)
    int id = size - 2;

    for (int i = size_a + size_a % 2 - 3; i >= 0; i -= 2) {
        int dvdnt_size = divident->size;
        bn_resize(divident, dvdnt_size + 2);
        memcpy(divident->digit + 2, divident->digit,
               dvdnt_size * sizeof(unsigned int));
        divident->digit[1] = a->digit[i];
        divident->digit[0] = a->digit[i - 1];

        int div_size = size - id - 1;
        bn_resize(divisor, div_size);
        memcpy(divisor->digit, res->digit + (id + 1),
               div_size * sizeof(unsigned int));
        bn_mul_int(divisor, 2);
        div_size = divisor->size;

        l = 1;
        r = BASE - 1;
        while (l <= r) {
            mid = (r + l) / 2;

            bn_resize(m, div_size + 1);
            memcpy(m->digit + 1, divisor->digit,
                   div_size * sizeof(unsigned int));
            m->digit[0] = mid;
            bn_mul_int(m, mid);

            int cmp = bn_cmp_abs(m, divident);
            if (cmp < 0)
                l = mid + 1;
            else if (cmp > 0)
                r = mid - 1;
            else
                break;
        }
        mid = (r + l) / 2;
        bn_resize(m, div_size + 1);
        memcpy(m->digit + 1, divisor->digit, div_size * sizeof(unsigned int));
        m->digit[0] = mid;
        bn_mul_int(m, mid);

        bn_sub_to(divident, m);

        res->digit[id] = mid;
        id--;
    }

    bn_normalize(res);
    bn_copy(res, a);

    bn_delete(divident);
    bn_delete(divisor);
    bn_delete(res);
    bn_delete(m);
    return 0;
}

int bn_diff(bn const* a, bn const* b) {
    int size_a = a->size, size_b = b->size;
    if (size_a != size_b) return 0;

    for (int i = size_a - 1; i > 0; i--) {
        if (a->digit[i] != b->digit[i]) return 0;
    }

    if (abs(a->digit[0] - b->digit[0]) <= 1) return 1;

    return 0;
}

int bn_root_to(bn* t, int reciprocal) {
    if (reciprocal == 2) return bn_sqrt(t);

    bn* l = bn_new();
    bn_init_int(l, 1);
    bn* r = bn_init(t);
    bn* mid = bn_new();
    bn* tmp = bn_new();

    int diff = bn_diff(l, r);

    while (diff == 0) {
        /* mid = (r + l)/2 */
        bn_copy(r, mid);     // mid = r
        bn_add_to(mid, l);   // mid += l
        bn_div_int(mid, 2);  // mid /= 2

        // tmp = mid^reciprocal
        bn_copy(mid, tmp);
        bn_pow_to(tmp, reciprocal);

        int cmp = bn_cmp(tmp, t);

        if (cmp == 0)
            break;
        else if (cmp > 0)
            bn_copy(mid, r);
        else
            bn_copy(mid, l);

        diff = bn_diff(l, r);
    }

    int cmp = bn_cmp(tmp, t);
    if (cmp > 0) {
        bn* one = bn_new();
        bn_init_int(one, 1);
        bn_sub_to(mid, one);
        bn_delete(one);
    }

    bn_copy(mid, t);

    bn_delete(l);
    bn_delete(r);
    bn_delete(mid);
    bn_delete(tmp);
    return 0;
}

bn* bn_add(bn const* left, bn const* right) {
    bn* res = bn_init(left);
    bn_add_to(res, right);
    return res;
}

bn* bn_sub(bn const* left, bn const* right) {
    bn* res = bn_init(left);
    bn_sub_to(res, right);
    return res;
}

bn* bn_mul(bn const* left, bn const* right) {
    bn* res = bn_init(left);
    bn_mul_to(res, right);
    return res;
}

bn* bn_div(bn const* left, bn const* right) {
    bn* res = bn_init(left);
    bn_div_to(res, right);
    return res;
}

bn* bn_mod(bn const* left, bn const* right) {
    bn* res = bn_init(left);
    bn_mod_to(res, right);
    return res;
}

const char* bn_to_string(bn const* t, int radix) {
    char charValue[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                        '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    int size = t->sign <= 0;
    bn* a = bn_init(t);

    while (a->sign != 0) {
        bn_div_int(a, radix);
        size++;
    }

    char* res = (char*)malloc((size + 1) * sizeof(char));
    res[size] = '\0';
    if (t->sign < 0) res[0] = '-';
    bn_copy(t, a);

    int r, i = 0;
    do {
        r = bn_div_int(a, radix);
        res[size - 1 - i] = charValue[r];
        i++;
    } while (a->sign != 0);

    bn_delete(a);
    return res;
}

int bn_cmp(bn const* left, bn const* right) {
    if (left->sign < right->sign) return -1;
    if (left->sign > right->sign) return 1;

    int cmp = bn_cmp_abs(left, right);
    return left->sign * cmp;
}

int bn_neg(bn* t) {
    t->sign *= -1;
    return 0;
}

int bn_abs(bn* t) {
    t->sign *= t->sign;
    return 0;
}

int bn_sign(bn const* t) { return t->sign; }
