#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


long num_steps = 0;
double step;

int main() {
	
	double pi, sum, x=0;
	int num_threads;
	
	printf("Num_steps: "); scanf("%ld", &num_steps);
	printf("Num_threads: "); scanf("%d", &num_threads);

	omp_set_num_threads(num_threads);

	step = 	1.0 / (double)num_steps;
	
	double start_time = omp_get_wtime();

	#pragma omp parallel for reduction(+:sum) 
	for (int i =0; i<num_steps; ++i) {
		x = (i+0.5)*step;
		sum += 4.0/(1.0 + x*x);
	}

	double end_time = omp_get_wtime() - start_time;

	pi = sum * step;
	printf("pi = %f\n", pi);
	printf("tempo = %f\n", end_time);

	
}
