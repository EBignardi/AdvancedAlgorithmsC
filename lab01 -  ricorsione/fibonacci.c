#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/* 
   Esercizio 2: Calcolare e stampare su standard output l’N-esimo numero della sequenza di Fibonacci.
   Sia N un numero intero positivo acquisito da standard input. 
   
   Si noti che la soluzione proposta implementa la versione estesa della successione, definita come segue:
   
   F(0) = 0,
   F(1) = 1,
   F(n) = F(n-1) + F(n-2),

   quindi:

   0,1,1,2,3,5,8,13,21,34,...
 */

unsigned Fibonacci(int N) {
	
	// Verifica dei casi base
	if (N < 2) {
		return N;
	}

	// Chiamata ricorsiva
	return Fibonacci(N - 1) + Fibonacci(N - 2);
}

int main(void) {
	
	int N;

	do {
		printf("Inserire N: ");
		scanf("%d", &N);
	
		if (N < 0) {
			printf("Il numero deve essere intero e positivo, riprovare!\n");
		}

	} while (N < 0);

	printf("Il valore %u-esimo della successione di Fibonacci e' %d.\n", N, Fibonacci(N));

	return EXIT_SUCCESS;
}