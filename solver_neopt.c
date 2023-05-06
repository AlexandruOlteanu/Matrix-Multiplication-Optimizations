/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
    printf("NEOPT SOLVER\n");
    double *C = (double*)malloc(N * N * sizeof(double));
    memset(C, 0, N * N * sizeof(double));
    double sum;
    int i, j, k;

    // Perform matrix multiplication of A and B
    for (i = 0; i < N; i++) {
        // Loop over columns of B
        for (j = 0; j < N; j++) {
            sum = 0.0;
            // Only multiply elements above or on the diagonal of A
            for (k = i; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            // Store result in C
            C[i * N + j] = sum;
        }
    }

    // Multiply C with transpose of A
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            sum = 0.0;
            // Multiply corresponding elements of C and A transpose
            for (k = 0; k < N; k++) {
                sum += C[i * N + k] * A[j * N + k];
            }
            // Store result in C
            C[i * N + j] = sum;
        }
    }

    // Compute transpose of B
    double *Bt = (double*)malloc(N * N * sizeof(double));
    memset(Bt, 0, N * N * sizeof(double));
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            Bt[j * N + i] = B[i * N + j];
        }
    }


    // Multiply transpose of B with itself
        double *D = (double*)malloc(N * N * sizeof(double));
  //  memset(D, 0, N * N * sizeof(double));
    for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                sum = 0.0;
                // Multiply corresponding elements of transpose of B and B
                for (k = 0; k < N; k++) {
                    sum += Bt[i * N + k] * Bt[k * N + j];
                }
                // Store result in D
                D[i * N + j] = sum;
            }
        }

    // Add D to C and return the result
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * N + j] += D[i * N + j];
        }
    }

    free(Bt); // free memory allocated for Bt
    free(D); // free memory allocated for D
    return C;
}