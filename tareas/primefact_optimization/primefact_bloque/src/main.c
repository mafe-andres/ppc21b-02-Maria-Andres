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
#include <math.h>
#include "list.h"

/**
 @struct Shared_data
 @brief Stores the list, the position in the list, amount of threads and mutex
 */
typedef struct shared {
  list_t list;
  /**< Stores a list*/
  uint64_t thread_count;
  /**< Stores amount of threads*/
} shared_data_t;

/**
 @struct Private_data
 @brief Stores the thread_number and a pointer to the shared data
 */
typedef struct private {
  uint64_t thread_number;
  /**< Stores the particular thread number*/
  shared_data_t* shared_data;
    /**< Stores a pointer to shared data*/
  int64_t from;
  int64_t to;
} private_data_t;

void* factorize_threads(void *data);
int read_numbers(list_t *list);
int create_threads(shared_data_t *shared_data);

/**
 @brief Reads amount of thread. Calls on readnumbers and create threads.
 @return EXIT_SUCCESS if succesfull, error code if error found
 */
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
    } else {
      fprintf(stderr, "error: invalid thread count\n");
      return EXIT_FAILURE;
    }
  }

  list_t list_temp;
  list_init(&list_temp);
  read_numbers(&list_temp);
  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    shared_data->list = list_temp;
    shared_data->thread_count = thread_count;
    if (list_length(&shared_data->list) != 0) {
      create_threads(shared_data);
      list_imprimir(&shared_data->list);
      list_destroy(&shared_data->list);
    } else {
      fprintf(stderr, "Error: could not create list\n");
      error = 12;
    }
    free(shared_data);
  } else {
    fprintf(stderr, "error: could not allocate shared memory\n");
    error = 11;
  }
  return error;
}

/**
 @brief Reads numbers from file and adds the to list
 @param list_t
 @return EXIT_SUCCESS if numbers added succesfully, EXIT_FAILURE if error
 */
int read_numbers(list_t *list) {
  int error = EXIT_FAILURE;
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
  if (list) {
    error = EXIT_SUCCESS;
  }
  return error;
}

int64_t block(int64_t thread_number, shared_data_t* shared_data){
    int64_t numperblock = (int64_t) round((double)list_length(&shared_data->list)/shared_data->thread_count);
    int64_t from = thread_number*numperblock;
    if (from > list_length(&shared_data->list)) {
      from = list_length(&shared_data->list);
    }
    if (list_length(&shared_data->list) == 1 && thread_number == 1) {
      from = 1;
    }
    return from;
}

/**
 @brief Creates and joins threads 
 @param shared_data_t
 @return EXIT_SUCCESS if threads finish succesfully, EXIT_FAILURE if error
 */
int create_threads(shared_data_t* shared_data) {
  int error = EXIT_SUCCESS;
  pthread_t* threads = (pthread_t*)
    malloc(shared_data->thread_count * sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)
    calloc(shared_data->thread_count, sizeof(private_data_t));
  if (threads && private_data) {
    for (uint64_t thread_number = 0; thread_number < shared_data->thread_count
        ; ++thread_number) {
      private_data[thread_number].thread_number = thread_number;
      private_data[thread_number].shared_data = shared_data;
      private_data[thread_number].from = block(thread_number, shared_data);
      private_data[thread_number].to = block(thread_number+1, shared_data);
      error = pthread_create(&threads[thread_number], NULL, factorize_threads
        , /*arg*/ &private_data[thread_number]);
      if (error == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "Error: could not create secondary thread\n");
        error = 22;
        break;
      }
    }
    for (uint64_t thread_number = 0; thread_number < shared_data->thread_count
        ; ++thread_number) {
      pthread_join(threads[thread_number], /*value_ptr*/ NULL);
    }

    free(private_data);
    free(threads);
  } else {
    fprintf(stderr, "error: could not allocate %ld threads\n"
      , shared_data->thread_count);
    error = 21;
  }
  return error;
}

/**
 @brief Sends every number on list to factorize, mutex controls that no numbers are repeated or overwritten 
 @param void pointer data
 @return NULL
 */
void* factorize_threads(void* data) {
    private_data_t* private_data = (private_data_t*) data;
    shared_data_t* shared_data = private_data->shared_data;
    int64_t pos = private_data->thread_number;
    while (pos<list_length(&shared_data->list)) {
      node_factorizar(list_get_element(&shared_data->list,pos));
      pos = pos + shared_data->thread_count;
    }
    return NULL;
}
