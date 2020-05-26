#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
	Esercizio 4: Calcolare il prodotto di due numeri interi positivi (utilizzando solo la somma).
	I numeri devono essere acquisiti di standard input. La soluzione dell'esercizio 4 è la
	funzione "ProdottoPositivi".

	Esercizio 4-bis: Estendere l'esercizio 4 al caso di numero interi con segno.  La soluzione
	dell'esercizio 4-bis è la funzione "Prodotto".

*/

unsigned ProdottoPositivi(int a, int b) {

	// Verifica del caso base
	if (b == 0) {
		return 0;
	}

	// Chiamata ricorsiva
	return a + ProdottoPositivi(a, --b);
}

int Prodotto(int a, int b) {

	// Verifica del caso base
	if (b == 0) {
		return 0;
	}

	// Chiamate ricorsive 
	if (b > 0) {
		return a + Prodotto(a, --b);
	}
	else {
		return -a + Prodotto(a, ++b);
	}
}


int main(void) {

	// Test della funzione "ProdottoPositivi"
	printf("Esercizio 4:\n");
	int a, b;
	do {
		printf("Inserire il primo numero (maggiore o uguale a 0): ");
		scanf("%d", &a);

		printf("Inserire il secondo numero (maggiore o uguale a 0): ");
		scanf("%d", &b);

		if (a < 0 || b < 0) {
			printf("I numeri devono essere entrambi maggiori o uguali a 0, riprovare!\n");
		}

	} while (a < 0 || b < 0);

	printf("%d x %d = %u\n", a, b, ProdottoPositivi(a, b));

	// Test della funzione "Prodotto"
	printf("\n\nEsercizio 4-bis:\n");
	printf("Inserire il primo numero: ");
	scanf("%d", &a);

	printf("Inserire il secondo numero: ");
	scanf("%d", &b);

	printf("%d x %d = %d\n", a, b, Prodotto(a, b));


	return EXIT_SUCCESS;
}