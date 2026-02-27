#include "strlib.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_string_new()
{
    string_t s = string_new();
    assert(s.length == 0);
    assert(s.data != NULL);
    assert(s.data[0] == '\0');
    string_free(&s);
    printf("test_string_new passed\n");
}

void test_string_from()
{
    string_t s = string_from("hello");
    assert(s.length == 5);
    assert(strcmp(s.data, "hello") == 0);
    string_free(&s);

    // Test empty string
    s = string_from("");
    assert(s.length == 0);
    assert(strcmp(s.data, "") == 0);
    string_free(&s);

    printf("test_string_from passed\n");
}

void test_string_append()
{
    string_t s1 = string_from("foo");
    string_t s2 = string_from("bar");

    string_append(&s1, &s2);
    assert(strcmp(s1.data, "foobar") == 0);
    assert(s1.length == 6);

    // Test appending empty string
    string_t empty = string_new();
    string_append(&s1, &empty);
    assert(strcmp(s1.data, "foobar") == 0);
    assert(s1.length == 6);

    // Test appending to itself (overlap)
    string_append(&s1, &s1);
    assert(strcmp(s1.data, "foobarfoobar") == 0);
    assert(s1.length == 12);

    string_free(&s1);
    string_free(&s2);
    string_free(&empty);

    printf("test_string_append passed\n");
}

void test_string_append_cstr()
{
    string_t s = string_from("hello");
    string_append_cstr(&s, " world");
    assert(strcmp(s.data, "hello world") == 0);
    assert(s.length == 11);

    // Test appending empty C-string
    string_append_cstr(&s, "");
    assert(strcmp(s.data, "hello world") == 0);
    assert(s.length == 11);

    // Test overlapping (pointer inside own string)
    string_append_cstr(&s, s.data + 6); // append "world"
    assert(strcmp(s.data, "hello worldworld") == 0);
    assert(s.length == 16);

    string_free(&s);
    printf("test_string_append_cstr passed\n");
}

void test_string_free()
{
    string_t s = string_from("test");
    string_free(&s);
    assert(s.data == NULL);
    assert(s.length == 0);
    assert(s.capacity == 0);
    printf("test_string_free passed\n");
}

int main()
{
    test_string_new();
    test_string_from();
    test_string_append();
    test_string_append_cstr();
    test_string_free();

    printf("All tests passed!\n");
    return 0;
}
