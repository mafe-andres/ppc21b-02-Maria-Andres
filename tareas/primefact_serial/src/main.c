/*
 * Copyright [2021] Maria Andres
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "array_int.h"
#include "list.h"

/**
 @brief Reads file, stores numbers in a list, calls factorization and print.
 @return 0
 */
int main(void) {
  List numeros;
  list_init(&numeros);
  int64_t num;
  int64_t error = -125;
  char *prueba = malloc(100);
  int final = 0;
  while (scanf("%"SCNd64, &num) == 1 || (final = scanf("%s", prueba)) == 1) {
    if (final == 1) {
      list_insert_last(&numeros, error);
      final = 0;
    } else {
      list_insert_last(&numeros, num);
    }
  }
  free(prueba);
  factorizar(&numeros);
  imprimir(&numeros);
  destroy(&numeros);
  return 0;
}
