#include <stdio.h>
#include "bn.c"

void print(bn* a){
    for(int i = 0; i < a->size; i++)
        printf("%u ", a->digit[i]);
    printf("\n");
}

// TODO: fix this 
int bn_init_string_to10e9(bn *res, const char *init_string){
    int n = strlen(init_string);

    //bn* res = bn_new();
    int size = n/9 + (n%9 != 0);
    res->size = size;
    res->sign = 1;
    res->digit = (unsigned int*)realloc(res->digit, size*sizeof(unsigned int));

    int end = 0;
    if(init_string[0] == '-'){
        res->sign = -1;
        end = 1;
    }
    if(init_string[0] == '+'){
        end = 1;
    }

    int i = n-1, k = 0;
    while(i >= end){
        unsigned int digit = 0, ten = 1;

        for(int j = 0; j < 9 && i-j >= end; j++){
            digit += ten*(init_string[i-j] - '0');
            ten *= 10;
        }

        res->digit[k] = digit;
        k++;
        i -= 9;
    }

    return 0;
}

int main(){
    int n;
    //scanf("%d", &n);

    bn* f1 = bn_new();
    bn* f2 = bn_new();

    //bn_init_int(f1, 1);
    //bn_init_int(f2, 1);
    bn_init_string_to10e9(f1, "123123348596735683123123456789");
    bn_init_string_to10e9(f2, "3845762936593457123456789000");
    //f1->sign = -1;
    //f2->sign = -1;

    bn* f = bn_add(f1, f2);
    bn_add_to(f1, f2);

    printf("\nsign: %d\nsize: %d\n", f1->sign, f1->size);
    printf("%u", f1->digit[f1->size - 1]);
    for(int i = f1->size - 2; i >= 0; i--)
        printf("%09u", f1->digit[i]);

    printf("\n\nsign: %d\nsize: %d\n", f2->sign, f2->size);
    printf("%u", f2->digit[f2->size - 1]);
    for(int i = f2->size - 2; i >= 0; i--)
        printf("%09u", f2->digit[i]);
    printf("\n\n");

    printf("\n\nsign: %d\nsize: %d\n", f->sign, f->size);
    printf("%u", f->digit[f->size - 1]);
    for(int i = f->size - 2; i >= 0; i--)
        printf("%09u", f->digit[i]);
    printf("\n\n");

    bn_delete(f1);
    bn_delete(f2);
    bn_delete(f);
    return 0;
}