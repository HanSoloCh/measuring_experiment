#include "time_exp.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define WITH_COUNT 'c'
#define WITH_CAPACITY 'r'

int main(int argc, char **argv) {
    int rc = 0;
    int *arr;
    size_t n;

    clock_t start, end;
    double cpu_time_used;

    if (argc != 3)
        return 3;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return 4;

    if (*argv[2] == WITH_COUNT) {
        start = clock();
        rc = alloc_mem_with_count(f, &arr, &n);
        end = clock();
    } else if (*argv[2] == WITH_CAPACITY) {
        start = clock();
        rc = alloc_mem_with_capacity(f, &arr, &n);
        end = clock();
    } else {
        rc = 5;
    }

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%lf\n", cpu_time_used);
    if (rc == 0)
        free(arr);

    fclose(f);
    return rc;
}