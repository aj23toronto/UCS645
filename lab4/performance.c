#include <mpi.h>
#include <stdio.h>
#include <math.h>

#define N 200000000   // 200 million (safe for laptop)

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long chunk = N / size;
    long long start_index = rank * chunk;
    long long end_index = start_index + chunk;

    double local_sum = 0.0;

    MPI_Barrier(MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    for (long long i = start_index; i < end_index; i++) {
        local_sum += sqrt(i * 1.0);
    }

    double global_sum = 0.0;

    MPI_Reduce(&local_sum, &global_sum, 1,
               MPI_DOUBLE, MPI_SUM, 0,
               MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("\nProcesses: %d\n", size);
        printf("Execution Time: %f seconds\n", end_time - start_time);
        printf("Global Sum: %f\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}