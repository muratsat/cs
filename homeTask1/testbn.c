#include <stdio.h>
#include "bn.c"

int main() {
    bn *a = bn_new(); // a = 0
    bn *b = bn_init(a); // b то>е = 0
    int code = bn_init_string(a, "123456789012345678");
    // a = 123456789012345678
    // Gдес+ и далее code - код ошибки.
    // 0 - всё хорошо
    // Не 0 - что-то пошло не так.
    code = bn_init_int(b, 999); // b = 999
    code = bn_add_to(a, b); // a = 123456789012346677
    code = bn_pow_to(b, 5); // b = 999^5
    code = bn_root_to(b, 5); // b = 999
    code = bn_init_int(a, 0); // a = 0
    code = bn_div_to(b,a); // OOPS, 999/0
    if (code != 0)
        printf("bn_div_to failed, code=%d\n", code);

    bn *c = bn_new();
    code = bn_init(c, 222);
    bn *d = bn_new();
    code = bn_init(d, 333);
    bn *e = bn_add(c, d); // e = 555
    bn *f = bn_mod(e, c); // f = 111
    const char *r1 = bn_to_string(f,10); // r1 -> "111"
    printf("f=%s\n", r1);
    free(r1);
    code = bn_cmp(c, d);

    if (code < 0)
        printf("c < d\n");
    else if (code == 0)
        printf("c == d\n");
    else
        printf("c > d\n");

    code = bn_neg(b); // b = -999;
    int bsign = bn_sign(b); // bsign = -1
    code = bn_abs(b); // b = 999;

    bn_delete(f); // Забудете удалить - провалите тесты
    bn_delete(e);
    bn_delete(d);
    bn_delete(c);
    bn_delete(b);
    bn_delete(a);
    return 0;
}