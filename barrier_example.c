#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {
	
	#pragma omp parallel shared(A,B,C) private(id)
	{
		id = omp_get_thread_num();
		A[id] = big_calc(id);
		
		#pragma omp barrier
		#pragma omp for
		for (i=0; i<n; ++i) {
			C[i] = big_calc2(i, A);
		}
		
		#pragma omp for nowait
		for (i=0; i<n; ++i) {
			B[i] = big_calc3(i, C);		
		}
		A[id] = big_calc4(id);
		
	}


	return 1
}
