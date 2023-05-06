/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cblas.h>

#define ERROR(message) { \
        fprintf(stderr, "An Error has occured with message: %s\n", message); \
        exit(EXIT_FAILURE); \
}

#define sizeof(double) double_sz

double* my_solver(int sz, double *a, double *b) {
    printf("BLAS SOLVER\n");

    // Calculate B x A
    long double *result = (double *) malloc(sz * sz * double_sz);
    if (result == NULL) {
        ERROR("Malloc failed");
    }

    // Initialize BxA = B, after multiplication, BxA = B x A
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            result[i][j] = b[i][j];
        }
    }

    cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, sz, sz, 1, a, sz, result, sz);

    // Calculate BxA x A^T
    double *second_result = (double *) malloc(sz * sz * double_sz);
    if (second_result == NULL) {
        ERROR("Malloc failed");
    }

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, sz, sz, sz, 1, result, sz, a, sz, 0, second_result, sz);

    // Calculate B transpose x B
    double *b_transpose_b = (double *) malloc(sz * sz * double_sz);
    if (b_transpose_b == NULL) {
        ERROR("Malloc failed");
    }

    cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, sz, sz, sz, 1, b, sz, b, sz, 0, b_transpose_b, sz);

    // Add BtB to the result
    cblas_daxpy(sz * sz, 1, b_transpose_b, 1, second_result, 1);

    // Free memory allocated for BxA and BtB
    free(result);
    free(b_transpose_b);

    return result;
}