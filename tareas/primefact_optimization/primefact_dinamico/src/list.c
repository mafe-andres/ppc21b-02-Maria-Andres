/*
 * Copyright [2021] Maria Andres
 */

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <array_int.h>
#include "list.h"

// Lista adaptada de <http://www1.cs.columbia.edu/~aya/W3101-01/lectures/linked-list.pdf>

/**
 @brief Initializes list
 @param list_t
 */
void list_init(list_t *l) {
    l->cabeza = 0;
}

/**
 @brief Inserts node at the end of the list. Runs through entire list and inserts node at the end of it
 @param list_t
 @param int64_t
 */
void list_insert_last(list_t *lista, int64_t num) {
    node_t *ptr;
    node_t *nuevo;
    nuevo = (node_t *)malloc(sizeof(node_t));
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
 @brief Frees all nodes and arrays inside nodes.
 @param list_t
 */
void list_destroy(list_t *lista) {
    node_t *ptr1;
    node_t *ptr2;
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
 @brief Counts nodes in list
 @param list_t
 @return int
 */
int list_length(list_t *lista) {
    node_t *ptr;
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
 @brief Factorizes every number in the list.
        Runs through list, if n is not factorizable stores -1. If n
        is factorizable checks if it is prime or not, if prime stores itself
        if not calculates list of prime numbers and corresponding exponents.
 @param list_t
 */
void list_factorizar(list_t *l) {
    node_t *ptr = l->cabeza;
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
                            if (contador > 1) {
                                array_append(ptr->primos, j);
                                array_append(ptr->potencias, contador);
                            } else {
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
 @brief Recieves a pointer to a node and get number. if n is not factorizable stores -1. 
        If n is factorizable checks if it is prime or not, if prime stores itself
        if not calculates list of prime numbers and corresponding exponents.
 @param list_t
 */
void node_factorizar(node_t *ptr) {
    int64_t num = ptr->num;
    if (num > 1 && num < (pow(2, 63)-1)) {
        int64_t base = 2;
        do {
            int64_t contador = 0;
            while ((num%base) == 0) {
                contador++;
                num /= base;
                if ((num%base) != 0) {
                    if (contador > 1) {
                        array_append(ptr->primos, base);
                        array_append(ptr->potencias, contador);
                    } else if (num >= 1) {
                        array_append(ptr->primos, base);
                        array_append(ptr->potencias, 1);
                    }
                }
            }
            if (base == 2) {
                base = 1;
            }
            base = base+2;
            } while (num >1);
    } else {
        if (((num < 1) || (num == 1) || (num == 0)) && (num != -1)) {
            array_append(ptr->primos, -2);
            array_append(ptr->potencias, -2);
        } else {
            array_append(ptr->primos, -1);
            array_append(ptr->potencias, -1);
        }
    }
}

/**
 @brief Prints in console all numbers and respective factorizations.
        Runs through the list, if it finds a negative number prints "invalid number",
        else, prints primes and exponents.
 @param list_t
 */
void list_imprimir(list_t *l) {
    node_t *ptr = l->cabeza;
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
