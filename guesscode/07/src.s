    .text
    .section    .rodata
l0:
    .quad   0x4008000000000000
l1:
    .quad   0x401c000000000000
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
