/*
 * Copyright [2021] Maria Andres
 */
#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "list.h"

// thread_shared_data_t
typedef struct shared {
  int64_t thread_count;
  List list;
  //mutex
  //pos
} shared_data_t;

// thread_private_data_t
typedef struct private {
  uint64_t thread_number;
  shared_data_t* shared_data;
} private_data_t;

int read_numbers(shared_data_t* shared_data) {
  int64_t num;
  int last = -1;
  char *prueba = malloc(100);
  int final = 0;
  while ((scanf("%"SCNd64, &num) == 1 || (final = scanf("%s", prueba)) == 1)) {
    if (final == 1) {
      list_insert_last(&shared_data->list, last);
      final = 0;
    } else {
      list_insert_last(&shared_data->list, num);
    }
  }
  free(prueba);
  return EXIT_SUCCESS;
}


// procedure main
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


  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    List list_temp;
    if (list_init(&list_temp)){
      shared_data->list = list_temp;
      list_destroy(&list_temp);
    } else {
      fprintf(stderr, "Error: could not create list\n");
      error = 12;
    }
    //createthreads
    free(shared_data);
  } else {

    fprintf(stderr, "error: could not allocate shared memory\n");
    error = 11;
  }
  return error;
}