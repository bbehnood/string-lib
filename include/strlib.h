#ifndef STRLIB_H
#define STRLIB_H

#include <stddef.h>

typedef struct string
{
    char *data;
    size_t length;
    size_t capacity;
} string_t;

string_t string_new();
string_t string_from(char *cstr);
void string_free(string_t *str);

#endif
