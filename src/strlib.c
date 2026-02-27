#include "strlib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

string_t string_new()
{
    string_t str;

    str.length = 0;
    str.capacity = INITIAL_CAPACITY;
    str.data = malloc(INITIAL_CAPACITY);

    return str;
}

string_t string_from(char *cstr)
{
    if (!cstr)
    {
        fprintf(stderr, "NULL pointer passed to string_from!\n");
        exit(EXIT_FAILURE);
    }

    string_t str = string_new();

    size_t len = strlen(cstr);
    str.length = len;
    str.capacity = (len + 1 >= INITIAL_CAPACITY) ? len + 1 : INITIAL_CAPACITY;

    str.data = malloc(str.capacity);
    if (!str.data)
    {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }
}

void string_free(string_t *str)
{
    str->length = 0;
    str->capacity = 0;
    free(str->data);
    str->data = NULL;
}
