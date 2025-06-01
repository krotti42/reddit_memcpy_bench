/**
 *
 * Copyright (c) 2024 Johannes Krottmayer <johannes@krotti42.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef _ASM_H
#define _ASM_H

#ifndef _ASM_ASSEMBLY_
#error Do not include this header in C sources
#endif

/* Import assembly functions */
#define IMPORT_ASM(name) \
            .extern name ;

/* Import C functions */
#define IMPORT_C(name) \
            .extern name ;

/* Entry */
#define ENTRY(name) ; \
        .globl name ; \
        .align ; \
        name: ;

/* Function */
#define FUNCTION_S(name) ; \
        .func name,name ; \
        .type name,%function ; \
        .globl name ; \
        .align ; \
        name: ;

#define FUNCTION_E(name) ; \
        .size name, . - name ; \
        .endfunc ;

#endif
