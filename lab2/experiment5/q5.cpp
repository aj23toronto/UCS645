#include <omp.h>
#include <stdio.h>

int main() {
    const long N = 100000000;
    double start, end;
    double sum;

    printf("Experiment 5: Synchronization Overhead\n\n");

    // ---------------- CRITICAL ----------------
    sum = 0.0;
    start = omp_get_wtime();

    #pragma omp parallel for
    for (long i = 0; i < N; i++) {
        #pragma omp critical
        sum += 1.0;
    }

    end = omp_get_wtime();
    printf("Critical Section Time : %f seconds\n", end - start);

    // ---------------- ATOMIC ----------------
    sum = 0.0;
    start = omp_get_wtime();

    #pragma omp parallel for
    for (long i = 0; i < N; i++) {
        #pragma omp atomic
        sum += 1.0;
    }

    end = omp_get_wtime();
    printf("Atomic Operation Time : %f seconds\n", end - start);

    // ---------------- REDUCTION ----------------
    sum = 0.0;
    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < N; i++) {
        sum += 1.0;
    }

    end = omp_get_wtime();
    printf("Reduction Time        : %f seconds\n", end - start);

    return 0;
}
