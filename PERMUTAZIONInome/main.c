#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct persona {
	char nome[20];
}persona;

bool controlla(struct persona *v, int i, int *listauso, int n, int pos) {

	int k;
	int z = pos - 1;
	if (z < 0)
		return true;


	for (k = 0; k < n; k++) {
		if (listauso[k] == z)
			break;
	}

	//i è la posizione dell'elemento che voglio inserire
	//k è la posizione dell'elemento precedente da confrontare
	if (v[i].nome[0] == v[k].nome[0])
		return false;
	if (v[i].nome[0] == v[k].nome[0] + 1)
		return false;
	if (v[i].nome[0] + 1 == v[k].nome[0])
		return false;
	return true;
}

void stampa(int k, struct persona *v, int*listauso) {
	printf("{ ");
	for (int i = 0; i < k; i++) {
		int p = 0;
		while (1) {
			if (listauso[p] == i) {
				printf("%s  ", v[p].nome);
				break;
			}
			p++;

		}
	}
	printf(" }\n");
}

void backTrack(int n, int k, int pos, struct persona *v, int*listauso, int np) {
	//k indica l`insieme da formare, np indica quante ne ho gia prese
	if (np == k) {
		stampa(k, v, listauso);
		return;
	}

	/*if (pos == n)
	return;*/

	for (int j = 0; j < n; j++) {
		if (listauso[j] == -1) {
			if (controlla(v, j, listauso, n, pos) == 1) {
				listauso[j] = pos;
				backTrack(n, k, pos + 1, v, listauso, np + 1);
				listauso[j] = -1;
			}
		}
	}
}



int main(void) {
	FILE *f = fopen("nomi.txt", "rt");
	if (f == NULL)
		return;
	char c[20];
	int n = 0;//nuemro di nomi
	while (1) {
		int letti = fscanf(f, "%s", c);
		if (letti != 1) {
			rewind(f);
			break;
		}
		n++;
	}
	int k;
	int t = n / 2;

	do {
		printf("inserire numero di elementi di cui deve essere fornito ogni insieme\nprestando attenzione al fatto che deve essere maggiore o uguale ad 1 e minore o uguale a %d = ", t);
		scanf("%d", &k);
	} while (k<1 || k>t);

	persona a;
	persona *vec = malloc(n * sizeof(persona));

	//inserisco nel vettore vec tutti i nomi
	for (int i = 0; i < n; i++) {
		int letti = fscanf(f, "%s", &a.nome);
		if (letti != 1)
			break;

		vec[i] = a;
	}
	rewind(f);
	int *listauso = malloc(n * sizeof(int));
	//resetto lintera lista
	for (int i = 0; i < n; i++)
		listauso[i] = -1;

	backTrack(n, k, 0, vec, listauso, 0);

	fclose(f);
	return;

}