#ifndef _TIME_EXP_H
#define _TIME_EXP_H

#include <stdio.h>
#include <time.h>

#define MEASURE clock_t start, stop
#define START_MEASURE start = clock()
#define STOP_MEASURE stop = clock()
#define GET_TIME_OF_MEASURE stop - start

int alloc_mem_with_count(FILE *f, int **arr, size_t *n_mem);

int alloc_mem_with_right_capacity(FILE *f, int **arr, size_t *n_mem);

int alloc_mem_with_wrong_capacity(FILE *f, int **arr, size_t *n_mem);

int alloc_mem_with_right_capacity_fragmentation(FILE *f, int **arr, size_t *n_mem, clock_t *extra_time);

int alloc_mem_with_wrong_capacity_fragmentation(FILE *f, int **arr, size_t *n_mem, clock_t *extra_time);

#endif
