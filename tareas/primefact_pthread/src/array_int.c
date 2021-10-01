/*
 * Copyright [2021] Maria Andres
 */
#include "array_int.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

int array_increase_capacity(array_int_t* a);

/**
  @brief Initializes array
  @param array_int
 */
void array_init(array_int_t* a) {
  assert(a);
  a->capacidad = 0;
  a->contador = 0;
  a->elementos = NULL;
}

/**
  @brief Frees the array
  @param array_int
*/
void array_destroy(array_int_t* a) {
  assert(a);
  a->capacidad = 0;
  a->contador = 0;
  free(a->elementos);
}

/**
  @brief Adds element to the end of array
  @param array_int
  @param int64_t
  @return EXIT_FAILURE for fail, EXIT_SUCCESS for succes
 */
int array_append(array_int_t* a, int64_t elm) {
  assert(a);
  if (a->contador == a->capacidad) {
    if (array_increase_capacity(a) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  a->elementos[a->contador++] = elm;
  return EXIT_SUCCESS;
}

/**
  @brief Increases array capacity
  @param array_int
  @return EXIT_FAILURE for fail, EXIT_SUCCESS for success
 */
int array_increase_capacity(array_int_t* a) {
  size_t new_capacidad = a->capacidad + 1;
  int64_t* new_elementos = (int64_t*)
    realloc(a->elementos, new_capacidad * sizeof(int64_t));
  if (new_elementos) {
    a->capacidad = new_capacidad;
    a->elementos = new_elementos;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
