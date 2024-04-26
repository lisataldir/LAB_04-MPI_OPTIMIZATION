#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void sum(double* x, int n){
	for (int i=1; i < n-1; i++){
		x[i] = (x[i-1] + 2*x[i] + x[i+1])/4;
	}
}

int main(int argc, char** argv){

	if (argc < 3){
		printf("Usage: %s [vector size] [repetitions]\n", argv[0]);
		return 1;
	}

    int n = atoi(argv[1]);
    int rep = atoi(argv[2]);

    double t0, t1;
	int rank, p;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

    double* x = (double*)calloc(n/p + 2, sizeof(double));
	for(int i=0; i<n/p + 2; i++){
		x[i] = 1.0;
	}

	double* y = (double*)calloc(n, sizeof(double));

	for (int t=0; t < rep; t++){

		if (rank == 0){

			t0 = MPI_Wtime();

			if(rank!=p-1){
				MPI_Send(x + 1, 1, MPI_DOUBLE, p - 1, 0, MPI_COMM_WORLD);
				MPI_Send(x + n/p, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(x, 1, MPI_DOUBLE, p - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(x + n/p + 1, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}

			sum(x, n/p);

			t1 = MPI_Wtime();
			
			printf("%d %g\n", p, t1 - t0);

		} else if ((rank & 1) == 1){

			MPI_Recv(x, 1, MPI_DOUBLE, (rank-1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(x + n/p + 1, 1, MPI_DOUBLE, (rank+1)%p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(x + 1, 1, MPI_DOUBLE, (rank-1), 0, MPI_COMM_WORLD);
			MPI_Send(x + n/p, 1, MPI_DOUBLE, (rank+1)%p, 0, MPI_COMM_WORLD);

			sum(x, n/p);

		} else {

			MPI_Send(x + 1, 1, MPI_DOUBLE, (rank-1), 0, MPI_COMM_WORLD);
			MPI_Send(x + n/p, 1, MPI_DOUBLE, (rank+1)%p, 0, MPI_COMM_WORLD);
			MPI_Recv(x, 1, MPI_DOUBLE, (rank-1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(x + n/p + 1, 1, MPI_DOUBLE, (rank+1)%p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			sum(x, n/p);
		}
	}

	MPI_Gather(x+1, n/p, MPI_DOUBLE, y + rank*n/p, n/p, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// if(rank==0){
	// 	for(int i=0; i < n; i++){
	// 		printf("%f\n", y[i]);
	// 	}
	// }

	MPI_Finalize();

	return 0;
}
