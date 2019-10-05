#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	long long int size;
	
	printf("Entre com um tamanho para o Array: ");
	scanf("%lld", &size);

	long long int arr[size];
	long int POT_THREE = 10000, POT_SIX = 10000000;
	
	for (int i=0; i<size; ++i) {
		arr[i] = 0;
	}
	
	for (int i=0; i<size; ++i) {

		for (int j = (i+1) * POT_THREE; j <= (i+1) * POT_SIX; ++j ) {
			arr[i] += j;	
		}

	}

	for (int i=0; i<size; ++i) {
		printf("%lld\t", arr[i]);
	}

	return 0;
}
