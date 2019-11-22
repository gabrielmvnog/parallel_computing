#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int valid_digits(int *digits, int true_value, int position) {
	int mod, sum = 0;	
	
	position = 8 + position;

	#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < position; ++i) {
		sum += digits[i] * (position + 1 - i);
	}

	mod = (sum * 10) % 11;
	mod = mod % 10;

	return mod == true_value;
}

int countlines(FILE *fp) {
	int lines = 0;
	int ch = 0;

	if (fp == NULL) {
		return 0;
	} else {
		while((ch = fgetc(fp)) != EOF) {
			if (ch == '\n') lines++;		
		}
	}

	return lines;
}

int main() {
	char *filename = "cpfs1.txt";
	FILE *fp = fopen(filename, "r");
	char line[15];
	int total_lines;

	double start_time = omp_get_wtime();

	int n_threads;

	printf("Entre com o numero de threads: ");
	scanf("%d", &n_threads);
	printf("\n");

	if (fp == NULL) {
		printf("NO SUCH FILE");
		return -1;
	} else {
		total_lines = countlines(fp);
		rewind(fp);

		#pragma omp parallel num_threads(n_threads)
		{
			int thread_id = omp_get_thread_num();		

			#pragma omp for 
			for (int i = 0; i < total_lines; ++i) {
				fgets(line, 15, fp);

				int valid, digits[15];

				for (int j = 0; j < 11; ++j) {
					digits[j] = line[j] - '0';
				}

				valid = valid_digits(digits, digits[9], 1) & valid_digits(digits, digits[10], 2);

				if (!valid) {
					printf("CPF: %sThread: %d\n", line, thread_id);
				}
			}
		}
	}

	double end_time = omp_get_wtime() - start_time;
	printf("\n");
	printf("Tempo final: %lf\n", end_time);

	fclose(fp);
	
	return 0;	
}

