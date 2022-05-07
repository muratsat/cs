#include <stdio.h>

int foo(int a, char* s);

int main() {
    char s[100];
    foo(1234, s);
    printf("%s\n", s);
}