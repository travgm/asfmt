/*
 * parser.c GNU as formatter
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

#include "parser.h"
#include "lex.h"

parser_state_t *init_parser() {
    parser_state_t *state = malloc(sizeof(parser_state_t));
    if (!state) {
        fprintf(stderr, "Error allocating memory for parser state\n");
        exit(1);
    }

    state->lines = 0;
    state->line_no = 0;
    state->current_token = 0;
    state->in_data_section = 0;
    state->in_label = 0;
    state->in_local_label = 0;

    return state;
}

void free_parser(parser_state_t *state) {
    free(state);
}

int parse_file(parser_state_t *state, FILE *in_file) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&state->current_line, &len, in_file)) != -1) {
        token_t *token = get_next_token(state);
    }

    return 0;
}