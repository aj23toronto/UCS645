#include <mpi.h>
#include <stdio.h>

#define N 100

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int numbers[N];
    int local_n = N / size;
    int local_array[local_n];

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            numbers[i] = i + 1;
        }
    }

    // Scatter the array
    MPI_Scatter(numbers, local_n, MPI_INT,
                local_array, local_n, MPI_INT,
                0, MPI_COMM_WORLD);

    // Compute local sum
    int local_sum = 0;
    for (int i = 0; i < local_n; i++) {
        local_sum += local_array[i];
    }

    printf("Process %d local sum = %d\n", rank, local_sum);

    // Reduce to get global sum
    int global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1,
               MPI_INT, MPI_SUM, 0,
               MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nGlobal Sum = %d\n", global_sum);
        printf("Expected = 5050\n");
        printf("Average = %.2f\n", global_sum / (float)N);
    }

    MPI_Finalize();
    return 0;
}
