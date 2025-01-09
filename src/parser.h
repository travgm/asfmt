/*
 * parser.h GNU as formatter
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
#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include "tokens.h"

#define MAX_OUTPUT_BUFFER_SIZE 4096

typedef struct parser_state {
    unsigned long int line_no;
    int line_pos;
    char *current_line;
    tokens_table prev_token;
    char *output_buffer;

    int prev_comment_space;
    int in_data_section;
    int in_label;
    int in_local_label;
} parser_state_t;

parser_state_t *init_parser();
void free_parser(parser_state_t *state);
parser_state_t *parse_file(parser_state_t *state, FILE *in_file);

#endif