#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
	Esercizio 1: Calcolare la somma dei primi N numeri interi positivi (0 escluso). 
	Sia N un numero intero acquisito da standard input.
*/

unsigned Somma(int N) {

	// Verifica del caso base
	if (N == 1) {
		return 1;
	}

	// Chiamata ricorsiva
	return N + Somma(N - 1);
}

int main(void) {

	int N;

	do {
		printf("Inserire N: ");
		scanf("%d", &N);

		if (N <= 0) {
			printf("Il numero deve essere intero e maggiore di 0, riprovare!\n");
		}

	} while (N <= 0);

	printf("La somma dei primi %u numeri interi e' %d.\n", N, Somma(N));

	return EXIT_SUCCESS;
}