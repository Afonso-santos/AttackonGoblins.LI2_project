#include "../../includes/types/dynamic_string.h"
#include <string.h>

#define MIN_ALLOCATED_LENGTH 16

String *create_string(const char *data) {
    String *string = malloc(sizeof(struct _String));
    string->data = malloc(sizeof(char) * MIN_ALLOCATED_LENGTH);
    string->length = 0;
    string->allocated_length = MIN_ALLOCATED_LENGTH;

    string_append(string, data);
    return string;
}

void free_string(String *string) {
    free(string->data);
    free(string);
}

void string_append(String *string, const char *data) {
    size_t data_length = strlen(data);
    while (string->length + data_length >= string->allocated_length) {
        string->allocated_length *= 2;
        string->data = realloc(string->data, sizeof(char) * string->allocated_length);
    }
    memcpy(string->data + string->length, data, data_length);
    string->length += data_length;
}