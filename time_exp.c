#include "time_exp.h"

#include <stdio.h>
#include <stdlib.h>

int alloc_mem_with_count(FILE *f, int **arr, size_t *n_mem) {
    int rc = 0;
    size_t count = 0;
    while (rc == 0) {
        int tmp;
        if (fscanf(f, "%d", &tmp) != 1)
            rc = 1;
        else
            count++;
    }
    if (feof(f))
        rc = 0;
    if (count <= 0)
        rc = 4;
    rewind(f);
    if (rc == 0) {
        *arr = malloc(count * sizeof(int));
        if (!*arr)
            rc = 2;
        else {
            for (size_t i = 0; i < count; ++i)
                fscanf(f, "%d", &(*arr)[i]);
        }
    }
    *n_mem = count;
    return rc;
}

int alloc_mem_with_capacity(FILE *f, int **arr, size_t *n_mem) {
    *arr = NULL;
    size_t count = 0;
    size_t capacity = 0;
    int rc = 0;
    while (rc == 0) {
        int tmp;
        if (fscanf(f, "%d", &tmp) != 1)
            rc = 1;
        else {
            if (count >= capacity) {
                capacity = capacity == 0 ? 1 : capacity * 2;
                int *new_tmp_arr = realloc(*arr, capacity * sizeof(int));
                if (new_tmp_arr == NULL) {
                    rc = 2;
                    free(*arr);
                } else {
                    *arr = new_tmp_arr;
                }
            }
            (*arr)[count++] = tmp;
        }
    }
    if (rc == 1 && feof(f)) {
        rc = 0;
    }
    *n_mem = count;
    return rc;
}

