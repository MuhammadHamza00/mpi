#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100 // Size of vectors

void vector_multiplication(int *a, int *b, int *c, int size) {
    for (int i = 0; i < size; i++) {
        c[i] = a[i] * b[i];
    }
}

int main(int argc, char** argv) {
    int world_size, world_rank;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int local_size = N / world_size;
    int *a = (int *)malloc(local_size * sizeof(int));
    int *b = (int *)malloc(local_size * sizeof(int));
    int *c = (int *)malloc(local_size * sizeof(int));

    // Initialize vectors
    for (int i = 0; i < local_size; i++) {
        a[i] = world_rank * local_size + i;
        b[i] = world_rank * local_size + i;
    }

    // Perform vector multiplication
    vector_multiplication(a, b, c, local_size);

    // Gather results to root process
    int *result = NULL;
    if (world_rank == 0) {
        result = (int *)malloc(N * sizeof(int));
    }
    MPI_Gather(c, local_size, MPI_INT, result, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Print result at root process
    if (world_rank == 0) {
        printf("Result vector:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    // Clean up
    free(a);
    free(b);
    free(c);

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
