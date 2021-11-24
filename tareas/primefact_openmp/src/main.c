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
#include <omp.h>
#include "list.h"


void* factorize_threads(void *data);
int read_numbers(list_t *list);
int create_threads(list_t *list, int64_t num_count, int64_t thread_count);

/**
 @brief Reads amount of thread. Calls on readnumbers and create threads.
 @return EXIT_SUCCESS if succesfull, error code if error found
 */
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  int64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
    } else {
      fprintf(stderr, "error: invalid thread count\n");
      return EXIT_FAILURE;
    }
  }
  list_t list;
  list_init(&list);
  read_numbers(&list);
  if (read_numbers(&list) == EXIT_FAILURE) {
    fprintf(stderr, "error: could not read file\n");
    error = 10;
  }
  int64_t num_count = list_length(&list);
  error = create_threads(&list, num_count, thread_count);
  list_imprimir(&list);
  return error;
}

/**
 @brief Reads numbers from file and adds the to list
 @param list_t
 @return EXIT_SUCCESS if numbers added succesfully, EXIT_FAILURE if error
 */
int read_numbers(list_t *list) {
  int error = EXIT_SUCCESS;
  int64_t num;
  int64_t last = -1;
  char *prueba = malloc(100);
  int final = 0;
  while (scanf("%"SCNd64, &num) == 1 || (final = scanf("%s", prueba)) == 1) {
    if (final == 1) {
      list_insert_last(list, last);
      final = 0;
    } else {
      list_insert_last(list, num);
    }
  }
  free(prueba);
  if (list_length(list) == -1) {
    error = EXIT_FAILURE;
  }
  return error;
}

int create_threads(list_t *list, int64_t num_count, int64_t thread_count) {
  int error = EXIT_SUCCESS;

  #pragma omp parallel for num_threads(thread_count) schedule(runtime) \
  default(none) shared(list, num_count)
  for (int64_t i = 0; i <= num_count; i++) {
    node_factorizar(list_get_element(list, i));
  }
  return error;
}
