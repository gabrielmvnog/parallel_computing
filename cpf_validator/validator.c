#include <stdio.h>
#include <stdlib.h>

int valid_digits(int *digits, int true_value, int position) {
	int mod, sum = 0;	
	
	position = 8 + position;

	for (int i = 0; i < position; ++i) {
		sum += digits[i] * (position + 1 - i);
	}
	
	mod = (sum * 10) % 11;
	mod = mod % 10;

	return mod == true_value;
}

int countlines(char *filename) {
	FILE *fp = fopen(filename, "r");
	int lines = 0;
	int ch = 0;

	if (fp == NULL) {
		return -1;
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

	if (fp == NULL) {
		printf("NO SUCH FILE");
		return -1;
	} else {

		total_lines = countlines(filename);

		for (int i = 0; i < total_lines; ++i) {
			fgets(line, 15, fp);

			int valid, digits[10];

			// printf("CPF: %s", line);
			
			for (int i = 0; i<= 10; ++i) {
				digits[i] = line[i] - '0';	
			}

			valid = valid_digits(digits, digits[9], 1) & valid_digits(digits, digits[10], 2);
	
			if (!valid) {
				printf("CPF: %s\n", line);
			}
		}
	}
	
	fclose(fp);
	
	return 0;	
}

