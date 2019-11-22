#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	long long int start, end, size;
	int n_threads;

	printf("Entre com o numero de threads: ");
	scanf("%d", &n_threads);
	
	printf("Entre com o inicio e o fim separados por espaço (start end): ");
	scanf("%lld %lld", &start, &end);
	
	size = end - start;

	long long int m3[size], m7[size], m11[size], prime[size];

	for (int i = 0; i < size; ++i) { 
		m3[i] = 0;
		m7[i] = 0;
		m11[i] = 0;
		prime[i] = 0;
	}
	
	double start_time = omp_get_wtime();
	#pragma omp parallel num_threads(n_threads)
	{
		int id = omp_get_thread_num();
		int total_threads = omp_get_num_threads();
		long long int current;
		
		current = start + id;
		for (int i = id; i < size; i = i+total_threads){

			if (current % 3 == 0) {
				#pragma omp critical
				m3[i] = current;
			}
			if (current % 7 == 0) {
				#pragma omp critical
				m7[i] = current;
			}
			if (current % 11 == 0) {
				#pragma omp critical
				m11[i] = current;
			}

			if (current == 2) {
				#pragma omp critical
				prime[i] = current;
			} 
			else if (current > 2) {
				#pragma omp parallel num_threads(total_threads)
				{
					int id_nested = omp_get_thread_num();
					int total_nested = omp_get_num_threads();
					int prime_flag = 0;

					for (int i = id_nested + 2; i < current; i = i+total_nested+2) {
						if (current % i == 0) {
							++prime_flag;
						}
					}
					
					if (prime_flag == 0) {
						#pragma omp critical
						prime[i] = current;
					}
				}
			}

			current += total_threads;
		}
	
	}
	double end_time = omp_get_wtime() - start_time;

	// Save to a file
	FILE *f = fopen("resultados.txt", "w");

	if (f == NULL) {
		exit(1);	
	}

	fprintf(f, "==== Resultados com %d threads | Intervalo: %lld até %lld =====\n", n_threads, start, end);

	fprintf(f, "\n");
	fprintf(f, "Multiplos de 3:\n");
	for (int i = 0; i < size; ++i) {
		if (m3[i] != 0) fprintf(f, "%lld ", m3[i]);
	}

	fprintf(f,"\n");
	fprintf(f,"\n");
	fprintf(f,"Multiplos de 7:\n");
	for (int i = 0; i < size; ++i) {
		if (m7[i] != 0) fprintf(f,"%lld ", m7[i]);
	}

	fprintf(f,"\n");
	fprintf(f,"\n");
	fprintf(f,"Multiplos de 11:\n");
	for (int i = 0; i < size; ++i) {
		if (m11[i] != 0) fprintf(f,"%lld ", m11[i]);	
	}

	fprintf(f,"\n");
	fprintf(f,"\n");

	fprintf(f,"Primos:\n");
	for (int i = 0; i < size; ++i) {
		if (prime[i] != 0) fprintf(f,"%lld ", prime[i]);	
	}

	fprintf(f,"\n");
	fprintf(f,"\n");
	fprintf(f,"Tempo final: %lf", end_time);

	return 0;
}
