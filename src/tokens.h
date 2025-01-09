#ifndef TOKENS_H_
#define TOKENS_H_

typedef enum tokens {
    line_eof = 0,
    nl,
    comment,
    label,
    loc_label,
    directive,
    data_directive,
    section,
    instruction,
    align,
    globl,
    empty_line,
    tok_error
} tokens_table;

#endif