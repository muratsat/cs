    .text
    .globl  foo
foo:
    movl    %esi, %eax
    cmpl    $2, %esi
    jb      l2
    movl    %eax, %r8d
    movl    (%rdi), %edx
    movl    $1, %esi
l1:
    movl    (%rdi,%rsi,4), %ecx
    movl    %edx, (%rdi,%rsi,4)
    movl    %ecx, -4(%rdi,%rsi,4)
    addq    $1, %rsi
    cmpq    %rsi, %r8
    jne     l1
l2:
    retq
