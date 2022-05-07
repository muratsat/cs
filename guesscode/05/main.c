#include <stdio.h>

int foo(const char* a, const char* b);

int main() {
    const char* a = "murat";
    const char* b = "muratb";
    printf("%d\n", foo(a, b));
}