#ifndef _TIME_EXP_H
#define _TIME_EXP_H

#include <stdio.h>

#define INIT_MEASURE struct timespec start, end
#define START_MEASURE clock_gettime(CLOCK_REALTIME, &start)
#define STOP_MEASURE clock_gettime(CLOCK_REALTIME, &end)
#define CALK_TIME_OF_MEASURE long seconds = end.tv_sec - start.tv_sec;       \
                             long nanoseconds = end.tv_nsec - start.tv_nsec; \
                             double elapsed = seconds + nanoseconds * 1e-9

#define GET_TIME_OF_MEASURE elapsed

int alloc_mem_with_count(FILE *f, int **arr, size_t *n_mem, double *experimental_time);

int alloc_mem_with_right_capacity(FILE *f, int **arr, size_t *n_mem, double *experimental_time);

int alloc_mem_with_wrong_capacity(FILE *f, int **arr, size_t *n_mem, double *experimental_time);

int alloc_mem_with_right_capacity_fragmentation(FILE *f, int **arr, size_t *n_mem, double *experimental_time);

int alloc_mem_with_wrong_capacity_fragmentation(FILE *f, int **arr, size_t *n_mem, double *experimental_time);

#endif
