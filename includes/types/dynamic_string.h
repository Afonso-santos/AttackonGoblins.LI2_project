#include <stdlib.h>

typedef struct _String {
    char *data;
    size_t length;
    size_t allocated_length;
} String;

String create_string(const char *data);
void free_string(String string);

void string_append(String string, const char *data);
