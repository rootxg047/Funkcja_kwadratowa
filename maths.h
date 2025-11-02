// maths.h
#ifndef MATHS_H
#define MATHS_H

#include <complex.h>

// Typ wyniku: rzeczywisty czy zespolony
typedef enum {
    ROOTS_REAL,
    ROOTS_COMPLEX,
    ROOTS_NONE  // np. a=0 i b=0
} root_type_t;

// Struktura na wynik (żeby zwrócić wszystko naraz)
typedef struct {
    root_type_t type;
    double real1, real2;           // dla rzeczywistych
    double complex1_re, complex1_im; // dla zespolonych (pierwszy)
    double complex2_re, complex2_im; // dla zespolonych (drugi)
    double delta;
    double vertex_p, vertex_q;
} quad_result_t;

// Funkcje
double delta(double a, double b, double c);

int roots_real(double a, double b, double c, double *x1, double *x2);
int roots_complex(double a, double b, double c, double *re1, double *im1, double *re2, double *im2);

int vertex(double a, double b, double c, double *p, double *q);

int solve_quadratic(double a, double b, double c, quad_result_t *result);

#endif
