    .text
    .globl foo
foo:
    xor %ecx,%ecx   
    mov (%rdi),%rax 
    add %rax,%rsi   
    and %ecx,%eax   
    ret