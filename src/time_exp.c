#include "time_exp.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define N_BLOCK 10000


static void block_mem(int **mem_arr, size_t n, size_t i) {
    if (i >= n) {
        i %= n;
        free(mem_arr[i]);
    }
    mem_arr[i] = malloc( N_BLOCK);
    assert(mem_arr[i] != NULL);
}

static void block_free(int **mem_arr, size_t n) {
    for (size_t i = 0; i < n; ++i)
        free(mem_arr[i]);
}

int alloc_mem_with_count(FILE *f, int **arr, size_t *n_mem, double *expetimental_time) {
    INIT_MEASURE;

    int rc = 0;
    size_t count = 0;
    START_MEASURE;
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
    STOP_MEASURE;
    CALK_TIME_OF_MEASURE;
    *expetimental_time = GET_TIME_OF_MEASURE;

    *n_mem = count;
    return rc;
}

int alloc_mem_with_right_capacity(FILE *f, int **arr, size_t *n_mem, double *expetimental_time) {
    INIT_MEASURE;
    
    *arr = NULL;
    size_t count = 0;
    size_t capacity = 0;
    int rc = 0;
    START_MEASURE;
    while (rc == 0) {
        int tmp;
        if (fscanf(f, "%d", &tmp) != 1)
            rc = 1;
        else {
            if (count >= capacity) {
                capacity = capacity == 0 ? 1 : capacity * 2;
                int *new_tmp_arr = realloc(*arr, capacity * sizeof(int));
#ifdef LOG
                printf("realloc: %p, count: %zu, capacity: %zu\n", new_tmp_arr, count, capacity);
#endif
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
    STOP_MEASURE;
    CALK_TIME_OF_MEASURE;
    *expetimental_time = GET_TIME_OF_MEASURE;
    
    if (rc == 1 && feof(f)) {
        rc = 0;
    }
    *n_mem = count;
    return rc;
}

int alloc_mem_with_wrong_capacity(FILE *f, int **arr, size_t *n_mem, double *expetimental_time) {
    INIT_MEASURE;

    *arr = NULL;
    size_t count = 0;
    size_t capacity = 0;
    int rc = 0;
    START_MEASURE;
    while (rc == 0) {
        int tmp;
        if (fscanf(f, "%d", &tmp) != 1)
            rc = 1;
        else {
            if (count >= capacity) {
                capacity++;
                int *new_tmp_arr = realloc(*arr, capacity * sizeof(int));
#ifdef LOG
                printf("realloc: %p, count: %zu, capacity: %zu\n", new_tmp_arr, count, capacity);
#endif
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
    STOP_MEASURE;
    CALK_TIME_OF_MEASURE;
    *expetimental_time = GET_TIME_OF_MEASURE;
    
    if (rc == 1 && feof(f)) {
        rc = 0;
    }
    *n_mem = count;
    return rc;
}

int alloc_mem_with_right_capacity_fragmentation(FILE *f, int **arr, size_t *n_mem, double *expetimental_time) {
    INIT_MEASURE;
    *expetimental_time = 0;
    
    // Массив для блоков искусственной фрагментации
    int *mem_arr[N_BLOCK] = {NULL};
    // Количество вызовов realloc
    size_t count_of_realloc = 0;

    int rc = 0;

    *arr = NULL;
    size_t count = 0;
    size_t capacity = 0;
    while (rc == 0) {
        START_MEASURE;
        int tmp;
        if (fscanf(f, "%d", &tmp) != 1)
            rc = 1;
        else {
            if (count >= capacity) {
                capacity = capacity == 0 ? 1 : capacity * 2;
                int *new_tmp_arr = realloc(*arr, capacity * sizeof(int));
#ifdef LOG
                printf("realloc: %p, count: %zu, capacity: %zu\n", new_tmp_arr, count, capacity);
#endif
                if (new_tmp_arr == NULL) {
                    rc = 2;
                    free(*arr);
                } else {
                    *arr = new_tmp_arr;
                }
            }
            (*arr)[count++] = tmp;
        }
        STOP_MEASURE;
        CALK_TIME_OF_MEASURE;
        *expetimental_time += GET_TIME_OF_MEASURE;
        
        block_mem(mem_arr, N_BLOCK, count_of_realloc++);
    }
    
    if (rc == 1 && feof(f)) {
        rc = 0;
    }
    block_free(mem_arr, N_BLOCK);
    
    *n_mem = count;
    return rc;
}


int alloc_mem_with_wrong_capacity_fragmentation(FILE *f, int **arr, size_t *n_mem, double *expetimental_time) {
    INIT_MEASURE;
    *expetimental_time = 0;
    // Массив для блоков искусственной фрагментации
    int *mem_arr[N_BLOCK] = {NULL};
    // Количество вызовов realloc
    size_t count_of_realloc = 0;

    int rc = 0;

    *arr = NULL;
    size_t count = 0;
    size_t capacity = 0;
    while (rc == 0) {
        START_MEASURE;
        int tmp;
        if (fscanf(f, "%d", &tmp) != 1)
            rc = 1;
        else {
            if (count >= capacity) {
                capacity++;
                int *new_tmp_arr = realloc(*arr, capacity * sizeof(int));
#ifdef LOG
                printf("realloc: %p, count: %zu, capacity: %zu\n", new_tmp_arr, count, capacity);
#endif
                if (new_tmp_arr == NULL) {
                    rc = 2;
                    free(*arr);
                } else {
                    *arr = new_tmp_arr;
                }
            }
            (*arr)[count++] = tmp;
        }
        STOP_MEASURE;
        block_mem(mem_arr, N_BLOCK, count_of_realloc++);
        CALK_TIME_OF_MEASURE;
        *expetimental_time += GET_TIME_OF_MEASURE;
    }
    
    if (rc == 1 && feof(f)) {
        rc = 0;
    }
    block_free(mem_arr, N_BLOCK);

    *n_mem = count;
    return rc;
}
