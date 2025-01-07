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

#include "lex.h"
#include "parser.h"

char peek_char(parser_state_t *state) {
    return state->current_line[state->line_pos];
}

void advance_char(parser_state_t *state) {
    state->line_pos++;
}

token_t tokenize_line(parser_state_t *state) {
    token_t token;

    if (state->current_line[state->line_no] == '\n') {
        token.type = nl;
        token.value = "\n";
        return token;
    }

    if (state->current_line[state->line_no] == ';') {
        token.type = comment;
        token.value = ";";
        return token;
    }

    return token;
}