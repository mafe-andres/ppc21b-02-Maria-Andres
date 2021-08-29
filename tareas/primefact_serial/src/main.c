#include <stdio.h>
#include <stdlib.h>
#include "array_int.h"

int main(int argc, char** argv){
    
    array_int_t arr;
    array_int_init(&arr);

    char* filename;
    if (argc>1){
        filename = argv[1];
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error al abrir el archivo.");
        exit(0);
    }

    char c[512];
    while (fgets(c, 512, file) != NULL){
        int64_t n = strtoll(c,NULL,10);
        array_int_append(&arr,n);
    }



//   char* filename;
//   if(argc>1){
//       filename = argv[1];
//   }

//   array_int_t arr;
//   array_int_init(&arr);

//   FILE* f = fopen(filename, "r");
//   if(f == NULL){
//       printf("Error al abrir el archivo.");
//       exit(0);
//   }
  
//   char c[512];
//   while(fgets(c, 512, f) != NULL){
//     int n = strtol(c,NULL,10);
//     agregar_elemento(&arr,n);
//   }
//   for(size_t i=0; i<arr.count; i++){
//     int num = arr.elements[i];
//     if(num>1){
//       printf("%d : ",arr.elements[i]);
//       for(int j=2; num>1; j++){
//         int contador=0;
//         while(num%j==0){
//           contador++;
//           num/=j;
//           if(num%j!=0){
//             if(contador>1){
//               if(num>1){
//                 printf("%d^%d*",j,contador);
//               }else{
//                 printf("%d^%d",j,contador);
//               }
//             }else if(num>1){
//               printf("%d*",j);
//             }else if(num==1){
//               printf("%d",j);
//             }
//           }
//         }
//       }
//       printf("\n");
//     }else if(num==1){
//       printf("1 : NA\n");
//     }else if(num<1){
//       printf("%d : Invalid number\n",num);
//     }
//   } 
}