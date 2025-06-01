/* memcpy assembly C for x86_64 */

#include <stddef.h>

/* Simple implemenation */
void *memcpy_c_v1(void *dst, const void *src, size_t num)
{
    size_t i;
    unsigned char *p_dst;
    unsigned char *p_src;
    
    p_dst = (unsigned char *) dst;
    p_src = (unsigned char *) src;
    
    for (i = 0; i < num; i++) {
        *p_dst = *p_src;
        p_dst++;
        p_src++;
    }
    
    return dst;
}

/* Advanced implemenation */
void *memcpy_c_v2(void *dst, const void *src, size_t num)
{
    size_t i;
    size_t cnt;     /* Number of 64 Bit values to copy */
    size_t rem;     /* Remaining bytes, if any */
    unsigned char *p_dst;
    unsigned char *p_src;
    unsigned long int *p64_dst;
    unsigned long int *p64_src;
    
    cnt = (num / sizeof(unsigned long int));
    rem = (num % sizeof(unsigned long int));
    
    /* Copy 64 Bit values */
    if (cnt) {
        p64_dst = (unsigned long int *) dst;
        p64_src = (unsigned long int *) src;
        
        for (i = 0; i < cnt; i++) {
            *p64_dst = *p64_src;
            p64_dst++;
            p64_src++;
        }
        
        if (!rem)
            return dst;
    }

    /* Copy remaining bytes */
    if (rem) {
        /* Decrement pointers if necessary */
        if (cnt) {
            p64_dst--;
            p64_src--;
            p_dst = (unsigned char *) p64_dst;
            p_src = (unsigned char *) p64_src;
        } else {
            p_dst = (unsigned char *) dst;
            p_src = (unsigned char *) src;
        }

        for (i = 0; i < rem; i++) {
            *p_dst = *p_src;
            p_dst++;
            p_src++;
        }
    }
    
    return dst;
}
