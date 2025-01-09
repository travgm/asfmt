#ifndef CONFIG_H_
#define CONFIG_H_

typedef struct user_opts {
    int instruction_sp;
    int directive_sp;
    int section_sp;
    int label_sp;
    int heading_comments_sp;
    int inline_comments_sp;
    int space_after_comma_bl;
} user_opts_t;

typedef struct {
    int instruction;
    int directive;
    int section;
    int label;
    int heading_comments;
    int inline_comments;
    int space_after_comma;
} Config;

user_opts_t read_config_values();


#endif