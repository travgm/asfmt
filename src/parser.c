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
#include "output.h"

parser_state_t *init_parser() {
    parser_state_t *state = malloc(sizeof(parser_state_t));
    if (!state) {
        fprintf(stderr, "Error allocating memory for parser state\n");
        exit(1);
    }

    state->line_pos = 0;
    state->line_no = 0;
    state->prev_token = empty_line;
    state->prev_comment_space = 0;
    state->in_data_section = 0;
    state->in_label = 0;
    state->in_local_label = 0;

    state->output_buffer = malloc(MAX_OUTPUT_BUFFER_SIZE);
    state->output_buffer[0] = '\0';

    return state;
}

void free_parser(parser_state_t *state) {
    free(state);
}

void process_token(parser_state_t *state, token_t token, int *pos) {
    size_t buffer_len = strlen(state->output_buffer);
    switch (token.type) {
        case label:
            append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            state->in_label = 1;
            break;
        case loc_label:
            append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            break;
        case directive:
            append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            break;
        case data_directive:
            if (state->prev_token == label || state->prev_token == data_directive || state->prev_token == comment) {
                append_spaces(&state->output_buffer, 5);
                buffer_len = strlen(state->output_buffer);
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            } else {
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            }
            break;
        case align:
            if (state->prev_token == section) {
                append_spaces(&state->output_buffer, 5);
                buffer_len = strlen(state->output_buffer);
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            } else {
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            }
            break;
        case section:
            append_spaces(&state->output_buffer, 5);
            buffer_len = strlen(state->output_buffer);
            append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            break;
        case instruction:
            append_spaces(&state->output_buffer, 5);
            buffer_len = strlen(state->output_buffer);
            append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            break;
        case comment:
            // Need next token to determine if its a label
            token_t next_token = get_next_token(state->current_line, pos);
            if (state->prev_token == empty_line) {
                state->in_label = 0;
                state->prev_comment_space = 0;
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            }
            else if (next_token.type == label) {
                state->in_label = 0;
                state->prev_comment_space = 0;
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);
                process_token(state, next_token, pos);
            }
            else if (state->prev_token == label || state->prev_token == loc_label || 
                state->prev_token == instruction) {
                append_spaces(&state->output_buffer, 5);
                buffer_len = strlen(state->output_buffer);
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);

                state->prev_comment_space = 5;
            } 
            else if (state->prev_token == comment) {
                append_spaces(&state->output_buffer, state->prev_comment_space);
                buffer_len = strlen(state->output_buffer);
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            }
            else if (next_token.type == instruction) {
                append_spaces(&state->output_buffer, 5);
                buffer_len = strlen(state->output_buffer);
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            }
            else {
                state->prev_comment_space = 0;
                append_output_buffer(&state->output_buffer, &buffer_len, token.value);
            }
            state->prev_token = next_token.type;
            break;
        case empty_line:
            //append_nl(&state->output_buffer);
            break;
        case tok_error:
            printf("error parsing line: %s\n", token.value);
            break;
        default:
            break;
    }
    append_nl(&state->output_buffer);
}

parser_state_t *parse_file(parser_state_t *state, FILE *in_file) {
    state->current_line = NULL; 
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&state->current_line, &len, in_file)) != -1) {
        int pos = 0;
        token_t token = get_next_token(state->current_line, &pos);
        process_token(state, token, &pos);
        state->prev_token = token.type;

        if (token.type != label && token.type != directive) {
            while (pos < read) {
                token = get_next_token(state->current_line, &pos);
            }
        }
    }

    free(state->current_line);
    return state;
}