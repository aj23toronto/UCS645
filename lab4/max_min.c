#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed random number differently for each process
    srand(time(NULL) + rank);

    int numbers[10];

    printf("\nProcess %d generated numbers: ", rank);

    for (int i = 0; i < 10; i++) {
        numbers[i] = rand() % 1001;
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Find local max and min
    int local_max = numbers[0];
    int local_min = numbers[0];

    for (int i = 1; i < 10; i++) {
        if (numbers[i] > local_max)
            local_max = numbers[i];
        if (numbers[i] < local_min)
            local_min = numbers[i];
    }

    printf("Process %d local max = %d, local min = %d\n",
           rank, local_max, local_min);

    // Structure for MAXLOC and MINLOC
    struct {
        int value;
        int rank;
    } local_maxloc, global_maxloc, local_minloc, global_minloc;

    local_maxloc.value = local_max;
    local_maxloc.rank = rank;

    local_minloc.value = local_min;
    local_minloc.rank = rank;

    // Find global max and which process had it
    MPI_Reduce(&local_maxloc, &global_maxloc, 1,
               MPI_2INT, MPI_MAXLOC, 0, MPI_COMM_WORLD);

    // Find global min and which process had it
    MPI_Reduce(&local_minloc, &global_minloc, 1,
               MPI_2INT, MPI_MINLOC, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nGlobal Maximum = %d (from Process %d)\n",
               global_maxloc.value, global_maxloc.rank);

        printf("Global Minimum = %d (from Process %d)\n",
               global_minloc.value, global_minloc.rank);
    }

    MPI_Finalize();
    return 0;
}
