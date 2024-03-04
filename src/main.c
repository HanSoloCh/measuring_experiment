#include "time_exp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WITH_COUNT "c"
#define WITH_CAPACITY "r"
#define WITH_WRONG_CAPACITY "w"

#define WITH_FRAGMENTATION_1 "fr"
#define WITH_FRAGMENTATION_2 "fw"

int main(int argc, char **argv) {
    int rc = 0;
    int *arr = NULL;
    size_t n;

    double experimental_time = 0;

    if (argc != 3)
        return 3;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return 4;

    if (strcmp(argv[2], WITH_COUNT) == 0) {
        rc = alloc_mem_with_count(f, &arr, &n, &experimental_time);
    } else if (strcmp(argv[2], WITH_CAPACITY) == 0) {
        rc = alloc_mem_with_right_capacity(f, &arr, &n, &experimental_time);
    } else if (strcmp(argv[2], WITH_WRONG_CAPACITY) == 0) {
        rc = alloc_mem_with_wrong_capacity(f, &arr, &n, &experimental_time);
    } else if (strcmp(argv[2], WITH_FRAGMENTATION_1) == 0) {
        rc = alloc_mem_with_right_capacity_fragmentation(f, &arr, &n, &experimental_time);
    } else if (strcmp(argv[2], WITH_FRAGMENTATION_2) == 0) {
        rc = alloc_mem_with_wrong_capacity_fragmentation(f, &arr, &n, &experimental_time);
    } else {
        rc = 5;
    }

#ifndef LOG
    printf("%.9lf\n", experimental_time);
#endif

    if (rc == 0)
        free(arr);

    fclose(f);
    return rc;
}