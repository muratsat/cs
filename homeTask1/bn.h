#pragma once
// структура большого числа
struct bn_s;
typedef struct bn_s bn;

enum bn_codes { BN_OK, BN_NULL_OBJECT, BN_NO_MEMORY, BN_DIVIDE_BY_ZERO };

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
bn *bn_add(bn const *left, bn const *right);
// Аналоги операции x = l-r
bn *bn_sub(bn const *left, bn const *right);
// Аналоги операции x = l*r
bn *bn_mul(bn const *left, bn const *right);
// Аналоги операции x = l/r
bn *bn_div(bn const *left, bn const *right);
// Аналоги операции x = l%r
bn *bn_mod(bn const *left, bn const *right);

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

/*  Вспомогательные функции */

// изменить размер числа на new_size
int bn_resize(bn *a, int new_size);

// Скопировать значение числа
// из SRC в DEST
int bn_copy(bn const *src, bn *dest);

// Удалить ведущие нули
int bn_normalize(bn *a);

// умножить длинное на короткое
int bn_mul_int(bn *a, long long b);

// умножить длинное на короткое
// и вернуть остаток
int bn_div_int(bn *a, unsigned int b);

// сравнить модули двуч чисел
// -1, если |a| < |b|
// 0,  если |a| < |b|
// 1,  если |a| > |b|
int bn_cmp_abs(bn const *a, bn const *b);

// сложить модули чисел
// |a| = |a| + |b|
int bn_add_abs(bn *a, bn const *b);

// вычесть модули чисел
// |a| = |a| - |b|
int bn_sub_abs(bn *a, bn const *b);

// приравнять к нулю
void bn_zero(bn *a);

// возвести в квадрат
int bn_square(bn *a);

// напечатать в консоль в
// системе счисления radix
int bn_print(bn *a, int radix, int endl);

// напечатать все цифры в том виде,
// в котором они хранятся в памяти
void bn_debug(bn const *a);

// извлечь квадратный корень из числа
int bn_sqrt(bn *a);

// инициализировать длинное число
// значением числа типа long long
int bn_init_ll(bn *a, long long x);
