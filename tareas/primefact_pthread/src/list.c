/*
 * Copyright [2021] Maria Andres
 */
#include "list.h"
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <array_int.h>

// Lista adaptada de <http://www1.cs.columbia.edu/~aya/W3101-01/lectures/linked-list.pdf>

/**
 @brief Initializes list
 @param List
 */
int list_init(List *l) {
    int error = EXIT_SUCCESS;
    l->cabeza = 0;
    if (l->cabeza!=0) {
        error = EXIT_FAILURE;
    }
    return error;
}

/**
 @brief Inserts node at the end of the list. Runs through entire list and inserts node at the end of it
 @param List
 @param int64_t
 */
void list_insert_last(List *lista, int64_t num) {
    Node *ptr;
    Node *nuevo;
    nuevo = (Node *)malloc(sizeof(Node));
    nuevo->num = num;
    nuevo->next = 0;
    nuevo->primos = (array_int_t *)malloc(sizeof(array_int_t));
    nuevo->potencias = (array_int_t *)malloc(sizeof(array_int_t));
    array_init(nuevo->primos);
    array_init(nuevo->potencias);
    if (lista->cabeza == 0) {
        lista->cabeza = nuevo;
    } else {
        ptr = lista->cabeza;
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = nuevo;
    }
}

/**
 @brief Counts nodes in list
 @param List
 @return int
 */
int length(List *lista) {
    Node *ptr;
    int count = 1;
    if (lista->cabeza == 0) {
        count = 1;
    } else {
        ptr = lista->cabeza;
        while (ptr->next) {
            ptr = ptr->next;
            count++;
        }
    }
    return count;
}

/**
 @brief Frees all nodes and arrays inside nodes.
 @param List
 */
void list_destroy(List *lista) {
    Node *ptr1;
    Node *ptr2;
    if (lista->cabeza != 0) {
        ptr1 = lista->cabeza;
        while (ptr1) {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            array_destroy(ptr2->potencias);
            array_destroy(ptr2->primos);
            free(ptr2->primos);
            free(ptr2->potencias);
            free(ptr2);
        }
    }
    lista->cabeza = 0;
}

/**
 @brief Factorizes every number in the list.
        Runs through list, if n is not factorizable stores -1. If n
        is factorizable checks if it is prime or not, if prime stores itself
        if not calculates list of prime numbers and corresponding exponents.
 @param List
 */
void factorizar(List *l) {
    Node *ptr = l->cabeza;
    if (l->cabeza != 0) {
        while (ptr) {
            int64_t num = ptr->num;
            if (num > 1 && num < (pow(2, 63)-1)) {
                for (int64_t j = 2; num > 1; j++) {
                int64_t contador = 0;
                    while (num%j == 0) {
                        contador++;
                        num /= j;
                        if (num%j != 0) {
                            if (contador > 1) {  // Non-prime
                                if (num > 1) {
                                    array_append(ptr->primos, j);
                                    array_append(ptr->potencias, contador);
                                } else {
                                    array_append(ptr->primos, j);
                                    array_append(ptr->potencias, contador);
                                }
                            } else {  // Prime
                                array_append(ptr->primos, j);
                                array_append(ptr->potencias, 1);
                            }
                        }
                    }
                }
            } else {
                if (((num < 1) || (num == 1) || (num == 0)) && (num != -1)) {
                    array_append(ptr->primos, -2);
                    array_append(ptr->potencias, -2);
                } else {
                    array_append(ptr->primos, -1);
                    array_append(ptr->potencias, -1);
                }
            }
            ptr = ptr->next;
        }
    }
}

/**
 @brief Prints in console all numbers and respective factorizations.
        Runs through the list, if it finds a negative number prints "invalid number",
        else, prints primes and exponents.
 @param List
 */
void imprimir(List *l) {
    Node *ptr = l->cabeza;
    while (ptr) {
        if ((ptr->num == 0) || (ptr->num == 1)) {
            printf("%"PRId64": NA", ptr->num);
        } else if (ptr->primos->elementos[0] == -1) {
            printf("invalid number");
        } else if (ptr->primos->elementos[0] == -2) {
            printf("%"PRId64": invalid number", ptr->num);
        } else {
            printf("%"PRId64": ", ptr->num);
            for (size_t i = 0; i < ptr->primos->contador; i++) {
                if (i == ptr->primos->contador-1) {
                    if (ptr->potencias->elementos[i] == 1) {
                    printf("%"PRId64"", ptr->primos->elementos[i]);
                    } else {
                        printf("%"PRId64"^", ptr->primos->elementos[i]);
                        printf("%"PRId64"", ptr->potencias->elementos[i]);
                    }
                } else {
                    if (ptr->potencias->elementos[i] == 1) {
                        printf("%"PRId64" ", ptr->primos->elementos[i]);
                    } else {
                        printf("%"PRId64"^", ptr->primos->elementos[i]);
                        printf("%"PRId64" ", ptr->potencias->elementos[i]);
                    }
                }
            }
        }
        printf("\n");
        ptr = ptr->next;
    }
}
