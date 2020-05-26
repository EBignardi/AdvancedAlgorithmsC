#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
	Esercizio 5: Calcolare il fattoriale di un numero N. Sia N un
	numero intero positivo acquisito da standard input.
*/

unsigned long long Fattoriale(int N) {

	// Verifica del caso base
	if (N == 0) {
		return 1;
	}

	// Chiamata ricorsiva
	return N * Fattoriale(N - 1);
}

// Le funzioni ricorsive "BitFattoriale" e "BitFattorialeRec" servono
// per calcolare il numero di bit necessari per rapprentare il fattoriale 
// di un numero N e permettono di verificare se il programma è in grado 
// o meno di calcolare tale valore senza causare overflow. Questo controllo 
// è addizionale rispetto a quanto richiesto dal testo dell'esercizio).
double BitFattorialeRec(int N) {

	// Verifica dei casi base
	if (N == 2) {
		return 1;
	}

	return log2(N) + BitFattorialeRec(N - 1);
}

unsigned BitFattoriale(int N) {
	if (N < 2) {
		return 1;
	}
	
	return (unsigned)ceil(BitFattorialeRec(N));
}

int main(void) {

	int N, bits;
	int max_bit = sizeof(unsigned long long) * 8;

	do {
		printf("Inserire N: ");
		scanf("%d", &N);

		if (N < 0) {
			printf("Il numero deve essere maggiore o uguale a 0, riprovare!\n");
		}
		
		// Verifico se il fattoriale di N (N!) può essere calcolato o meno (overflow).
		bits = BitFattoriale(N);
		if (bits> max_bit) {
			printf("%d! non puo' essere calcolato, inserire un numero piu' piccolo!\n", N);
		}

	} while (N < 0 || bits > max_bit);

	printf("%d! = %llu\n", N, Fattoriale(N));

	return EXIT_SUCCESS;
}