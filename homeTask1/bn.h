#pragma once
// структура большого числа
struct bn_s;
typedef struct bn_s bn;

enum bn_codes {
    BN_OK, BN_NULL_OBJECT, BN_NO_MEMORY, BN_DIVIDE_BY_ZERO
};

// Создать новое BN 
bn *bn_new(); 
// Создать копию существующего BN
bn *bn_init(bn const *orig); 


// Инициализировать значение BN десятичным представлением строки
int bn_init_string(bn *t, const char *init_string);

// Инициализировать значение BN предствалением строки
// в системе счисления radix
int bn_init_string_radix(bn *t, const char *init_string, int radix);

// Инициализировать значение BN заданным целым числом
int bn_init_int(bn *t, int init_int);

// Уничтожить BN (освободить память)
int bn_delete(bn *t);

// Операция, аналогичная +=
int bn_add_to(bn *t, bn const *right);
// Операция, аналогичная -=
int bn_sub_to(bn *t, bn const *right);
// Операция, аналогичная *=
int bn_mul_to(bn *t, bn const *right);
// Операция, аналогичная /=
int bn_div_to(bn *t, bn const *right);
// Операция, аналогичная %=
int bn_mod_to(bn *t, bn const *right);

// Возвести число в степень degree
int bn_pow_to(bn *t, int degree);

// Извлечь корень степени reciplocal из BN
int bn_root_to(bn *t, int reciprocal);

// Аналоги операции x = l+r 
bn* bn_add(bn const *left, bn const *right);
// Аналоги операции x = l-r 
bn* bn_sub(bn const *left, bn const *right);
// Аналоги операции x = l*r 
bn* bn_mul(bn const *left, bn const *right);
// Аналоги операции x = l/r 
bn* bn_div(bn const *left, bn const *right);
// Аналоги операции x = l%r 
bn* bn_mod(bn const *left, bn const *right);

// Выдать представление BN в системе счисления radix в виде строки
// Строку после использования потребуется удалить.
const char *bn_to_string(bn const *t, int radix);

// Если левое меньше, вернуть <0; если равны, вернуть 0; иначе >0
int bn_cmp(bn const *left, bn const *right);

// Изменить знак на противоположный
int bn_neg(bn *t);
// Взять модуль
int bn_abs(bn *t);
//-1 если t<0; 0 если t = 0, 1 если t>0
int bn_sign(bn const *t); 

/* Headers for helper functions */

// Assign new size to bignum A
int bn_resize(bn* a, int new_size);

// Copy a bignum from SRC to DEST
int bn_copy(bn const *src, bn *dest);

// Remove trailing zeros
int bn_normalize(bn* a);

// Multiply bignum A by int B
int bn_mul_int(bn* a, long long b);

// Dibide bignum A by int B
// and return the remainder
int bn_div_int(bn* a, unsigned int b);

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

// Find the square of a number
int bn_square(bn* a);

// Print number
int bn_print(bn* a, int radix, int endl);

// print all digits in base 2^32
void bn_debug(bn const* a);

// extract square root from number
int bn_sqrt(bn* a);

// initialize number with long long integer
int bn_init_ll(bn* a, long long x);
