#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// visualizzi tutti i possibili insiemi di 10 macchine
// b = contatore berline vicine
// m = contatore monovolume
// k = contatore berline
// tot = posti totali
// conta = sara incrementato a ogni volta che inserisco un oggetto nel vettore
// v = vettore soluzione
void CalcolaMacchine(int *v, int b, int m, int tot, int conta, int k) {
	int i; //usato come contatore nei vari cicli for

	//caso in cui ho finito e trovato una delle soluzioni --> STAMPO
	if (conta == tot && m >= 3 && k >= 5) {
		printf("\nSoluzione: ");
		for (i = 0; i < tot; i++) printf("%d ", v[i]);
		return;
	}

	//caso in cui sono arrivato alla fine 
	if (conta == tot) 	
		return;
	

	v[conta] = 0;
	//chiamata ricorsiva
	CalcolaMacchine(v, b, m + 1, tot, conta + 1, k);

	//controlla la condizione per continuare
	//se ho gia due berline vicine devo mettere una monovolume
	if (b == 2) {
		v[conta] = 0;
		CalcolaMacchine(v, 0, m + 1, tot, conta + 1, k);
	}
	else {
		v[conta] = 1;
		CalcolaMacchine(v, b + 1, m, tot, conta + 1, k + 1);
	}
}

int main(void)
{

	int v[10]; //vettore composto da 0-1 in base se Berlina (1) o Monovolume (0)
	int totale = 10; // tot indica i componenti totali

	//resetto lintero vettore
	for (int i = 0; i < totale; i++)
		v[i] = -1;

	CalcolaMacchine(v, 0, 0, totale, 0, 0);
}
