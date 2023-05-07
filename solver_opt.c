#include "utils.h"
#include <string.h>

#define ERROR(message) { \
        fprintf(stderr, "an Error has occured with message: %s\n", message); \
        exit(EXIT_FaILURE); \
}

#define double_size sizeof(double)

double* my_solver(int sz, double *a, double* b) {
    printf("OPT SOLVER\n");
    double *c = (double*)malloc(sz * sz * double_size);
    register double sum;
    register int i, j, k;

    for (i = 0; i < sz; i++) {
        for (j = 0; j < sz; j++) {
            sum = 0.0;
            for (k = i; k < sz; k++) {
                sum += a[i * sz + k] * b[k * sz + j];
            }
            c[i * sz + j] = sum;
        }
    }

    for (i = 0; i < sz; i++) {
        for (j = 0; j < sz; j++) {
            sum = 0;
            for (k = j; k < sz; k++) {
                sum += c[i * sz + k] * a[j * sz + k];
            }
            c[i * sz + j] = sum;
        }
    }
    
    double *d = (double*)malloc(sz * sz * sizeof(double));
    for (i = 0; i < sz; i++) {
            for (j = 0; j < sz; j++) {
                sum = 0.0;
                for (k = 0; k < sz; k++) {
                    sum += b[k * sz + i] * b[j * sz + k ];
                }
                d[i * sz + j] = sum;
            }
        }

    for (i = 0; i < sz; i++) {
        for (j = 0; j < sz; j++) {
            c[i * sz + j] += d[i * sz + j];
        }
    }

    
    free(d);
    return c;
}