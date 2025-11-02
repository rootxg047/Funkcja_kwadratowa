// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "maths.h"

int main(int argc, char *argv[]) {
    char *filename = NULL;
    double a = 0, b = 0, c = 0;
    int is_file_mode = 0;

    if (parse_cli_args(argc, argv, &filename, &a, &b, &c, &is_file_mode) != 0) {
        return 1;
    }

    quad_result_t result;

    if (is_file_mode) {
        FILE *file = fopen(filename, "r");
        if (!file) {
            printf("Błąd: nie można otworzyć pliku %s\n", filename);
            return 1;
        }

        print_csv_header();
        char line[1024];
        int line_num = 0;
        while (fgets(line, sizeof(line), file)) {
            line_num++;
            if (read_line_coefficients(line, &a, &b, &c) == 0) {
                if (solve_quadratic(a, b, c, &result) == 0) {
                    // TODO: zapisz a,b,c do CSV
                    printf("%.6f,%.6f,%.6f,", a, b, c);
                    print_result_csv(&result);
                } else {
                    printf("%.6f,%.6f,%.6f,ERROR\n", a, b, c);
                }
            }
        }
        fclose(file);

    } else if (argc == 4) {
        if (solve_quadratic(a, b, c, &result) == 0) {
            print_result(&result);
        } else {
            printf("Błąd: a nie może być 0\n");
            return 1;
        }

    } else {
        // Tryb interaktywny
        printf("Wpisz a b c (lub pustą linię, by wyjść):\n");
        char line[1024];
        while (fgets(line, sizeof(line), stdin)) {
            if (line[0] == '\n') break;
            if (read_line_coefficients(line, &a, &b, &c) == 0) {
                if (solve_quadratic(a, b, c, &result) == 0) {
                    print_result(&result);
                    printf("\n");
                } else {
                    printf("Nieprawidłowe dane lub a=0\n");
                }
            } else {
                printf("Błąd parsowania linii\n");
            }
            printf("Wpisz a b c:\n");
        }
    }

    return 0;
}
