#include <omp.h>
#include <stdio.h>

int main() {
    long N = 100000000;

    double *A = new double[N];
    double *B = new double[N];
    double *C = new double[N];

    for (long i = 0; i < N; i++)
        A[i] = B[i] = 1.0;

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (long i = 0; i < N; i++)
        C[i] = A[i] + B[i];

    double end = omp_get_wtime();

    printf("Time = %f seconds\n", end - start);

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
