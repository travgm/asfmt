#ifndef LEX_H_
#define LEX_H_

typedef enum tokens {
    line_eof = 0,
    nl,
    comment,
    label,
    loc_label,
    directive,
    pre_proc,
    comma
} tokens_table;

typedef struct token {
    tokens_table type;
    char *value;
} token_t;

#endif