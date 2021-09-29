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
struct node {
    int64_t num;
    /**< Almacena el entero*/
    array_int_t *primos;
    /**< Almacena las bases de la factorizacion*/
    array_int_t *potencias;
    /**< Almacena las potencias de la factorizacion*/
    struct node *next;
    /**< Almacena el siguiente nodo*/
};

typedef struct node Node;

/**
 @struct list
 @brief stores a single node, the head of the list
 */
struct list {
    Node *cabeza;
};

typedef struct list List;

int list_init(List* lista);
void list_insert_last(List*lista, int64_t);
int length(List* lista);
void list_destroy(List* lista);
void factorizar(Node* ptr);
void imprimir(List* lista);

#endif  // LIST_H
