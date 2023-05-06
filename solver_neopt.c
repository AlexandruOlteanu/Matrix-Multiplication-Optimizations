#include "utils.h"
#include <string.h>

#define ERROR(message) { \
        fprintf(stderr, "An Error has occured with message: %s\n", message); \
        exit(EXIT_FAILURE); \
}

#define ZERO 0
#define double_sz sizeof(double)


double* my_solver(int sz, double *a, double* b) {
    printf("NEOPT SOLVER\n");
    double *c = (double*)calloc(sz * sz, sizeof(double));

    if (c == NULL) {
        ERROR("Calloc failed");
    }
    
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            c[j + i * sz] = ZERO;
        }
    }

    int i = ZERO, j = ZERO, k = ZERO;
    do {
        j = ZERO;
        do {
            c[j + i * sz] = ZERO;
            k = i;
            do {
                c[j + i * sz] += a[k + i * sz] * b[j + k * sz];
                ++k;
            } while (k < sz);
            ++j;
        } while (j < sz);
        ++i;
    } while (i < sz);

    double result = ZERO;
    i = ZERO;
    do {
        j = ZERO;
        do {
            result = 0;
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

    double *b_transpose = (double *) calloc(sz * sz, double_sz);
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            b_transpose[j + i * sz] = ZERO;
        }
    }

    i = ZERO;
    do {
        j = ZERO;
        do {
            b_transpose[j * sz + i] = b[i * sz + j];
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
        second[j + i * sz] = ZERO;
        do {
            k = ZERO;
            do {
                second[j + i * sz] += b_transpose[k + i * sz] * b_transpose[j + k * sz];
                ++k;
            } while (k < sz);
            c[j + i * sz] += second[j + i * sz];
            ++j;
        } while (j < sz);
        ++i;
    } while (i < sz);

    free(b_transpose);
    free(second);
    return c;
}