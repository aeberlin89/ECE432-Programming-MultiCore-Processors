#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
	int my_rank, comm_sz;
	double runTime, maxTime, start, finish;
	double n = 12.5;
	double* m;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	int number = atoi(argv[1]);

	/***************** PART A *****************/

	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();
	
	for (int x = 0; x < number; x++) {
		if (my_rank == 0) {
			MPI_Send(&n, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
		}
		else {
			MPI_Recv(&n, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	finish = MPI_Wtime();
	runTime = finish - start;
	MPI_Reduce(&runTime, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	double partA = maxTime;

	if (my_rank == 0) {
		printf("\n*****PART A*****\n");
		printf("For %d messages containing one double number:\n", number);
		printf("Max Time = %e seconds.\n", maxTime);
	}

	/***************** PART B *****************/

	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();

	m = malloc(number*sizeof(double));

	for (int i = 0; i < number; i++)
		m[i] = i;

	if (my_rank == 0) {
		MPI_Send(m, number, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
	}
	else {
		MPI_Recv(m, number, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	finish = MPI_Wtime();
	runTime = finish - start;
	MPI_Reduce(&runTime, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	double partB = maxTime;
	
	if (my_rank == 0) {
		printf("\n*****PART B*****\n");
		printf("For one message containing %d double numbers:\n", number);
		printf("Max Time = %e seconds.\n", maxTime);
	}

	/***************** PART C *****************/
	
	double partC = 1 / (partB/partA);
	if (my_rank == 0) {
		printf("\n*****PART C*****\n");
		printf("Part B is %lf times faster than Part A.\n\n", partC);
	}
	
	MPI_Finalize();
	return 0;
}
