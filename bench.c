/* Quick and dirty benchmark */

#define BENCH_LOOPS       1024
#define BENCH_SIZE        16384

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long get_tsc(void);
extern void *memcpy_asm_v1(void *, const void *, size_t);
extern void *memcpy_asm_v2(void *, const void *, size_t);
extern void *memcpy_asm_v3(void *, const void *, size_t);
extern void *memcpy_c_v1(void *, const void *, size_t);
extern void *memcpy_c_v2(void *, const void *, size_t);

int compare(const void* a, const void* b)
{
    return (*(unsigned long*)a - *(unsigned long*)b);
}

void print_result(unsigned long result[])
{
    int i;
    unsigned long avg = 0;
    
    qsort(result, BENCH_LOOPS, sizeof(unsigned long), compare);
    printf("Min: %lu\n", result[0]);
    printf("Max: %lu\n", result[BENCH_LOOPS - 1]);
    
    for (i = 0; i < BENCH_LOOPS; i++) {
        avg += result[i];
    }
    
    printf("Avg: %lu\n", avg / BENCH_LOOPS);
}

int main(int argc, char *argv[])
{
    char *buf1[BENCH_SIZE];
    char *buf2[BENCH_SIZE];
    unsigned long result[BENCH_LOOPS];
    int i;
    unsigned long tsc_start, tsc_end;
    

    printf("Speed memcpy_asm_v1():\n");
    
    for (i = 0; i < BENCH_LOOPS; i++) {
        memset(buf1, 0xFF, sizeof(buf1));
        memset(buf2, 0x00, sizeof(buf2));
        tsc_start = get_tsc();
        memcpy_asm_v1(buf2, buf1, sizeof(buf1));
        tsc_end = get_tsc();
        result[i] = tsc_end - tsc_start;
    }
    
    print_result(result);

    printf("Speed memcpy_asm_v2():\n");

    for (i = 0; i < BENCH_LOOPS; i++) {
        memset(buf1, 0xFF, sizeof(buf1));
        memset(buf2, 0x00, sizeof(buf2));
        tsc_start = get_tsc();
        memcpy_asm_v2(buf2, buf1, sizeof(buf1));
        tsc_end = get_tsc();
        result[i] = tsc_end - tsc_start;
    }

    print_result(result);

    printf("Speed memcpy_asm_v3():\n");

    for (i = 0; i < BENCH_LOOPS; i++) {
        memset(buf1, 0xFF, sizeof(buf1));
        memset(buf2, 0x00, sizeof(buf2));
        tsc_start = get_tsc();
        memcpy_asm_v3(buf2, buf1, sizeof(buf1));
        tsc_end = get_tsc();
        result[i] = tsc_end - tsc_start;
    }

    print_result(result);
    
    printf("Speed memcpy_c_v1():\n");
    
    for (i = 0; i < BENCH_LOOPS; i++) {
        memset(buf1, 0xFF, sizeof(buf1));
        memset(buf2, 0x00, sizeof(buf2));
        tsc_start = get_tsc();
        memcpy_c_v1(buf2, buf1, sizeof(buf1));
        tsc_end = get_tsc();
        result[i] = tsc_end - tsc_start;
    }
    
    print_result(result);

    printf("Speed memcpy_c_v2():\n");

    for (i = 0; i < BENCH_LOOPS; i++) {
        memset(buf1, 0xFF, sizeof(buf1));
        memset(buf2, 0x00, sizeof(buf2));
        tsc_start = get_tsc();
        memcpy_c_v2(buf2, buf1, sizeof(buf1));
        tsc_end = get_tsc();
        result[i] = tsc_end - tsc_start;
    }

    print_result(result);
    
    return 0;
}
