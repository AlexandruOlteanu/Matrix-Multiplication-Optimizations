#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cblas.h>

#define ERROR(message) { \
        fprintf(stderr, "An Error has occured with message: %s\n", message); \
        exit(EXIT_FAILURE); \
}

#define double_sz sizeof(double)

double* my_solver(int sz, double *a, double *b) {
    printf("BLAS SOLVER\n");

    double *result = (double *) malloc(sz * sz * double_sz);
    if (result == NULL) {
        ERROR("Malloc failed");
    }

    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            result[j + i * sz] = b[j + i * sz];
        }
    }

    cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, sz, sz, 1, a, sz, result, sz);

    long double *second_result = (long double *) malloc(sz * sz * double_sz);
    if (second_result == NULL) {
        ERROR("Malloc failed");
    }

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, sz, sz, sz, 1, result, sz, a, sz, 0, (double *) second_result, sz);

    long double *b_transpose_b = (long double *) malloc(sz * sz * double_sz);
    if (b_transpose_b == NULL) {
        ERROR("Malloc failed");
    }

    cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, sz, sz, sz, 1, b, sz, b, sz, 0, (double *)b_transpose_b, sz);

    cblas_daxpy(sz * sz, 1, (double *)b_transpose_b, 1, (double *)second_result, 1);

    free(result);
    free(b_transpose_b);

    return (double *) second_result;
}