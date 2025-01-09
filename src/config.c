#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

const char *config_file = ".asfmt";

FILE *open_config() {
    FILE *file = fopen(config_file, "r");
    if (!file) {
        return NULL;
    }
    return file;
}

Config config;

void parse_line(char *line) {
    char key[50];
    int value;
    if (sscanf(line, "%39[^=]=%d", key, &value) == 2) {
        if (strcmp(key, "instruction") == 0) {
            config.instruction = value;
        } else if (strcmp(key, "directive") == 0) {
            config.directive = value;
        } else if (strcmp(key, "section") == 0) {
            config.section = value;
        } else if (strcmp(key, "label") == 0) {
            config.label = value;
        } else if (strcmp(key, "heading_comments") == 0) {
            config.heading_comments = value;
        } else if (strcmp(key, "inline_comments") == 0) {
            config.inline_comments = value;
        } else if (strcmp(key, "space_after_comma") == 0) {
            config.space_after_comma = value;
        }
    }
}

void parse_config(FILE *file) {
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        /* Ignore comments or newlines */
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }
        parse_line(line);
    }
}

user_opts_t set_config_defaults() {
    user_opts_t opts;

    opts.instruction_sp = 5;
    opts.directive_sp = 5;
    opts.section_sp = 5;
    opts.label_sp = 5;
    opts.heading_comments_sp = 5;
    opts.inline_comments_sp = 5;
    opts.space_after_comma_bl = 1;

    return opts;
}

user_opts_t read_config_values() {
    FILE *file = open_config();
    if (!file) {
        return set_config_defaults();
    }
    parse_config(file);
    fclose(file);

    user_opts_t opts;

    opts.instruction_sp = config.instruction;
    opts.directive_sp = config.directive;
    opts.section_sp = config.section;
    opts.label_sp = config.label;
    opts.heading_comments_sp = config.heading_comments;
    opts.inline_comments_sp = config.inline_comments;
    opts.space_after_comma_bl = config.space_after_comma;


    return opts;
}



