#include <omp.h>
#include <stdio.h>

int main() {
    const int N = 100000;   // number of iterations
    double start, end;

    printf("Experiment 4: Scheduling and Load Imbalance\n\n");

    // ---------------- STATIC ----------------
    start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        // Imbalanced workload: work increases with i
        for (int j = 0; j < i; j++) {
            // dummy computation
        }
    }
    end = omp_get_wtime();
    printf("Static Scheduling Time   : %f seconds\n", end - start);

    // ---------------- DYNAMIC ----------------
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 4)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            // dummy computation
        }
    }
    end = omp_get_wtime();
    printf("Dynamic Scheduling Time  : %f seconds\n", end - start);

    // ---------------- GUIDED ----------------
    start = omp_get_wtime();
    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            // dummy computation
        }
    }
    end = omp_get_wtime();
    printf("Guided Scheduling Time   : %f seconds\n", end - start);

    return 0;
}
