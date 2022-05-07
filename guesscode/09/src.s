    .text
    .globl  foo
foo:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %rdi, -8(%rbp)
    movq    %rsi, -16(%rbp)
    cmpq    $0, -8(%rbp)
    jle     L1
    movq    -8(%rbp), %rax
    cqto
    movl    $10, %ecx
    idivq   %rcx
    movq    -16(%rbp), %rcx
    addq    $1, %rcx
    movq    %rax, %rdi
    movq    %rcx, %rsi
    callq   foo
    movq    -8(%rbp), %rax
    cqto
    movl    $10, %ecx
    idivq   %rcx
    addq    $48, %rdx
    movq    -16(%rbp), %rcx
    movb    %dl, (%rcx)
L1:
    addq    $16, %rsp
    popq    %rbp
    retq
