// Esercizio 1 (Ombrelloni)

// Giovanni, Mario e Luca trascorrono una giornata al mare.Giunti in spiaggia decidono di affittare un ombrellone 
// ciascuno: tutti e tre vogliono affittarne uno in prima fila, senza però essere vicini tra loro.La prima fila, 
// contenente N ombrelloni(per semplicità si fissi N a 10), è tutta libera.

// Scrivere una procedura ricorsiva per trovare le possibili posizioni dei tre ragazzi.Mostrare su standard output
// quante e quali sono le soluzioni.

// Suggerimento :
// Si consiglia di passare alla procedura ricorsiva i seguenti parametri :
//	•	un array per memorizzare la soluzione parziale corrente;
//	•	il numero delle soluzioni trovate;
//	•	un contatore per memorizzare quanti ragazzi sono stati posizionati fino a quel momento;
//	•	un contatore per memorizzare la “posizione” corrente dell'analisi del vettore.

// Considerazioni sulla firma della funzione di backtracking "SubsetK": 
// n: è il numero n degli ombrelloni in prima fila (qui fisso a 10)
// s: è la posizione corrente (a che livello dell'albero di backtrack si trova la funzione corrente)
// v: è il vettore binario (0-1) del posizionamento corrente 1 = posizionato, 0 = NON posizonato
// n_slz: è il numero delle soluzioni trovate
// cnt: è il contatore dei ragazzi posizionati fino ad ora nella soluzione corrente
// k: (< n) è il numero dei ragazzi da posizionare (qui fisso a 3)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void SubsetK(const unsigned n, int s, bool *v, unsigned *n_slz, unsigned cnt, unsigned const k) {

	// Controllo se la soluzione è completa, ovvero se ho già posizionato tutti i ragazzi (caso base)
	if (cnt == k) {
		printf("%4d) ", ++(*n_slz));

		// Completo la soluzione corrente
		memset(v + s, 0, (n - s) * sizeof *v);
		
		// In alternativa al memset si poteva utilizzare un ciclo
		//for (int i = s; i < n; i++) {
		//	v[i] = 0;
		//}

		// Stampo su stdout la soluzione corrente
		for (unsigned i = 0; i < n; i++) {
			printf("%d ", v[i]);
		}
		printf("\n");
		return;
	}

	// Controllo se c'è ancora posto nella fila (caso base)
	if (s == n) {
		// Sono giunto all'ultimo ombrellone della file, la soluzione non è accettabile
		// perchè non sono riuscito a posizionare tutti i ragazzi
		return;
	}

	// Proseguo il backtrack lasciando l'ombrellone corrente vuoto
	v[s] = 0;
	SubsetK(n, s + 1, v, n_slz, cnt, k);

	// Se posso, proseguo il backtrack posizionando un ragazzo nell'ombrellone corrente
	if (s == 0 || (s > 0 && v[s - 1] == 0)) {
		v[s] = 1;
		SubsetK(n, s + 1, v, n_slz, cnt + 1, k);
	}
}

void main(void) {

	unsigned n = 10; // Posti disponibili (ombrelloni in prima fila)
	unsigned k = 3;  // Persone da sistemare (numero di ragazzi)

	unsigned n_slz = 0; // Numero soluzioni
	bool *v; // Soluzione corrente

	v = malloc(n * sizeof *v);

	SubsetK(n, 0, v, &n_slz, 0, k);
	printf("Sono state trovate %d soluzioni!\n", n_slz);

	free(v);
}