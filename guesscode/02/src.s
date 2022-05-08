    .text
    .globl  foo
foo:
    testl   %esi, %esi
    jle     l1
    movslq  %esi, %rcx
    xorl    %edx, %edx
    xorl    %eax, %eax
l4:
    addl    (%rdi,%rdx,4), %eax
    addq    $2, %rdx
    cmpq    %rcx, %rdx
    jl      l4
    retq
l1:
    xorl    %eax, %eax
    retq
