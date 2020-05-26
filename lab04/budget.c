#define _CRT_SECURE_NO_WARNINGS

// Dato un budget B rappresentato da un intero positivo diverso da zero acquisito da standard 
// input e un numero infinito di monete con i seguenti tagli : 50c, 20c, 10c, 5c, 2c e 1c, 
// scrivere un programma che trovi il numero mimino(intero) di monete necessarie per formulare 
// il budget. Si utilizzia tale scopo un algoritmo greedy basato sulla massimizzazione del 
// taglio delle monete.

#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 

void budget(unsigned *monete, size_t size, int B)
{
	unsigned *ris = calloc(size, sizeof(unsigned));
	unsigned min = 0;

	for (unsigned i = 0; i < size; ++i)
	{
		ris[i] = B / monete[i];
		B = B % monete[i];
		min = min + ris[i];
	}

	printf("Il numero minimo di monete trovato e' %d:\n", min);
	for (unsigned i = 0; i < size; ++i)
		printf("%d: %d\n", monete[i], ris[i]);
}

int main()
{
	int B;
	while(1){
		printf("Inserire il budget: ");
		scanf("%d", &B);

		if (B > 0) {
			break;
		}

		printf("Il budget deve essere maggiore di 0!\n");
	};

	unsigned monete[] = { 50, 20, 10, 5, 2, 1 };
	size_t size = sizeof(monete) / sizeof(unsigned);

	budget(monete, size, B);
};