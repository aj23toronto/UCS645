#include <mpi.h>
#include <stdio.h>

#define N 8

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int A[N], B[N];
    int local_n = N / size;

    int local_A[local_n], local_B[local_n];

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            A[i] = i + 1;
            B[i] = N - i;
        }
    }

    // Scatter vectors
    MPI_Scatter(A, local_n, MPI_INT,
                local_A, local_n, MPI_INT,
                0, MPI_COMM_WORLD);

    MPI_Scatter(B, local_n, MPI_INT,
                local_B, local_n, MPI_INT,
                0, MPI_COMM_WORLD);

    // Compute partial dot product
    int local_dot = 0;
    for (int i = 0; i < local_n; i++) {
        local_dot += local_A[i] * local_B[i];
    }

    printf("Process %d partial dot = %d\n", rank, local_dot);

    // Reduce to get final result
    int global_dot;
    MPI_Reduce(&local_dot, &global_dot, 1,
               MPI_INT, MPI_SUM, 0,
               MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nFinal Dot Product = %d\n", global_dot);
        printf("Expected = 120\n");
    }

    MPI_Finalize();
    return 0;
}
