#include "strlib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

static void ensure_capacity(string_t *str, const size_t needed_capacity)
{
    if (str->capacity >= needed_capacity) return;

    size_t new_capacity = str->capacity;

    while (new_capacity < needed_capacity)
    {
        new_capacity *= 2;
    }

    char *temp = realloc(str->data, new_capacity);
    if (!temp)
    {
        fprintf(stderr, "Out of memory!\n");
        free(str->data);
        str->data = NULL;
        exit(EXIT_FAILURE);
    }

    str->data = temp;
    str->capacity = new_capacity;
}

string_t string_new()
{
    string_t str;

    str.length = 0;
    str.capacity = INITIAL_CAPACITY;
    str.data = malloc(INITIAL_CAPACITY);
    if (!str.data)
    {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    str.data[0] = '\0';
    return str;
}

string_t string_from(const char *cstr)
{
    if (!cstr)
    {
        fprintf(stderr, "NULL pointer passed to string_from!\n");
        exit(EXIT_FAILURE);
    }

    string_t str;

    str.length = strlen(cstr);
    str.capacity = (str.length + 1 >= INITIAL_CAPACITY) ? str.length + 1
                                                        : INITIAL_CAPACITY;

    str.data = malloc(str.capacity);
    if (!str.data)
    {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    memcpy(str.data, cstr, str.length + 1);
    return str;
}

void string_free(string_t *str)
{
    str->length = 0;
    str->capacity = 0;
    free(str->data);
    str->data = NULL;
}

void string_append(string_t *str, const string_t *suffix)
{
    if (!str || !suffix)
    {
        fprintf(stderr, "NULL pointer passed to string_append\n");
        exit(EXIT_FAILURE);
    }

    size_t len = str->length + suffix->length;
    ensure_capacity(str, len + 1);

    memmove(str->data + str->length, suffix->data, suffix->length + 1);
    str->length += suffix->length;
}

void string_append_cstr(string_t *str, const char *suffix)
{
    if (!str || !suffix)
    {
        fprintf(stderr, "NULL pointer passed to string_append_cstr\n");
        exit(EXIT_FAILURE);
    }

    size_t suffix_length = strlen(suffix);
    size_t new_length = str->length + suffix_length;
    ensure_capacity(str, new_length + 1);

    memmove(str->data + str->length, suffix, suffix_length + 1);
    str->length += suffix_length;
}
