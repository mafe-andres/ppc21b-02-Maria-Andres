# Factorización

Factorizar números en sus componentes primos es una tarea larga. Todo número entero positivo no primo se puede dividir en una suma de numeros primos.  Por ejemplo, el número 10 se puede representar como 2 x 5, el número 100 como 2 x 2 x 5 x 5 o como 2^2 x 5^2 usando notación de potencias. Los numeros primos no se pueden factorizar. 

Este programa usa la tecnología *pthreads* para repartir el trabajo. Cada *thread* factoriza un número de manera paralela. [Diseño.](/design/)

## Manual de Usuario

Para compilar el programa se puede usar el makefile incluído en la carpeta, basta con  correr el comando make desde el folder del proyecto.
```bash
make
```

Para correr el programa se debe usar al ejecutable en la carpeta bin e introducir uno de los archivos de prueba en la carpeta tests.
```bash
./bin/primefact_serial < tests/input000.txt
```

También se puede utilizar la opción de make para correr todos los tests:
```bash
make test
```

Adicionalmente se puede introducir la cantidad de threads con los que se desea que funcione el trabajo de la siguiente manera:
```bash
./bin/primefact_serial threadcount < tests/input000.txt
```
Donde threadcount es un número entero igual o mayor a 1. Si no se introduce ningún parametro el programa correrá con la misma cantidad de núcleos que tenga su procesador.

## Créditos
María Fernanda Andrés Monge
maria.andres@ucr.ac.cr

Lista Enlazada adaptada de (http://www1.cs.columbia.edu/~aya/W3101-01/lectures/linked-list.pdf)
