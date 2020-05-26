#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
	Esercizio 6: Calcolare la divisione intera di due numeri interi positivi (utilizzando solo la sottrazione).
	I numeri devono essere acquisiti da tastiera. La funzione ricorsiva deve restituire il valore -1 se la
	divisione è impossibile. La soluzione dell'esercizio 6 è la funzione "DivisionePositivi"

	Esercizio 6-bis: Estendere l'esercizio 4 al caso di numero interi con segno.  La soluzione dell'esercizio
	6-bis è la funzione "Divisione".
*/

int DivisionePositivi(int a, int b) {

	// Verifica dei casi base
	if (b == 0) {
		return -1;
	}

	if (a < b) {
		return 0;
	}

	// Chiamata ricorsiva
	return 1 + DivisionePositivi(a-b, b);
}

int Divisione(int a, int b) {

	// Verifica dei casi base
	if (b == 0) {
		return -1; // In questo caso il valore -1 è ambiguo perchè potrebbe significare sia che 
				   // il risultato della divisione è -1, sia che la divisione è impossibile.
	}

	if (abs(a) < abs(b)) {
		return 0;
	}

	// Chiamate ricorsive
	if (a > 0) {
		if (b > 0) {
			// a > 0 && b > 0
			return 1 + Divisione(a - b, b);
		}
		else {
			// a > 0 && b < 0
			return -1 + Divisione(a + b, b);
		}
	}
	else {
		if (b > 0) {
			// a < 0 && b > 0
			return -1 + Divisione(a + b, b);
		}
		else {
			// a < 0 && b < 0
			return 1 + Divisione(a - b, b);
		}
	}
}

int main(void) {

	// Test della funzione "DivisionePositivi"
	printf("Esercizio 6:\n");
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

	printf("%d / %d = %d\n", a, b, DivisionePositivi(a, b));

	// Test della funzione "Divisione"
	printf("\n\nEsercizio 6-bis:\n");
	printf("Inserire il primo numero: ");
	scanf("%d", &a);

	printf("Inserire il secondo numero: ");
	scanf("%d", &b);

	printf("%d / %d = %d\n", a, b, Divisione(a, b));


	return EXIT_SUCCESS;
}