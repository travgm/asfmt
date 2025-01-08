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
#include <ctype.h>

#include "lex.h"

char peek_char(parser_state_t *state) {
    return state->current_line[state->line_pos];
}

void advance_char(parser_state_t *state) {
    state->line_pos++;
}

char *trim_whitespaces(const char *line) {
    // Find the first non-whitespace character
    const char *start = line;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    // Find the last non-whitespace character
    const char *end = line + strlen(line) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    // Calculate the length of the trimmed string
    size_t trimmed_length = end - start + 1;

    // Allocate memory for the new trimmed string
    char *trimmed_line = malloc(trimmed_length + 1);
    if (!trimmed_line) {
        return NULL;
    }

    // Copy the trimmed content to the new string
    strncpy(trimmed_line, start, trimmed_length);
    trimmed_line[trimmed_length] = '\0';

    return trimmed_line;
}

token_t get_next_token(char *line, int *pos) {
    token_t token = {0};
    char *word = malloc(MAX_LINE_LENGTH);
    if (!word) {
        token.type = tok_error;
        return token;
    }

    while (isspace(line[*pos]) || line[*pos] == '\t') {
        if (line[*pos] == ' ') token.spaces++;
        if (line[*pos] == '\t') token.tabs++;
        (*pos)++;
    }

    int word_pos = 0;
    while (!isspace(line[*pos]) && line[*pos] != '\0') {
        word[word_pos++] = line[*pos];
        (*pos)++;
    }
    word[word_pos] = '\0';

    /* Determine line type */
    if (word[0] == '.' && word[word_pos-1] != ':') {
        token.type = directive;
        token.value = trim_whitespaces(line);
    }
    else if (word[0] == '.' && word[word_pos-1] == ':') {
        token.type = loc_label;
        token.value = trim_whitespaces(line);
    }
    else if (word[word_pos-1] == ':') {
        token.type = label;
        token.value = trim_whitespaces(line);
    }
    else if (word[0] == '#') {
        token.type = comment;
        token.value = trim_whitespaces(line);
    }
    else if (strcmp(trim_whitespaces(line), "") == 0) {
        token.type = empty_line;
        token.value = "";
    } 
    else {
        token.type = instruction;
        token.value = trim_whitespaces(line);
    }

    free(word);
    return token;
}
