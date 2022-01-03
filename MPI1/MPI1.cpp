// PRIR_project.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 



#define n 5 

int a[] = { 2, 4, 7, 6, 5 };


int a2[1000];

int main(int argc, char* argv[])
{

	int pid, np,
		elements_per_process,
		n_elements_recieved;

	MPI_Status status;


	MPI_Init(&argc, &argv);


	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	double startParallel, stopParallel;
	startParallel = MPI_Wtime();

	if (pid == 0) {
		int index, i;
		elements_per_process = n / np;


		if (np > 1) {

			for (i = 1; i < np - 1; i++) {
				index = i * elements_per_process;

				MPI_Send(&elements_per_process,
					1, MPI_INT, i, 0,
					MPI_COMM_WORLD);
				MPI_Send(&a[index],
					elements_per_process,
					MPI_INT, i, 0,
					MPI_COMM_WORLD);
			}


			index = i * elements_per_process;
			int elements_left = n - index;

			MPI_Send(&elements_left,
				1, MPI_INT,
				i, 0,
				MPI_COMM_WORLD);
			MPI_Send(&a[index],
				elements_left,
				MPI_INT, i, 0,
				MPI_COMM_WORLD);
		}


		int largest = INT_MIN;
		for (i = 0; i < elements_per_process; i++)
		{
			if (a[i] > largest) {
				largest = a[i];
			}


		}



		int tmp;
		for (i = 1; i < np; i++) {
			MPI_Recv(&tmp, 1, MPI_INT,
				MPI_ANY_SOURCE, 0,
				MPI_COMM_WORLD,
				&status);
			int sender = status.MPI_SOURCE;
			if (tmp > largest)
				largest = tmp;
		}


		printf("Largest is : %d\n", largest);
	}

	else {
		MPI_Recv(&n_elements_recieved,
			1, MPI_INT, 0, 0,
			MPI_COMM_WORLD,
			&status);


		MPI_Recv(&a2, n_elements_recieved,
			MPI_INT, 0, 0,
			MPI_COMM_WORLD,
			&status);


		int partial_largest = INT_MIN;
		for (int i = 0; i < n_elements_recieved; i++)
		{
			if (a2[i] > partial_largest) {
				partial_largest = a2[i];
			}
		}

		MPI_Send(&partial_largest, 1, MPI_INT,
			0, 0, MPI_COMM_WORLD);
	}
	stopParallel = MPI_Wtime();
	printf("Execution time = %f", stopParallel - startParallel);


	MPI_Finalize();

	return 0;
}