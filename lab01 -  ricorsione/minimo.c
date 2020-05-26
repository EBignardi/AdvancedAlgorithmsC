#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
	Esercizio 3: Calcolare il minimo di una sequenza di elementi interi letti da 
	file di testo e separati da spazi bianchi.
*/

int Minimo(int *vec, unsigned len) {
	// Verifica del caso base
	len--;
	if (len == 0) {
		return vec[0];
	}

	// Chiamata ricorsiva
	int min = Minimo(vec, len);
	
	if (min < vec[len]) {
		return min;
	}
	else {
		return vec[len];
	}
}

unsigned CaricaVettore(char *filename, int **vec) {

	FILE *f = fopen(filename, "r");
	unsigned len = 0;
	int *loaded_vec = NULL;

	// Verifico se il file è stato aperto correttamente
	if (f == NULL) {
		printf("Si e' verificato un errore in apertura del file '%s' di input.\n", filename);
		exit(1);
	}

	// Leggo il file
	while (1) {
		int n;
		int r = fscanf(f, "%d", &n);
		if (r == 1) {
			loaded_vec = realloc(loaded_vec, sizeof(int)*++len);
			loaded_vec[len - 1] = n;
		}
		else {
			if (r == EOF) {
				break;
			}
			else {
				printf("Si e' verificato un errore in lettura del file di input.\n");
				exit(1);
			}
		}				
	}

	*vec = loaded_vec;
	fclose(f);
	return len;
}

int main(void) {

	char filename[] = "vettore.txt";

	int *vec = NULL;
	unsigned len = CaricaVettore(filename, &vec);

	printf("L'elemento minimo presente nel file e' %d.\n", Minimo(vec, len));

	free(vec);

	return EXIT_SUCCESS;
}