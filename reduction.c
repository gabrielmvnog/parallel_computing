#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	
	int A[MAX], sum, median;

	#pragma omp parallel for reduction(+:sum)
	for (int i=0; i<MAX; ++i) {
		sum = sum + A[i];	
	}
	
	median = sum / MAX;

	return 0;
}
