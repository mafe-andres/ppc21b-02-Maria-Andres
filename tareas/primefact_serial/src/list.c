#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <list.h>
#include <array_int.h>
#include <math.h>

void list_init(List *l){
    l->cabeza = 0;
}

void list_insert_last(List *l, int64_t num){
    Node *ptr;
    Node *nuevo;

    nuevo = (Node *)malloc(sizeof(Node));
    nuevo->num = num;
    nuevo->next = 0;    

    if (l->cabeza == 0){
        l->cabeza = nuevo;
    }else{
        ptr = l->cabeza;
        while (ptr->next){
            ptr = ptr->next;
        }
        ptr->next = nuevo;
    }
}

int length(List *l){
    Node *ptr;
    int count = 1;
    if (l->cabeza == 0){
        count = 1;
    }
    else{
        ptr = l->cabeza;
        while(ptr->next){
            ptr = ptr->next;
            count++;
        }
    }
    return count;
}

void destroy(List *l){
    Node *ptr1; 
    Node *ptr2;
    if (l->cabeza != 0){
        ptr1 = l->cabeza;
        while (ptr1){
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            free(ptr2);
        }
    }
    l->cabeza = 0;
}

void factorizar(List *l){
    Node *ptr;
    if(l->cabeza != 0){
        ptr = l->cabeza;
        while(ptr->next){
            int64_t num = ptr->num;
            array_init(ptr->primos);
            array_init(ptr->potencias);
            if (num > 1 && num < (pow(2, 63)-1)) {
                for (int j = 2; num > 1; j++) {
                int contador = 0;
                    while (num%j == 0) {
                        contador++;
                        num /= j;
                        if (num%j != 0) {
                            if (contador > 1) {
                                array_append(ptr->primos, j);
                                array_append(ptr->potencias, contador);
                            } else if (num > 1) {
                                array_append(ptr->primos, j);
                                array_append(ptr->potencias, 1);
                            }
                        }
                    }
                }
            }
            else if((num == 1)||(num == 0)){
                ptr->num = num;
            }
            else{
                array_append(ptr->primos, -1);
                ptr->num = num;
            }
            ptr = ptr->next;
        }
    }
}

void imprimir(List *l){
    Node *ptr = l->cabeza;
    while (ptr->next){
        if ((ptr->num == 0) || (ptr->num == 1)){
            printf("%"PRId64": NA\n",ptr->num);
        }
        else if (ptr->primos->elementos[0] == -1){
            printf("Invalid Number\n");
        }
        else{
            printf("%"PRId64": ",ptr->num);
            for (int i = 0; i < ptr->primos->contador; i++){
                if (ptr->potencias->elementos[i]==1){
                    printf("%"PRId64" ",ptr->primos->elementos[i]);
                }
                else{
                    printf("%"PRId64"^",ptr->primos->elementos[i]);
                    printf("%"PRId64" ",ptr->potencias->elementos[i]);
                }
            }
        }        
        ptr = ptr->next;
    }
}
