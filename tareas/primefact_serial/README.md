# Factorización Serial

Factorizar números en sus componentes primos es una tarea larga. Todo número entero positivo no primo se puede dividir en una suma de numeros primos.  Por ejemplo, el número 10 se puede representar como 2 x 5, el número 100 como 2 x 2 x 5 x 5 o como 2^2 x 5^2 usando notación de potencias. Los numeros primos no se pueden factorizar.

## Manual de Usuario

Para compilar el programa se puede usar el makefile incluído en la carpeta, basta con  correr el comando make desde el folder del proyecto.

```bash
make
```
Para correr el programa se debe usar al ejecutable en la carpeta bin e introducir uno de los archivos de prueba en la carpeta tests.
```bash
./bin/primefact_serial < tests/input000.txt
```
## Créditos
María Fernanda Andrés Monge
maria.andres@ucr.ac.cr

Lista Enlazada adaptada de (http://www1.cs.columbia.edu/~aya/W3101-01/lectures/linked-list.pdf)
