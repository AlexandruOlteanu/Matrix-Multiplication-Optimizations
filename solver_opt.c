#include "utils.h"
#include <string.h>

#define ERROR(message) { \
        fprintf(stderr, "An Error has occured with message: %s\n", message); \
        exit(EXIT_FAILURE); \
}

double* my_solver(int N, double *A, double* B) {
    printf("OPT SOLVER\n");
    double *C = (double*)malloc(N * N * sizeof(double));
    memset(C, 0, N * N * sizeof(double));
    register double sum;
    register int i, j, k;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            sum = 0.0;
            for (k = i; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            sum = 0.0;
            for (k = j; k < N; k++) {
                sum += C[i * N + k] * A[j * N + k];
            }
            C[i * N + j] = sum;
        }
    }
    
    double *D = (double*)malloc(N * N * sizeof(double));
    for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                sum = 0.0;
                for (k = 0; k < N; k++) {
                    sum += B[k * N + i] * B[j * N + k ];
                }
                D[i * N + j] = sum;
            }
        }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * N + j] += D[i * N + j];
        }
    }

    
    free(D); // free memory allocated for D
    return C;
}