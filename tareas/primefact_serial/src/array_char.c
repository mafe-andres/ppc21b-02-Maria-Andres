#include "array_char.h"
#include<assert.h>
#include<stdlib.h>

int array_char_increase_capacity(array_char_t* array);

int array_char_init(array_char_t* array){
    assert(array);
    array->capacity = 0;
    array->count = 0;
    return EXIT_SUCCESS;
}

void array_char_destroy(array_char_t* array){
  assert(array);
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}
int array_char_append(array_char_t* array,char element){
  assert(array);
  if(array->count == array->capacity){
    if(array_char_increase_capacity(array) != EXIT_SUCCESS){
      return EXIT_FAILURE;  
    }  
  }
  array->elements[array->count++]=element;
  return EXIT_SUCCESS;
}

int array_char_increase_capacity(array_char_t* array){
  size_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  char* new_elements = (char*) 
    realloc(array->elements, new_capacity * sizeof(char));  
  if(new_elements){
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  }else{
    return EXIT_FAILURE;
  }
}