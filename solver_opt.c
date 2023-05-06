#include "utils.h"
#include <string.h>

#define ERROR(message) { \
        fprintf(stderr, "An Error has occured with message: %s\n", message); \
        exit(EXIT_FAILURE); \
}

#define ZERO 0
#define double_sz sizeof(double)

double* my_solver(int sz, double *a, double* b) {
    printf("OPT SOLVER\n");
    double *c = (double*)calloc(sz * sz, sizeof(double));

    if (c == NULL) {
        ERROR("Calloc failed");
    }

    register int i = ZERO, j = ZERO, k = ZERO;
    register double result = 0;
    
    for (i = 0; i < sz; ++i) {
        for (j = 0; j < sz; ++j) {
            c[j + i * sz] = ZERO;
        }
    }

    i = ZERO;
    do {
        j = ZERO;
        do {
            result = ZERO;
            k = i;
            do {
                result += a[k + i * sz] * b[j + k * sz];
                ++k;
            } while (k < sz);
            c[j + i * sz] = result;
            ++j;
        } while (j < sz);
        ++i;
    } while (i < sz);

    i = ZERO;
    do {
        j = ZERO;
        do {
            result = ZERO;
            k = ZERO;
            do {
                result += c[k + i * sz] * a[k + j * sz];
                ++k;
            } while (k < sz);
            c[j + i * sz] = result;
            ++j;
        } while (j < sz);
        ++i;
    } while (i < sz);

    double *second = calloc(sz * sz, double_sz);
    if (second == NULL) {
        ERROR("Calloc failed");
    }
    i = ZERO;
    do {
        j = ZERO;
        do {
            k = ZERO;
            result = 0;
            do {
                result += b[k * sz + i] * b[j * sz + k];
                ++k;
            } while (k < sz);
            second[j + i * sz] = result;
            ++j;
        } while (j < sz);
        ++i;
    } while (i < sz);

    i = ZERO;
    do {
        j = ZERO;
        do {
            c[j + i * sz] += second[j + i * sz];
            ++j;
        } while (j < sz);
        ++i;
    } while (i < sz);


    free(second);
    return c;
}