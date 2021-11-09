#include <stdio.h>
#include "bn.c"

void print(bn* a){
    for(int i = 0; i < a->size; i++)
        printf("%u ", a->digit[i]);
    printf("\n");
}

int main(){
    bn *a = bn_new();
    bn *b = bn_new();

    a->size = 3; a->sign = 1;
    a->digit = (unsigned int*)realloc(a->digit, a->size*sizeof(unsigned int));
    a->digit[0] = 1;
    a->digit[1] = 4;
    a->digit[2] = 3;

    b->size = 3; b->sign = 1;
    b->digit = (unsigned int*)realloc(b->digit, b->size*sizeof(unsigned int));
    b->digit[0] = 0;
    b->digit[1] = 1;
    b->digit[2] = 3;
    //b->digit[1] = 4294967295;

    bn* c = bn_sub_abs(a, b);

    for(int i = 0; i < a->size; i++)
        printf("%u ", a->digit[i]);
    printf("\n");

    for(int i = 0; i < b->size; i++)
        printf("%u ", b->digit[i]);
    printf("\n");

    for(int i = 0; i < c->size; i++)
        printf("%u ", c->digit[i]);
    printf("\n");

    bn_delete(a);
    bn_delete(b);
    bn_delete(c);
    return 0;
}