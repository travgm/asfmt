/*
 * tokens.h GNU as formatter
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