#include <omp.h>
#include <stdio.h>

int main() {
    long N = 100000000;   // fixed size

    double *A = new double[N];
    double *B = new double[N];
    double *C = new double[N];

    for (long i = 0; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (long i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    double end = omp_get_wtime();

    printf("Threads: %d, Time: %f seconds\n",
           omp_get_max_threads(), end - start);

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
