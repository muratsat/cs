    .text
    .globl  foo
foo:
    movb    (%rsi), %al
    movb    (%rdi), %cl
    cmpb    %al, %cl
    jne     l5
    movl    $1, %edx
l2:
    testb   %al, %al
    je      l3
    movzbl  (%rsi,%rdx), %eax
    movzbl  (%rdi,%rdx), %ecx
    addq    $1, %rdx
    cmpb    %al, %cl
    je      l2
l5:
    movsbl  %al, %edx
    movsbl  %cl, %eax
    subl    %edx, %eax
    retq
l3:
    xorl    %eax, %eax
    retq
