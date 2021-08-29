#ifndef ARRAY_CHAR_H
#define ARRAY_CHAR_H

# include <stddef.h>

typedef struct{
    size_t capacity;
    size_t count;
    char* elements;
}array_char_t;

int array_char_init(array_char_t* array);
void array_char_destroy(array_char_t* array);
int array_char_append(array_char_t* array,char element);


#endif // ARRAY_CHAR_H