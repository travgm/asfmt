#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <stdio.h>
#include <stdlib.h>

int write_output_buffer(char *buffer, size_t size, char *filename);
void append_output_buffer(char *buffer, size_t *size, char *string);

#endif