#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

int main() {
	FILE *fp;
	int n_threads, found = 0;
	char filename[256] = "test.txt", w2f[256] = "etc";

	printf("Entre com o numero de threads: ");
	scanf("%d", &n_threads);

	// printf("Entre com o caminho do arquivo: ");
	// scanf("%s", filename);	

	// printf("Entre com a palavra a ser procurada: ");
	// scanf("%s", w2f);

	int window = strlen(w2f);

	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Nao foi possivel abrir o arquivo\n");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
 	int end_fp = ftell(fp);
	rewind(fp);

	double start_time = omp_get_wtime();
	#pragma omp parallel num_threads(n_threads)
	{
		FILE *fp_thread;

		fp_thread = fopen(filename, "r");

		int id = omp_get_thread_num();
		int total_threads = omp_get_num_threads();
		int start, end, division, mod;

		division = end_fp / total_threads; 
		mod = end_fp % total_threads;

		start = (id - 1) * division;
		end = id * division;

		#pragma omp master
		{
			start = end_fp - (division + mod);
			end = end_fp;

			printf("%d\n", start);
			printf("%d\n", end);
			printf("%d\n", division);
			printf("%d\n", mod);
		}

		fseek(fp_thread, start, SEEK_CUR);

		for (int i=start; i<end; ++i) {

			char word[window];
			
			for(int j=0; j<window; ++j) word[j] = (char)fgetc(fp_thread);

			if (strcmp (word, w2f) == 0) {
				found = 1;
				break;
			}

			fseek(fp_thread, -window+1, SEEK_CUR);
		}
	}
	double end_time = omp_get_wtime() - start_time;

	if (found == 1) {
		printf("-> Palavra '%s' encontrada!\n", w2f);
	} else {
		printf("-> Palavra não encontrada!\n");
	}

	printf("\n");
	printf("Tempo final: %lf\n", end_time);

	return 0;
}
