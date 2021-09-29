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
  uint64_t thread_count;
  List list;
  pthread_mutex_t mutex;
  Node node;
} shared_data_t;

// thread_private_data_t
typedef struct private {
  uint64_t thread_number;
  shared_data_t* shared_data;
} private_data_t;


void* factorizar_threads(void* data);
int read_numbers(shared_data_t* shared_data);
int create_threads(shared_data_t* shared_data);

// procedure main
int main(int argc, char* argv[]) {
  int error = 0;

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
    list_init(&list_temp);
    shared_data->list = list_temp;
    list_destroy(&list_temp);
    shared_data->thread_count = thread_count;

    error = create_threads(shared_data);
    free(shared_data);
  } else {
    fprintf(stderr, "error: could not allocate shared memory\n");
    error = 11;
  }
  return error;
}

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

void* factorizar_threads(void* data){
    private_data_t* private_data = (private_data_t*) data;
    shared_data_t* shared_data = private_data->shared_data;
    Node *ptr = shared_data->list.cabeza;
    return NULL;
}

int create_threads(shared_data_t* shared_data) {
  int error = EXIT_SUCCESS;
  // create_thread(greet)
  pthread_t* threads = (pthread_t*)
    malloc(shared_data->thread_count * sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)
    calloc(shared_data->thread_count, sizeof(private_data_t));
  if (threads && private_data) {
    // for thread_number := 0 to thread_count do
    for (uint64_t thread_number = 0; thread_number < shared_data->thread_count
        ; ++thread_number) {
      private_data[thread_number].thread_number = thread_number;
      private_data[thread_number].shared_data = shared_data;
      // create_thread(greet, thread_number)
          
      error = pthread_create(&threads[thread_number], /*attr*/ NULL, factorizar_threads
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

