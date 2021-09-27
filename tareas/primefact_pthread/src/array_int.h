/*
 * Copyright [2021] Maria Andres
 */
#ifndef ARRAY_INT_H
#define ARRAY_INT_H
#include <stddef.h>
#include <stdint.h>

/**
 @struct array_int
 @brief Stores an array of intergers
 */
typedef struct {
  size_t capacidad;
  /**< Almacena la el tamaño del array*/
  size_t contador;
  /**< Almacena la cantidad de elementos en el array*/
  int64_t* elementos;
  /**< Almacena un array de enterps*/
} array_int_t;

void array_init(array_int_t* a);
void array_destroy(array_int_t* a);
int array_append(array_int_t*a , int64_t elm);
int array_increase_capacity(array_int_t* a);

#endif  // ARRAY_INT_H
