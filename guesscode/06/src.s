    .text
    .globl  foo
foo:
    movq    $0, (%rdi)
    xorl    %eax, %eax
l1:
    xorl    %ecx, %ecx
l2:
    movq    (%rsi,%rcx,8), %rdx
    addq    %rdx, (%rdi)
    addq    $1, %rcx
    cmpq    $10, %rcx
    jne     l2
    addq    $1, %rax
    addq    $80, %rsi
    cmpq    $10, %rax
    jne     l1
    xorl    %eax, %eax
    retq
