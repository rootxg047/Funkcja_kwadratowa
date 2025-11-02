// io.c
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void print_usage() {
    printf("Użycie:\n");
    printf("  quad a b c          - pojedyncze równanie\n");
    printf("  quad -f plik.txt    - plik z wieloma liniami (a b c)\n");
    printf("  quad                - tryb interaktywny\n");
}

int parse_cli_args(int argc, char *argv[],
                   char **filename, double *a, double *b, double *c, int *is_file_mode) {
    *is_file_mode = 0;
    *filename = NULL;

    if (argc == 1) {
        return 0; // tryb interaktywny
    }

    if (argc == 2 && strcmp(argv[1], "-f") == 0) {
        print_usage();
        return -1;
    }

    if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        *filename = argv[2];
        *is_file_mode = 1;
        return 0;
    }

    if (argc == 4) {
        *a = strtod(argv[1], NULL);
        *b = strtod(argv[2], NULL);
        *c = strtod(argv[3], NULL);
        return 0;
    }

    print_usage();
    return -1;
}

// Pomocnicza: pomija białe znaki i komentarze
static const char* skip_whitespace_and_comments(const char *str) {
    while (*str && (isspace(*str) || *str == '#')) {
        if (*str == '#') {
            while (*str && *str != '\n') str++;
        } else {
            str++;
        }
    }
    return str;
}

int read_line_coefficients(const char *line, double *a, double *b, double *c) {
    const char *ptr = skip_whitespace_and_comments(line);
    if (*ptr == '\0') return -1; // pusta linia lub komentarz

    char *endptr;
    *a = strtod(ptr, &endptr);
    if (ptr == endptr || isnan(*a) || isinf(*a)) return -1;

    ptr = skip_whitespace_and_comments(endptr);
    *b = strtod(ptr, &endptr);
    if (ptr == endptr || isnan(*b) || isinf(*b)) return -1;

    ptr = skip_whitespace_and_comments(endptr);
    *c = strtod(ptr, &endptr);
    if (ptr == endptr || isnan(*c) || isinf(*c)) return -1;

    // Sprawdź, czy coś zostało (np. śmieci)
    ptr = skip_whitespace_and_comments(endptr);
    if (*ptr != '\0' && *ptr != '#') return -1;

    return 0;
}

void print_result(const quad_result_t *res) {
    printf("a=%.6f, b=%.6f, c=%.6f\n", res->delta, res->vertex_p, res->vertex_q);

    if (res->type == ROOTS_REAL) {
        if (res->real1 == res->real2) {
            printf("Pierwiastek podwójny: x = %.6f\n", res->real1);
        } else {
            printf("Pierwiastki rzeczywiste: x1 = %.6f, x2 = %.6f\n", res->real1, res->real2);
        }
    } else if (res->type == ROOTS_COMPLEX) {
        printf("Pierwiastki zespolone:\n");
        printf("  x1 = %.6f + %.6fi\n", res->complex1_re, res->complex1_im);
        printf("  x2 = %.6f + %.6fi\n", res->complex2_re, res->complex2_im);
    } else {
        printf("Brak rozwiązania (a=0, b=0)\n");
    }

    printf("Wierzchołek: (%.6f, %.6f)\n", res->vertex_p, res->vertex_q);
}

void print_csv_header() {
    printf("a,b,c,delta,root1,root2,vertex_p,vertex_q,type\n");
}

void print_result_csv(const quad_result_t *res) {
    double a, b, c; // będziemy potrzebować – dodamy w main
    // Na razie placeholder – uzupełnimy później
    printf("TODO,a,b,c,%.6f,", res->delta);
    if (res->type == ROOTS_REAL) {
        printf("%.6f,%.6f,", res->real1, res->real2);
    } else {
        printf("%.6f+%.6fi,%.6f+%.6fi,", res->complex1_re, res->complex1_im, res->complex2_re, res->complex2_im);
    }
    printf("%.6f,%.6f,%s\n", res->vertex_p, res->vertex_q,
           res->type == ROOTS_REAL ? "real" : "complex");
}
