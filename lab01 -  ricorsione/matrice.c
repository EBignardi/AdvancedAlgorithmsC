#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
	Esercizio 7: Scrivere un programma che determini se una matrice quadrata N × N sia o meno simmetrica rispetto
	alla diagonale principale. La matrice deve essere letta da file di testo dove le colonne sono separate da spazi
	bianchi e le righe dal carattere ‘\n’.
*/

typedef struct MQ {
	unsigned dimensione;
	int **dati;
} MQ;

bool Simmetrica(const MQ *mat, int i, int j) {

	// Verifica del caso base
	if (i == 0) {
		return true;
	}

	// Controlli sulla riga corrente terminati: si passa alla riga di indice inferiore
	if (j < 0) {
		return (Simmetrica(mat, i - 1, i - 1));
	}

	// Elemento sulla diagonale principale: si passa alla colonna di indice inferiore
	if (i == j) {
		return (Simmetrica(mat, i, j - 1));
	}

	// Elemento della triangolare inferiore da confrontare con il simmetrico nella triangolare superiore
	return (mat->dati[i][j] == mat->dati[j][i]) && (Simmetrica(mat, i, j - 1));
}

void CaricaMatrice(char *filename, MQ *mat) {

	FILE *f = fopen(filename, "r");
	unsigned len = 0;

	// Verifico se il file è stato aperto correttamente
	if (f == NULL) {
		printf("Si e' verificato un errore in apertura del file '%s' di input.\n", filename);
		exit(1);
	}

	if (fscanf(f, "%d", &mat->dimensione) != 1) {
		printf("La formattazione del file di input è sbagliata!");
		exit(1);
	}

	// Alloco la memoria per contenere la matrice
	mat->dati = malloc(sizeof(int*)*mat->dimensione);

	for (unsigned i = 0; i < mat->dimensione; ++i) {
		mat->dati[i] = malloc(sizeof(int)*mat->dimensione);
	}

	// Leggo il file 
	int r = 0, c = 0;
	while (1) {
		int n;
		int rs = fscanf(f, "%d", &n);
		if (rs == 1) {
			if (r >= mat->dimensione || c >= mat->dimensione) {
				printf("La formattazione del file di input e' sbagliata!\n");
				exit(1);
			}
			mat->dati[r][c++] = n;
			if (c == mat->dimensione) {
				r++; 
				c = 0;
			}
		}
		else {
			if (rs == EOF) {
				if (c != 0 || r != mat->dimensione) {
					printf("La formattazione del file di input e' sbagliata\n!");
					exit(1);
				}
				break;
			}
			else {
				printf("Si e' verificato un errore in lettura del file di input.\n");
				exit(1);
			}
		}
	}

	fclose(f);
}

int main(void) {

	char filename[] = "matrice.txt";

	MQ mat;

	CaricaMatrice(filename, &mat);
	if (Simmetrica(&mat, (int)mat.dimensione - 1, (int)mat.dimensione - 1)) {
		printf("La matrice e' simmetrica rispetto alla diagonale principale.\n");
	}
	else {
		printf("La matrice NON e' simmetrica rispetto alla diagonale principale.\n");
	}

	free(mat.dati);

	return EXIT_SUCCESS;
}