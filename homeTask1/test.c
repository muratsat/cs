#include <stdio.h>
#include "bn.c"

int main(){
    // a = 1337
    bn* a = bn_new();
    bn_init_string(a, 1337);

    // b = 0b101
    bn* b = bn_new();
    bn_init_string_radix(b, "101", 2);

    // a = a + b
    bn_add_to(a, b);

    // вывести в консоль десятичное 
    // представление числа a
    bn_print(a, 10, 1);


    bn_delete(a);
    bn_delete(b);
    return 0;
}