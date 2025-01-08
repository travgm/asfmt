#include <string.h>
#include "output.h"

int write_output_buffer(char *buffer, size_t size, char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return -1;
    }
    fwrite(buffer, 1, size, file);
    fclose(file);
    return 0;
}

void append_output_buffer(char *buffer, size_t *size, char *string) {
    if (!buffer) {
        return;
    }
    size_t new_size = *size + strlen(string);
    buffer = realloc(buffer, new_size + 1);
    if (!buffer) {
        return;
    }
    strcat(buffer, string);
    *size = new_size;
}