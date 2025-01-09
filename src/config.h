/*
 * config.h GNU as formatter
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