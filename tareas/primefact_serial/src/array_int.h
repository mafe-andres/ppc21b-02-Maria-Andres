#ifndef ARRAY_INT_H
#define ARRAY_INT_H

# include <stddef.h>
# include <stdint.h>
# include <array_char.h>

typedef struct{
  size_t capacity;
  size_t count;
  int64_t* elements;  
  array_char_t fact;

}array_int_t;

int array_int_init(array_int_t* array);
void array_int_destroy(array_int_t* array);
int array_int_append(array_int_t* array,int64_t element);


#endif // ARRAY_DOUBLE_H