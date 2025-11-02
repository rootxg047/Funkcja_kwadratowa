// maths.c
#include "maths.h"
#include <math.h>
#include <float.h>

double delta(double a, double b, double c) {
    return b * b - 4.0 * a * c;
}

int roots_real(double a, double b, double c, double *x1, double *x2) {
    double d = delta(a, b, c);
    if (d < 0) return -1;

    // Bezpieczne obliczenia – unikamy utraty cyfr
    double sqrt_d = sqrt(d);
    if (b >= 0) {
        *x1 = (-b - sqrt_d) / (2.0 * a);
        *x2 = (2.0 * c) / (-b - sqrt_d);  // alternatywny wzór
    } else {
        *x1 = (2.0 * c) / (-b + sqrt_d);
        *x2 = (-b + sqrt_d) / (2.0 * a);
    }
    return 0;
}

int roots_complex(double a, double b, double c, double *re1, double *im1, double *re2, double *im2) {
    double d = delta(a, b, c);
    if (d >= 0) return -1;

    double sqrt_abs_d = sqrt(-d);
    double denom = 2.0 * a;

    *re1 = *re2 = -b / denom;
    *im1 = sqrt_abs_d / denom;
    *im2 = -sqrt_abs_d / denom;

    return 0;
}

int vertex(double a, double b, double c, double *p, double *q) {
    if (a == 0) return -1;
    *p = -b / (2.0 * a);
    *q = delta(a, b, c) / (-4.0 * a);  // q = f(p)
    return 0;
}

int solve_quadratic(double a, double b, double c, quad_result_t *result) {
    if (a == 0) {
        result->type = ROOTS_NONE;
        return -1;
    }

    result->delta = delta(a, b, c);

    if (result->delta > 0) {
        result->type = ROOTS_REAL;
        roots_real(a, b, c, &result->real1, &result->real2);
    } else if (result->delta == 0) {
        result->type = ROOTS_REAL;
        double x = -b / (2.0 * a);
        result->real1 = result->real2 = x;
    } else {
        result->type = ROOTS_COMPLEX;
        roots_complex(a, b, c,
                      &result->complex1_re, &result->complex1_im,
                      &result->complex2_re, &result->complex2_im);
    }

    vertex(a, b, c, &result->vertex_p, &result->vertex_q);
    return 0;
}
