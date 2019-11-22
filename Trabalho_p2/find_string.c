#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	FILE *fp;
	int found = 0;
	char filename[256] = "test.txt", w2f[256] = "vidência";

	// printf("Entre com o caminho do arquivo: ");
	// scanf("%s", filename);	

	// printf("Entre com a palavra a ser procurada: ");
	// scanf("%s", w2f);

	int window = strlen(w2f);
	char word[window];

	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Nao foi possivel abrir o arquivo\n");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
 	int end_fp = ftell(fp);
	rewind(fp);	

	for (int i=0; i<end_fp; ++i) {
		fgets(word, (long) window + 1, fp);	

		if (strcmp (word, w2f) == 0) {
			found = 1;
			break;		
		}

		printf("%s", word);
		printf("\n");
		
		//fseek(fp, -window+1, SEEK_CUR);

		if (word[strlen(word)-1] != '\n') fseek(fp, -window+1, SEEK_CUR);
	}

	if (found == 1) {
		printf("-> Palavra %s encontrada!\n", w2f);
	} else {
		printf("-> Palavra não encontrada!\n");
	}

	return 0;
}
