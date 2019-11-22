#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	FILE *fp;
	int found = 0;
	char filename[256] = "test.txt", w2f[256] = "médium";

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

	for (int i=0; i<end_fp; ++i) {

		char word[window];
		
		for(int j=0; j<window; ++j) word[j] = (char)fgetc(fp);

		printf("%s", word);
		printf("\n");

		if (strcmp (word, w2f) == 0) {
			found = 1;
			break;		
		}

		fseek(fp, -window+1, SEEK_CUR);
	}

	if (found == 1) {
		printf("-> Palavra '%s' encontrada!\n", w2f);
	} else {
		printf("-> Palavra não encontrada!\n");
	}

	return 0;
}
