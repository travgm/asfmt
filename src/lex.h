#ifndef LEX_H_
#define LEX_H_

#include "tokens.h"
#include "parser.h"

#define MAX_LINE_LENGTH 2048

typedef struct token {
    tokens_table type;
    char *value;
    int spaces;
    int tabs;
} token_t;

token_t get_next_token(char *line, int *pos);

#endif