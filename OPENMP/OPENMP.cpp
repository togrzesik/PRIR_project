﻿#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int a[] = { 2, 4, 7, 6, 5 };
	int mx = -1;
	int i, n = 5;
	double time = omp_get_wtime();
	double timeDiff;
#pragma omp parallel for shared(a)
	for (i = 0; i < n; i++) {
#pragma omp critical
		{
			if (a[i] > mx)
				mx = a[i];
		}
	}
	int smx = -1;
	for (i = 0; i < n; i++)
		smx = a[i] > smx ? a[i] : smx;
	printf("\nSerial max = %d\tParallel max = %d\n", smx, mx);
	timeDiff = omp_get_wtime() - time;
	printf("Time: %f", timeDiff);
	return 0;
}