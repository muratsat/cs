    .text
    .globl  foo
foo:
    movsd   (%rsi), %xmm1
    xorpd   %xmm0, %xmm0
    ucomisd %xmm0, %xmm1
    jbe     l3
    addq    $8, %rsi
l2:
    addsd   (%rdi), %xmm1
    movsd   %xmm1, (%rdi)
    movsd   (%rsi), %xmm1
    addq    $8, %rsi
    ucomisd %xmm0, %xmm1
    ja      l2
l3:
    retq
