/*
 * Copyright [2021] Maria Andres
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "factorize.h"

void call_factorize(int64_t *values, int start, int end) {
  for (int i = start; i < end; i++) {
      factorize(values[i-1]);
  }
}

void factorize(int64_t num) {
    if (num > 1 && num < (pow(2, 63)-1)) {
        printf("%d: ", (int)num);
        int base = 2;
        do {
            int contador = 0;
            while ((num%base) == 0) {
                contador++;
                num /= base;
                if ((num%base) != 0) {
                    if (contador > 1) {
                        printf("%d^%d ", base, contador);
                    } else if (num >= 1) {
                        printf("%d ", base);
                    }
                }
            }
            if (base == 2) {
                base = 1;
            }
            base = base+2;
            } while (num >1);
        printf("\n");
    } else {
        if (num == 0 || num == 1) {
            printf("%d: NA\n", (int)num);
        } else if (num < 0) {
            printf("%d: invalid number\n", (int)num);
        } else {
            printf("invalid number\n");
        }
    }
}
