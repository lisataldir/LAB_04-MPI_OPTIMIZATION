#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

	if (argc < 2){
		printf("Usage: %s [size]\n", argv[0]);
		return 1;
	}

	double t0, t1;
	int rank;
	unsigned long size = (unsigned long)atoi(argv[1]);
	char buffer[size];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0){
		MPI_Barrier(MPI_COMM_WORLD);
		t0 = MPI_Wtime();
		MPI_Send(buffer, size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(buffer, size, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		t1 = MPI_Wtime();
		printf("%g\n", t1 - t0);
	} else if (rank == 1) {
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Recv(buffer, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Send(buffer, size, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
	}
	MPI_Finalize();

	return 0;
}
