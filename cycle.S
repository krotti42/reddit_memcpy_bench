/* Read TSC */

#define _ASM_ASSEMBLY_

#include "asm.h"

.text

FUNCTION_S(get_tsc)
    pushq %rbp
    movq %rsp, %rbp
    rdtsc
    shl $32, %rdx
    or %rdx, %rax
    popq %rbp
    ret
FUNCTION_E(get_tsc)

.end
