/*
 * Copyright [2021] Maria Andres
 */

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>
#include "factorize.h"


void init_processes(int process_number, int process_count);
void swap(int *a, int *b);
int calculate(int process_number, int process_count, size_t value_count);

/**
 @brief Initializes MPI, initializes processes
 @return EXIT_SUCCESS if succesfull, EXIT_FAILURE if error found
 */
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    int process_number = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    int process_count = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    init_processes(process_number, process_count);

    MPI_Finalize();
  } else {
    printf("error: could not init MPI");
    error = EXIT_FAILURE;
  }
  return error;
}

/**
 @brief If process 0 reads numbers, sends to other processes. Other processes
 recieve values. Calls block mapping and calls factorize.
 @param process_count overall number of proccesses
 @param process_number current number of proccessses 
 @return void
 */
void init_processes(int process_number, int process_count) {
  int64_t *values;
  size_t value_count = 0;
  int start;
  int end;

  // if process 0
  if (process_number == 0) {
    size_t count = 0;
    size_t capacity = 10;
    values = malloc(10*sizeof(int64_t));

    int64_t num;
    char *prueba = malloc(100);
    int final = 0;
    while (scanf("%"SCNd64, &num) == 1 || (final = scanf("%s", prueba)) == 1) {
      if (final == 1) {
        values[count] = num;
        count++;
        final = 0;
      } else {
        values[count] = num;
        count++;
      }
      if (count == capacity) {
        size_t new_capacity = capacity + 10;
        int64_t *new_elements = (int64_t*) \
        realloc(values, new_capacity * sizeof(int64_t));
        values = new_elements;
        capacity = new_capacity;
      }
    }
    free(prueba);
    value_count = count;

    int *processes = malloc((process_count-1)*sizeof(int));
    for (int target = 1; target < process_count; ++target) {
      assert(sizeof(value_count) == sizeof(uint64_t));
      if (MPI_Send(&value_count, /*count*/ 1, MPI_UINT64_T, target
        , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        printf("could not send value count");
      }
      if (MPI_Send(&values[0], value_count, MPI_DOUBLE, target
        , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        printf("could not send values");
      }
      processes[target-1] = target;
    }

    // randomizes processes for pseudo dynamic mapping
    srand(time(NULL));
    for (int i = process_count-2; i > 0; i--) {
        int j = rand() % (i+/1);
        swap(&processes[i], &processes[j]);
    }

    // block mapping
    for (int i = 0; i < (process_count-1); i++) {
      int start = calculate(i, (process_count-1), value_count);
      if (MPI_Send(&start, /*count*/ 1, MPI_INTEGER, processes[i]
      , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
      printf("could not send start value");
      }
      int end = calculate(i+1, (process_count-1), value_count);
      if (MPI_Send(&end, /*count*/ 1, MPI_INTEGER, processes[i]
      , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
      printf("could not send end value");
      }
    }

  // if other process
  } else {
    if (MPI_Recv(&value_count, /*capacity*/ 1, MPI_UINT64_T, /*source*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      printf("could not receive value count");
    }
    values = malloc(value_count*sizeof(int64_t));
    if (MPI_Recv(&values[0], /*capacity*/ value_count, MPI_DOUBLE, /*source*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      printf("could not receive values");
    }
    if (MPI_Recv(&start, /*capacity*/ 1, MPI_INTEGER, /*source*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      printf("could not receive start value");
    }
    if (MPI_Recv(&end, /*capacity*/ 1, MPI_INTEGER, /*source*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      printf("could not receive end value");
    }
    call_factorize(values, start, end);
  }
}

/**
 @brief Swaps two ints
 @return void
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 @brief Calculates start number using total numbers.
 @return int Start point
 */
int calculate(int process_number, int process_count, size_t value_count) {
    int numperblock = round((double)value_count/process_count);
    int from = process_number*numperblock;
    if (from > (int)value_count) {
      from = (int)value_count;
    }
    if ((int)value_count == 1 && process_count == 1) {
      from = 1;
    }
    return from;
}
