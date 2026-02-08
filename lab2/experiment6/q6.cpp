#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 8
#define ITERATIONS 100000000
#define CACHE_LINE 64   // bytes

int main() {
    omp_set_num_threads(NUM_THREADS);

    double start, end;

    // ---------------- FALSE SHARING VERSION ----------------
    static int partial_sum[NUM_THREADS];   // shared cache line

    start = omp_get_wtime();

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        for (int i = 0; i < ITERATIONS; i++) {
            partial_sum[tid]++;   // false sharing
        }
    }

    end = omp_get_wtime();
    printf("Unpadded (False Sharing) Time : %f seconds\n", end - start);

    // ---------------- PADDED VERSION ----------------
    static int padded_sum[NUM_THREADS][CACHE_LINE / sizeof(int)];

    start = omp_get_wtime();

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        for (int i = 0; i < ITERATIONS; i++) {
            padded_sum[tid][0]++;   // no false sharing
        }
    }

    end = omp_get_wtime();
    printf("Padded (No False Sharing) Time: %f seconds\n", end - start);

    return 0;
}
