    .text
    .globl  foo
foo:
    movb    (%rdi), %cl
    leal    -48(%rcx), %edx
    xorl    %eax, %eax
    cmpb    $9, %dl
    ja      l2
    addq    $1, %rdi
    xorl    %eax, %eax
l1:
    leal    (%rax,%rax,4), %eax
    movsbl  %cl, %ecx
    leal    (%rcx,%rax,2), %eax
    addl    $-48, %eax
    movzbl  (%rdi), %ecx
    leal    -48(%rcx), %edx
    addq    $1, %rdi
    cmpb    $10, %dl
    jb      l1
l2:
    retq
