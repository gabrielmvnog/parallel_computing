#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	long long int start, end, size, current;

	printf("Entre com o intervalo separado por espaço (start end): ");
	scanf("%lld %lld", &start, &end);

	size = end - start;
	
	long long int m3[size], m7[size], m11[size], prime[size];
	

	for (int i = 0; i < size; ++i) { 
		m3[i] = 0;
		m7[i] = 0;
		m11[i] = 0;
		prime[i] = 0;
	}
	
	time_t time_begin = time(NULL);
	
	current = start;
	for (int i = 0; i < size; ++i) {
		if (current % 3 == 0) {
			m3[i] = current;
		}
		if (current % 7 == 0) {
			m7[i] = current;
		}
		if (current % 11 == 0) {
			m11[i] = current;
		}
		
		if (current == 2) {
			prime[i] = current;
		} 
		else if (current > 2) {
			int prime_flag = 0;
			for (int i = 2; i < current; ++i) {
				if (current % i == 0) {
					++prime_flag;
				}
			}
			
			if (prime_flag == 0) {
				prime[i] = current;
			}
		}

		++current;
	}

	time_t time_end = time(NULL);
	
	printf("\n");
	printf("==== Resultados =====\n");

	printf("\n");
	printf("Multiplos de 3\n");
	for (int i = 0; i < size; ++i) {
		if (m3[i] != 0) printf("%lld ", m3[i]);
	}

	printf("\n");
	printf("Multiplos de 7\n");
	for (int i = 0; i < size; ++i) {
		if (m7[i] != 0) printf("%lld ", m7[i]);
	}

	printf("\n");
	printf("Multiplos de 11\n");
	for (int i = 0; i < size; ++i) {
		if (m11[i] != 0) printf("%lld ", m11[i]);	
	}

	printf("\n");
	printf("Primos\n");
	for (int i = 0; i < size; ++i) {
		if (prime[i] != 0) printf("%lld ", prime[i]);	
	}
	printf("\n");
	
	printf("Tempo de execução: %ld segundos\n", (time_end - time_begin));

	return 0;
}
