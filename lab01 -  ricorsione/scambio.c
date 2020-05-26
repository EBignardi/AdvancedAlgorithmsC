#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
	Esercizio 8: Dato un vettore di N numeri interi, scrivere una funzione ricorsiva che ne scambi gli elementi
	fino a metterli in ordine inverso rispetto alla posizione iniziale (senza dichiarare vettori aggiuntivi).
	Il vettore di input deve essere letto da file di testo (i numeri sono separati da spazi).
*/

void Inverti(int *v, int i, int n) {
	if (i >= n / 2) {
		return;
	}
	else {
		int c = v[n - i - 1];
		v[n - i - 1] = v[i];
		v[i] = c;
		Inverti(v, i + 1, n);
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

void Stampa(int *v, unsigned l) {
	printf("[");
	unsigned i;
	for (i = 0; i < l - 1; ++i) {
		printf("%d, ", v[i]);
	}
	printf("%d]\n", v[i]);
}

int main(void) {

	char filename[] = "vettore.txt";

	int *vec = NULL;
	unsigned len = CaricaVettore(filename, &vec);

	printf("Vettore originale:\n");
	Stampa(vec, len);
	
	Inverti(vec, 0, len);

	printf("\nVettore invertito:\n");
	Stampa(vec, len);

	free(vec);

	return EXIT_SUCCESS;
}