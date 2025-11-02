// io.h
#ifndef IO_H
#define IO_H

#include "maths.h"

void print_usage();
int parse_cli_args(int argc, char *argv[], char **filename, double *a, double *b, double *c, int *is_file_mode);
int read_line_coefficients(const char *line, double *a, double *b, double *c);
void print_result(const quad_result_t *res);
void print_csv_header();
void print_result_csv(const quad_result_t *res);

#endif
