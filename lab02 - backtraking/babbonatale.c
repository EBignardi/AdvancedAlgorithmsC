// Esercizio 2 (Babbo Natale):
//
// Ogni anno che passa Babbo Natale fatica sempre più a caricare la slitta dei regali.Scrivere una procedura 
// ricorsiva che permetta di massimizzare il numero di regali caricati senza superare il peso consentito 
// (capienza). Si acquisiscano da standard input la capienza massima C(intero senza segno), il numero totale 
// dei regali N (intero senza segno) e i loro pesi P(array di interi senza segno).Mostrare su standard output 
// la soluzione, ovvero la sequenza di regali che occorre caricare per ottenere il valore massimo.
//
// Suggerimento :
// Si consiglia di passare alla procedura ricorsiva i seguenti parametri :
//	•	il numero di regali disponibili;
//	•	un array per memorizzare i pacchi caricati;
//	•	un array contenente i pesi dei pacchi;
//	•	una variabile per memorizzare il numero massimo di pacchi caricabili(soluzione);
//	•	un array per memorizzare la sequenza di caricamento migliore(soluzione);
//	•	un array per memorizzare la sequenza di caricamento corrente;
//	•	un contatore per memorizzare la posizione corrente dell'analisi del vettore;
//	•	la capienza della slitta;
//	•	il peso parziale raggiunto;
//	•	il numero di pacchi caricato dalla soluzione corrente;

// Considerazioni sulla firma della funzione di backtracking "RiempiSlitta": 
// N: è il numero di regali totali disponibili
// s: è la posizione corrente (a che livello dell'albero di backtrack si trova la funzione corrente)
// curr_sol: è il vettore binario (0-1) dei pacchi caricati (1) e non (0) dalla soluzione corrente.
// P: è il vettore dei pesi relativi ai vari pacchi
// best_sol: è il vettore binario (0-1) della miglior combinazione di pacchi trovata
// max: è il numero di regali caricati dalla soluzione migliore (best)
// count: è il numero di pacchi caricato dalla soluzione corrente
// sommaparziale: è la somma dei pesi dei pacchi caricati nella soluzione corrente
// C: è la portata massima della slitta

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void RiempiSlitta(const unsigned N, unsigned s, bool *curr_sol, const unsigned *P, bool *best_sol, unsigned *max, unsigned count, unsigned sommaparziale, const unsigned C) {

	// Se sono una foglia dell'albero di backtrack la slitta è piena.
	if (s == N) {
		// Mostro la soluzione corrente (che non è necessariamente quella ottima)
		printf("Peso: %4d, Regali: %2d, Combinazione: ", sommaparziale, count);
		for (unsigned i = 0; i<N; ++i) {
			printf("%d ", curr_sol[i]);
		}
		printf("\n");

		// Se la soluzione corrente è migliore della best_sol aggiorno la best_sol e il max
		if (count>*max) {
			*max = count;
			memcpy(best_sol, curr_sol, N * sizeof *curr_sol);
		}
		return;
	}

	// Scendo l'albero considerando il caso in cui non carico il pacco corrente
	curr_sol[s] = 0;
	RiempiSlitta(N, s + 1, curr_sol, P, best_sol, max, count, sommaparziale, C);

	// Se posso, scendo l'albero considerando il caso in cui caricao il pacco corrente
	if (sommaparziale + P[s] <= C) {
		curr_sol[s] = 1;
		RiempiSlitta(N, s + 1, curr_sol, P, best_sol, max, count + 1, sommaparziale + P[s], C);
	}
}

void main(void) {
	unsigned C, N;

	printf("Inserire la capienza massima C della slitta: ");
	scanf("%u", &C);

	printf("Inserire il numero di pacchi N a dispozione: ");
	scanf("%u", &N);

	unsigned *P = malloc(N * sizeof(unsigned));

	printf("Inserire la liste dei pesi (interi senza segno separati da spazi):\n");
	for (unsigned i = 0; i < N; ++i) {
		scanf("%u", &P[i]);
	}

	bool *best_sol, *curr_sol;

	best_sol = calloc(N, sizeof *best_sol);
	curr_sol = malloc(N * sizeof *best_sol);

	unsigned max = 0; // Massimo numero di pacchi caricabili

	RiempiSlitta(N, 0, curr_sol, P, best_sol, &max, 0, 0, C);

	printf("Il numero massimo di regali che Babbo Natale puo' caricare e' %d.\nPer farlo puo' utilizzare la seguente combinazione di pacchi (non e' detto che sia l'unica):\n", max);
	for (unsigned i = 0; i < N; ++i) {
		printf("%d ", best_sol[i]);
	}
	printf("\n");

	free(best_sol);
	free(curr_sol);
}