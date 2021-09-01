#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdint.h>
#include <array_int.h>

struct node{
    int64_t num;
    array_int_t primos;
    array_int_t potencias;
    struct node *next;
};

typedef struct node Node;

struct list{
    Node *cabeza;
};

typedef struct list List;

void list_init(List*);
void list_insert_last(List*n, int64_t);
int length(List*);
void destroy(List*);
void factorizar(List*);
void imprimir(List*)

#endif  // LIST_H
