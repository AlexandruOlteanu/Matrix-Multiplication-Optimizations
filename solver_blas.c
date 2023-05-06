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

double* my_solver(int N, double *A, double *B) {
    printf("BLAS SOLVER\n");

    // Calculate B x A
    double *BxA = calloc(N * N, sizeof(double));
    DIE(BxA == NULL, "BxA calloc error");

    // Initialize BxA = B, after multiplication, BxA = B x A
    memcpy(BxA, B, N * N * sizeof(double));

    cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, BxA, N);

    // Calculate BxA x A^T
    double *result = calloc(N * N, sizeof(double));
    DIE(result == NULL, "Result calloc error");

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1, BxA, N, A, N, 0, result, N);

    // Calculate B transpose x B
    double *BtB = calloc(N * N, sizeof(double));
    DIE(BtB == NULL, "BtB calloc error");

    cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, N, N, N, 1, B, N, B, N, 0, BtB, N);

    // Add BtB to the result
    cblas_daxpy(N * N, 1, BtB, 1, result, 1);

    // Free memory allocated for BxA and BtB
    free(BxA);
    free(BtB);

    return result;
}