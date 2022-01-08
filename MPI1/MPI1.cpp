#include <mpi.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

#define FILL_MODE_NOT_RANDOM 0
#define FILL_MODE_RANDOM 1


int initVector(double* vector, unsigned int vSize, unsigned int fillMode, unsigned int procIndex) {

    for (unsigned int i = 0; i < vSize; i++) {
        if (fillMode == FILL_MODE_RANDOM) {
            vector[i] = rand() / (double)RAND_MAX;
        }
        else {
            vector[i] = procIndex;
        }
    }
    return 0;
}


int main(int argc, char** argv) {

    MPI_Init(&argc, &argv); 

    unsigned int vSize = 2000;
    if (argc == 2) { 
        vSize = atoi(argv[1]);
    }

    unsigned int fillMode = FILL_MODE_NOT_RANDOM;
    if (argc == 3) {
        if (strcmp("-random", argv[3])) {
            fillMode = FILL_MODE_RANDOM;
        }
    }

    int procCount, procIndex; 


    MPI_Comm_size(MPI_COMM_WORLD, &procCount); 
    MPI_Comm_rank(MPI_COMM_WORLD, &procIndex); 



    double startParallel, stopParallel; 
    startParallel = MPI_Wtime();


    double* dataVector; 
    double procMax;
    double calculatedMax;
    double realMax;

    dataVector = (double*)malloc(vSize * sizeof(double));
    realMax = initVector(dataVector, vSize, fillMode, procIndex);


    if (procIndex == 0) {
        printf("Array size per process is %u\n", vSize);
    }


    procMax = dataVector[0];
    for (unsigned int i = 0; i < vSize; i++) {
        if (dataVector[i] > procMax) {
            procMax = dataVector[i];
        }
    }

    MPI_Reduce(&procMax, &calculatedMax, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (procIndex == 0) {
        if (fillMode == FILL_MODE_NOT_RANDOM) {
            if (calculatedMax == procCount - 1) {
                printf("Max parallel = %f\n", calculatedMax);
            }
            else {
                printf("No Success Calculation Maximum! You must recalculate this!");
                return 1;
            }
        }
    }


    stopParallel = MPI_Wtime();
    if (procIndex == 0) {
        printf("Execution time= %f, process count= %d, size= %u\n",
            stopParallel - startParallel,
            procCount,
            vSize
        );
    }

    MPI_Finalize();

    return 0;
}