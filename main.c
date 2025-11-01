#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "maths.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Witaj! To narzędzie quad. Wpisz współczynniki: a b c\n");
    } else if (argc == 4) {
        // Parsujemy argumenty na double (na razie proste, bez błędów)
        double a = atof(argv[1]);  // atof konwertuje string na double
        double b = atof(argv[2]);
        double c = atof(argv[3]);
        
        double d = delta(a, b, c);  // Używamy funkcji z maths
        printf("Delta: %f\n", d);
    } else {
        print_usage();  // Używamy funkcji z io
        return 1;
    }
    return 0;
}
