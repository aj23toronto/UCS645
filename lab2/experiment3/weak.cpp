#include <omp.h>
#include <stdio.h>

int main() {
    long base = 25000000;   // work per thread
    int threads = omp_get_max_threads();
    long N = base * threads;

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

    printf("Threads: %d, N: %ld, Time: %f seconds\n",
           threads, N, end - start);

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
