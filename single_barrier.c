#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	int MAX;
	
	printf("Entre com o numero maximo: ");
	scanf("%d", &MAX);
	
	long long int A[MAX], B[MAX], doubled_A[MAX], sum_A=0;;

	#pragma omp parallel
	{
		#pragma omp single
		printf("Primeira thread executada: %d\n",omp_get_thread_num());
		
		int thread_id = omp_get_thread_num();

		#pragma omp for
		for(int i = 0; i < MAX; ++i){
			int start_value = thread_id + i + 1;
			int sum = 0;

			for(int j=start_value; j<(start_value * start_value); ++j) {
				
				if (j == 1) {
					continue;
				}	
				else if(j == 2) {
					sum += j;				
				} else {
					int prime = 1;

					for(int k=3; k<j; ++k) {
						if (j%k == 0) {
							prime = 0;
						}
					}
					
					if (prime == 1) {
						sum += j;
					}
				}			
			}

			A[i] = sum;
		}

		#pragma omp barrier

		#pragma omp for reduction(+:sum_A)
		for(int i = 0; i<MAX; ++i) {
			sum_A += A[i];
		}

		#pragma omp barrier

		#pragma omp for
		for(int i =0; i<MAX; ++i) {
			int sum = 0;

			for(int j = sum_A; j < (sum_A * sum_A); ++j){		
				 sum += i + j + thread_id;
			}
			
			B[i] = sum;
		}

		#pragma omp barrier

		#pragma omp for
		for(int i = 0; i < MAX; ++i){		
			doubled_A[i] = A[i] * 2;
		}

	}
	
	printf("A: %lld\n",A[1]);
	printf("doubled_A: %lld\n",doubled_A[1]);
	printf("B: %lld\n",B[1]);
}
