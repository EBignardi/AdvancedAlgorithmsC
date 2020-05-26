#include <stdio.h>
//n programmi
//t[i] tempo di esecuzione
//s[i] tempo di scadenza
//z tempo trascorso da inizio programma
//costo[i] funzione costo (di esecuzione)
void funzione(int n, int *t, int *s, int cont_tempo, int cont_rimanente, int z, int *costo) {
	int ris = 0, i, best = 0, j = 0;

	//calcolo il costo di ogni processo nel tempo
	for (i = 0; i < n; i++) {
		costo[i] = (s[i] - z) * t[i];
	}

	//trovo il processo migliore da far eseguire
	i = 0;
	best = costo[i];
	while (i < n) {
		//devo trovare il processo con costo MINORE e che possa finire in tempo
		if (best > costo[i] && (i != z) && ((t[i] + cont_tempo) < s[i])) { 
			best = costo[i];
			//salvo la posizione del migliore in j
			j = i;
		}
		i++;
	}

	//azzero il costo del migliore cosi da non renderlo piu utilizzabile al prox giro
	costo[j] = 0;

	//conto il tempo impiegato dal processo migliore
	cont_tempo += t[j];

	//controllo se il tempo che ho a disposizione per eseguire il processo migliore
	if (cont_tempo < s[j]) {
		printf("%d\t", j);
		z += j;
		funzione(n, t, s, cont_tempo + t[j], s[j], z, costo);
	}

	return;
}

int main(void)

{
	int tempo[4] =  { 6, 4, 2, 15 };
	int scadenza[4] = { 20, 5, 4, 21 };

	int *c = malloc(sizeof(scadenza) * sizeof(int));

	funzione(4, tempo, scadenza, 0, 0, 0, c);
}