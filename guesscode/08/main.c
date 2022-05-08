#include <stdio.h>

long long foo(const char* s);

int main() {
    const char *str = "4294967296";

    printf("%lld \n", foo(str));
}