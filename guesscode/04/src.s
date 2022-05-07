    .text
    .globl  foo
foo:
    movb    (%rdi), %al
    movb    %al, (%rsi)
    testb   %al, %al
    je      l2
    xorl    %eax, %eax
l1:
    movzbl  1(%rdi,%rax), %ecx
    movb    %cl, 1(%rsi,%rax)
    addq    $1, %rax
    testb   %cl, %cl
    jne     l1
    retq
l2:
    xorl    %eax, %eax
    retq
