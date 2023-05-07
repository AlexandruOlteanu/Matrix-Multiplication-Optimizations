#include "utils.h"
#include <string.h>

#define ERROR(message) { \
        fprintf(stderr, "an Error has occured with message: %s\n", message); \
        exit(EXIT_FAILURE); \
}

#define double_size sizeof(double)

double* my_solver(int sz, double *a, double* b) {
    printf("OPT SOLVER\n");
    double *c = (double *) calloc(sz * sz, double_size);
    if (c == NULL) {
        ERROR("Calloc failed");
    }
    register int i, j, k;
    register double res;

    for (i = sz - 1; i >= 0; --i) {
        for (j = sz - 1; j >= 0; --j) {
            res = 0;
            for (k = sz - 1; k >= i; --k) {
                res +=  b[j + k * sz] * a[k + i * sz];
            }
            c[j + i * sz] = res;
        }

        for (j = 0; j < sz; ++j) {
            res = 0;
            for (k = sz - 1; k >= j; --k) {
                res += a[k + j * sz] * c[k + i * sz];
            }
            c[j + i * sz] = res;
        }

        for (j = sz - 1; j >= 0; --j) {
            res = 0;
            for (k = sz - 1; k >= 0; --k) {
                res += b[k + j * sz] * b[i + k * sz];
            }
            c[j + i * sz] += res;
        }
    }

    return c;
}