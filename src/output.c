/*
 * output.c GNU as formatter
 *
 * Copyright (C) 2024 Travis Montoya
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
 */
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

void append_output_buffer(char **buffer, size_t *size, char *string) {
    if (!buffer || !*buffer) {
        return;
    }
    
    size_t new_size = *size + strlen(string);
    char *new_buffer = realloc(*buffer, new_size + 1);
    if (!new_buffer) {
        return;
    }
    
    *buffer = new_buffer;
    strcpy(*buffer + *size, string); 
    *size = new_size;
    (*buffer)[new_size] = '\0'; 
}

void append_nl(char **buffer) {
    if (!buffer || !*buffer) {
        return;
    }
    size_t size = strlen(*buffer);
    append_output_buffer(buffer, &size, "\n");
}

void append_spaces(char **buffer, int num_spaces) {
    if (!buffer || !*buffer) {
        return;
    }
    size_t size = strlen(*buffer);
    char spaces[num_spaces + 1];
    memset(spaces, ' ', num_spaces);
    spaces[num_spaces] = '\0';
    append_output_buffer(buffer, &size, spaces);
}