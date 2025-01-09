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