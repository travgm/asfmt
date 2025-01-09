/*
 * asfmt.c - GNU as formatter
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "asfmt.h"


int create_copy_file(FILE *in_file, char *name) {
    char out_file[1024];
    snprintf(out_file, sizeof(out_file), "%s.bak", name);
    char buffer[1024];
    size_t bytes_read = 0;
    
    FILE *out = fopen(out_file, "w");
    if (!out) {
        fprintf(stderr, "Error creating a backup of %s\n", name);
        return -1;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), in_file)) > 0) {
        size_t written = fwrite(buffer, 1, bytes_read, out);
        if (written != bytes_read) {
            fprintf(stderr, "Error writing to backup file\n");
            fclose(out);
            return -1;
        }
    }

    fclose(out);
    return 0;
}

int process_file(parser_state_t *state, char *in_file) {
    FILE *file = fopen(in_file, "r");
    if (!file) {
        return -1;
    }
    if (create_copy_file(file, in_file) == -1) {
        fclose(file);
        return -1;
    }
    
    rewind(file);
    int status = 0;

    parser_state_t *res = parse_file(state, file);
    fclose(file);
    if (res->output_buffer == NULL) {
        status = -1;
        return status;
    } else {
        size_t buffer_len = strlen(res->output_buffer);
        write_output_buffer(res->output_buffer, buffer_len, in_file);
    }

    return status;
}

int main(int argc, char *argv[]) {
    struct timespec start, end;
    parser_state_t *state = init_parser();
    int success = -1;

    if (argc < 2 || argc > 2) {
        fprintf(stderr, "Usage: asfmt <file>\n");
        exit(1);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

    success = process_file(state, argv[1]);
    if (success == -1) {
        fprintf(stderr, "Error processing file\n");
        free_parser(state);
        exit(1);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Processed file in %f seconds\n", elapsed_time);

    free_parser(state);
    return 0;
}