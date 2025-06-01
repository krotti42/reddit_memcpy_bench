/* memcpy assembly variants for x86_64 */

#define _ASM_ASSEMBLY_

#include "asm.h"

.text

/* Using loop instruction */
FUNCTION_S(memcpy_asm_v1)
    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %rdi
    movq %rdi, %rbx
    movq %rdx, %rcx
    jrcxz 6f
    /* Check if we can copy quad words */
    movq %rdx, %rax
    movq $0, %rdx
    movq $8, %rcx
    div %rcx
    movq %rax, %rcx
    jrcxz 2f
    /* Copy quad words */
1:
    movq (%rsi), %rax
    movq %rax, (%rbx)
    addq $8, %rsi
    addq $8, %rbx
    loopnz 1b
2:
    /* Check if we can copy (remaining) double words */
    movq %rdx, %rax
    movq $0, %rdx
    movq $4, %rcx
    div %rcx
    movq %rax, %rcx
    jrcxz 4f
3:
    /* Copy (remaining) double words */
    movl (%rsi), %eax
    movl %eax, (%rbx)
    addq $4, %rsi
    addq $4, %rbx
    loopnz 3b
4:
    movq %rdx, %rcx
    jrcxz 6f
5:
    /* Copy remaining bytes */
    movb (%rsi), %al
    movb %al, (%rbx)
    incq %rsi
    incq %rbx
    loopnz 5b
6:
    popq %rax
    popq %rbx
    popq %rbp
    ret
FUNCTION_E(memcpy_asm_v1)

/* Without loop instruction */
FUNCTION_S(memcpy_asm_v2)
    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %rdi
    movq %rdi, %rbx
    movq %rdx, %rcx
    jrcxz 6f
    /* Check if we can copy quad words */
    movq %rdx, %rax
    movq $0, %rdx
    movq $8, %rcx
    div %rcx
    movq %rax, %rcx
    jrcxz 2f
    /* Copy quad words */
1:
    movq (%rsi), %rax
    movq %rax, (%rbx)
    addq $8, %rsi
    addq $8, %rbx
    decq %rcx
/*    cmpq $0, %rcx */
    jnz 1b
2:
    /* Check if we can copy (remaining) double words */
    movq %rdx, %rax
    movq $0, %rdx
    movq $4, %rcx
    div %rcx
    movq %rax, %rcx
    jrcxz 4f
3:
    /* Copy (remaining) double words */
    movl (%rsi), %eax
    movl %eax, (%rbx)
    addq $4, %rsi
    addq $4, %rbx
    loopnz 3b
4:
    movq %rdx, %rcx
    jrcxz 6f
5:
    /* Copy remaining bytes */
    movb (%rsi), %al
    movb %al, (%rbx)
    incq %rsi
    incq %rbx
    loopnz 5b
6:
    popq %rax
    popq %rbx
    popq %rbp
    ret
FUNCTION_E(memcpy_asm_v2)

FUNCTION_S(memcpy_asm_v3)
    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %rdi
    movq %rdi, %rbx
    movq %rdx, %rcx
    cmpq $0, %rcx
    je 8f
#ifdef __SSE2__
    /* Check if we can copy double quad words */
    movq %rdx, %rax
    movq $0, %rdx
    movq $32, %rcx
    div %rcx
    movq %rax, %rcx
    cmpq $0, %rcx
    je 2f
    movq $32, %rax
    /* Copy quad words */
1:
    movdqa (%rsi), %xmm1
    movdqa %xmm1, (%rbx)
    movdqa 16(%rsi), %xmm1
    movdqa %xmm1, 16(%rbx)
    addq %rax, %rsi
    addq %rax, %rbx
    decq %rcx
    jnz 1b
#endif
2:
    /* Check if we can copy quad words */
    movq %rdx, %rax
    movq $0, %rdx
    movq $8, %rcx
    div %rcx
    movq %rax, %rcx
    cmpq $0, %rcx
    je 4f
    /* Copy quad words */
3:
    movq (%rsi), %rax
    movq %rax, (%rbx)
    addq $8, %rsi
    addq $8, %rbx
    decq %rcx
    jnz 3b
4:
    /* Check if we can copy (remaining) double words */
    movq %rdx, %rax
    movq $0, %rdx
    movq $4, %rcx
    div %rcx
    movq %rax, %rcx
    cmpq $0, %rcx
    je 6f
5:
    /* Copy (remaining) double words */
    movl (%rsi), %eax
    movl %eax, (%rbx)
    addq $4, %rsi
    addq $4, %rbx
    decq %rcx
    jnz 5b
6:
    movq %rdx, %rcx
    cmpq $0, %rcx
    je 8f
7:
    /* Copy remaining bytes */
    movb (%rsi), %al
    movb %al, (%rbx)
    incq %rsi
    incq %rbx
    decq %rcx
    jnz 7b
8:
    popq %rax
    popq %rbx
    popq %rbp
    ret
FUNCTION_E(memcpy_asm_v3)

.end
