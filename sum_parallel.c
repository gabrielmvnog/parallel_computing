#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	long long int size;
	int n_threads;

	printf("Entre com o numero de threads: ");
	scanf("%d", &n_threads);
	
	printf("Entre com um tamanho para o Array: ");
	scanf("%lld", &size);

	long long int arr[size];
	long int POT_THREE = 10000, POT_SIX = 10000000;
	
	for (int i=0; i<size; ++i) {
		arr[i] = 0;
	}

	double start_time = omp_get_wtime();

	#pragma omp parallel num_threads(n_threads)
	{
		int id = omp_get_thread_num();
		int total_threads = omp_get_num_threads();
		
		for (int i=id; i<size; i += total_threads) {

			#pragma omp parallel num_threads(4)
			{
				int id_threads = omp_get_thread_num();
				int nested_threads = omp_get_num_threads();

				for (int j = (i+1) * POT_THREE; j <= (i+1) * POT_SIX; j += nested_threads) {

					#pragma omp atomic					
					arr[i] += j;

				}
			}
		}
	}

	double end_time = omp_get_wtime() - start_time;
	
	printf("\n");
	printf("==== Resultados =====\n");

	printf("\n");
	for (int i=0; i<size; ++i) {
		printf("%lld\t", arr[i]);
	}

	printf("\n");
	printf("\n");
	printf("Tempo final: %lf", end_time);

	printf("\n");

	return 0;
}
