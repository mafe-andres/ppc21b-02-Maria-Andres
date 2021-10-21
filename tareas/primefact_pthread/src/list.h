/*
 * Copyright [2021] Maria Andres
 */
#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdint.h>
#include <array_int.h>

/**
 @struct node
 @brief stores interger and corresponding factorizations
 */
typedef struct node {
    int64_t num;
    /**< Almacena el entero*/
    array_int_t *primos;
    /**< Almacena las bases de la factorizacion*/
    array_int_t *potencias;
    /**< Almacena las potencias de la factorizacion*/
    struct node *next;
    /**< Almacena el siguiente nodo*/
} node_t;

/**
 @struct list
 @brief stores a single node, the head of the list
 */
typedef struct list {
    node_t *cabeza;
} list_t;


void list_init(list_t* lista);
void list_destroy(list_t* lista);
int list_length(list_t* lista);
void list_insert_last(list_t*lista, int64_t num);
void list_factorizar(list_t*lista);
node_t list_getelement(list_t*lista, int64_t num);
void node_factorizar(node_t *ptr);
void list_imprimir(list_t* lista);

#endif  // LIST_H
