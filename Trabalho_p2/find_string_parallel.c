#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

int main() { 
	FILE *fp;
	int n_threads, found = 0;
	char filename[256] = "large-file", w2f[256];

	printf("Entre com a string a ser procurada: ");
	scanf("%[^\n]", w2f);

	printf("Entre com o numero de threads: ");
	scanf("%d", &n_threads);

	// printf("Entre com o caminho do arquivo: ");
	// scanf("%s", filename);	

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

			//printf("%d\n", start);
			//printf("%d\n", end);
			//printf("%d\n", division);
			//printf("%d\n", mod);
		}

		#pragma omp barrier

		fseek(fp_thread, start, SEEK_CUR);

		for (int i=start; i<end; ++i) {

			char word[window];

			fgets(word, window+1, fp_thread);

			if (word[strlen(word)-1] != '\n') fseek(fp_thread, -window+1, SEEK_CUR);

			if (strcmp (word, w2f) == 0) found = 1;	
		}
	
	}
	double end_time = omp_get_wtime() - start_time;

	if (found == 1) {
		printf("-> String '%s' encontrada!\n", w2f);
	} else {
		printf("-> String não encontrada !!!\n");
	}

	printf("\n");
	printf("Tempo final: %lf\n", end_time);

	return 0;
}
