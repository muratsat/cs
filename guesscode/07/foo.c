// void foo(void* rdi, double xmm0, double xmm1, double xmm2){
//     double l0 = 3.0, l1 = 7.0;
//     xmm0 += xmm0;
//     xmm1 *= l0;
//     xmm1 += xmm0;
//     xmm2 *= l1;
//     xmm2 += xmm1;
//     *(double*)rdi = xmm2;
// }

void foo(double* x, double a, double b, double c){
    *x = 2*a + 3*b + 7*c;
}

/*
l0:
    .quad   0x4008000000000000 = 3
l1:
    .quad   0x401c000000000000 = 7
    .text
    .globl  foo
foo:
    addsd   %xmm0, %xmm0
    mulsd   l0(%rip), %xmm1
    addsd   %xmm0, %xmm1
    mulsd   l1(%rip), %xmm2
    addsd   %xmm1, %xmm2
    movsd   %xmm2, (%rdi)
    retq

xmm0 += xmm0;
xmm1 *= l0;
xmm1 += xmm0;
xmm2 *= l1
xmm2 += xmm1;
rdi[] = xmm2;

*/