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
#include <unistd.h>
#include <mpi.h>
#include "list.h"


void factorize(int process_number, int process_count, const char* process_hostname);
//int create_threads(int process_number, int process_count, const char* process_hostname);

/**
 @brief Reads amount of thread. Calls on readnumbers and create threads.
 @return EXIT_SUCCESS if succesfull, error code if error found
 */
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    int process_number = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    int process_count = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
    int hostname_length = -1;
    MPI_Get_processor_name(process_hostname, &hostname_length);

    factorize(process_number, process_count, process_hostname);

    MPI_Finalize();
  } else {
    printf("error: could not init MPI");
    error = EXIT_FAILURE;
  }
  // int error = EXIT_SUCCESS;
  // int64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  // if (argc == 2) {
  //   if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
  //   } else {
  //     fprintf(stderr, "error: invalid thread count\n");
  //     return EXIT_FAILURE;
  //   }
  // }
  // list_t list;
  // list_init(&list);
  // read_numbers(&list);
  // if (read_numbers(&list) == EXIT_FAILURE) {
  //   fprintf(stderr, "error: could not read file\n");
  //   error = 10;
  // }
  // int64_t num_count = list_length(&list);
  // error = create_threads(&list, num_count, thread_count);
  // list_imprimir(&list);
  return error;
}

void factorize(int process_number, int process_count, const char* process_hostname) {

int64_t *values;
size_t value_count = 0;
  if (process_number == 0){
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
      if (count == capacity){
        size_t new_capacity = capacity + 10;
        int64_t *new_elements = (int64_t*) realloc(values, new_capacity * sizeof(int64_t));
        values = new_elements;
        capacity = new_capacity;
      }
    }
    free(prueba);
    value_count = count;
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
    }
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
  }

  for (size_t index = 0; index < value_count; ++index) {
    printf(process_hostname);
    printf(": %d .m: values[%d] == %d\n", process_number,(int)index,(int)values[index]);
  }


}

// int calculate_start(int rank, int end, int workers, int begin) {
//   const int range = end - begin;
//   return begin + rank * (range / workers) + std::min(rank, range % workers);
// }

// int calculate_finish(int rank, int end, int workers, int begin) {
//   return calculate_start(rank + 1, end, workers, begin);
// }


// /**
//  @brief Reads numbers from file and adds the to list
//  @param list_t
//  @return EXIT_SUCCESS if numbers added succesfully, EXIT_FAILURE if error
//  */
// int read_numbers(list_t *list) {
//   int error = EXIT_SUCCESS;
//   int64_t num;
//   int64_t last = -1;
//   char *prueba = malloc(100);
//   int final = 0;
//   while (scanf("%"SCNd64, &num) == 1 || (final = scanf("%s", prueba)) == 1) {
//     if (final == 1) {
//       list_insert_last(list, last);
//       final = 0;
//     } else {
//       list_insert_last(list, num);
//     }
//   }
//   free(prueba);
//   if (list_length(list) == -1) {
//     error = EXIT_FAILURE;
//   }
//   return error;
// }

// int create_threads(list_t *list, int64_t num_count, int64_t thread_count) {
//   int error = EXIT_SUCCESS;

//   #pragma omp parallel for num_threads(thread_count) schedule(runtime)
//   default(none) shared(list, num_count)
//   for (int64_t i = 0; i <= num_count; i++) {
//     node_factorizar(list_get_element(list, i));
//   }
//   return error;
// }
