#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	unsigned peso;    // Peso del pacco	
	unsigned altezza; // Altezza del pacco	
	unsigned limite;  // Limite di peso che il pacco pu� sorregere
} pacco;

typedef struct {
	unsigned altezza;  // Altezza torre
	int *pacchiTorre;  // Vettore che tiene traccia dei pacchi utilizzati e dell'ordine con cui sono stai caricati
} torre;


// La funzione "verifica" controlla se � possibile o meno caricare un pacco sulla torre.
// corrente: torre corrente, 
// f: dimensione della torre corrente, 
// pacchi: array dei pacchi disponibili, 
// i: posizione del pacco che si vuole inserire (verificare) alla base della torre corrente
bool verifica(torre *corrente, int f, pacco *pacchi, int i)
{
	unsigned pesoTotale = 0;

	for (int j = 0; j<f; j++) {
		pesoTotale += pacchi[corrente->pacchiTorre[j]].peso;
	}

	if (pacchi[i].limite < pesoTotale) {
		return false; // NON � possibili caricare il pacco
	}

	return true; // E' possibile caricare il pacco
}

void CostruisciTorre(int n, pacco *pacchi, int s, torre *corrente, torre *best, int *listaUso)
{

	// Controllo se sono terminati i pacchi
	if (s == n) {

		// Se la soluzione corrente � migliore della best aggiorno la best
		if (corrente->altezza > best->altezza) {
			best->altezza = corrente->altezza;
			memcpy(best->pacchiTorre, corrente->pacchiTorre, n * sizeof(int));

			// In alternativa al memcpy si poteva utilizzare un ciclo for
			//for (int i = 0; i<n; i++){
			//	best->pacchi[i] = corrente->pacchi[i];
			//}
		}
		return;
	}

	// Per ogni pacco a disposizione
	for (int i = 0; i<n; i++) {

		// Se il pacco � gi� stato utilizzato salto al successivo
		if (listaUso[i] == 0) {
			// Verifico se � possibile caricare il pacco
			if (verifica(corrente, s, pacchi, i)) {

				// Inserisco il pacco perch� rispetta i vincoli
				corrente->pacchiTorre[s] = i;
				corrente->altezza += pacchi[i].altezza;
				listaUso[i] = 1;

				// Proseguo con il backtrack
				CostruisciTorre(n, pacchi, s + 1, corrente, best, listaUso);

				// Tolgo il pacco per provare a caricare il successivo alla prossima iterazione
				corrente->pacchiTorre[s] = -1;
				listaUso[i] = 0;
				corrente->altezza -= pacchi[i].altezza;
			}
			else {
				// Non posso inserire il pacco quindi proseguo senza caricarlo
				CostruisciTorre(n, pacchi, n, corrente, best, listaUso);
			}
		}
	}
}


int main(void)
{
	// Elenco dei pacchi che � possibile caricare (basta modificare questo array se si vuole modificare la lista dei pacchi che si possono utilizzare per costruire la torre)
	pacco elencoPacchi[] = { { .peso = 10,.altezza = 20,.limite = 40 },{ .peso = 10,.altezza = 10,.limite = 8 },{ .peso = 9,.altezza = 3,.limite = 5 } /*, { .peso = 10, .altezza = 1000, .limite = 20 }*/ };

	// Numero di pacchi a disposizione
	int n = sizeof(elencoPacchi) / sizeof(pacco);

	torre corrente = { .altezza = 0,.pacchiTorre = malloc(n * sizeof(int)) };
	torre best = { .altezza = 0,.pacchiTorre = malloc(n * sizeof(int)) };

	// Inizializzo la lista dei pacchi in torre corrente e torre best a -1
	for (int i = 0; i<n; i++) {
		corrente.pacchiTorre[i] = -1;
		best.pacchiTorre[i] = -1;
	}

	int *listaUso;
	listaUso = calloc(n, sizeof(int)); // Nessun pacco utilizzato all'inizio -> listaUso inizializzata a zero

	printf("Lista di pacchi che si possono utilizzare (PESO, ALTEZZA, LIMITE):\n");
	for (int i = 0; i < n; i++) {
		printf("(Pacco %d): %4d, %4d, %4d\n", i, elencoPacchi[i].peso, elencoPacchi[i].altezza, elencoPacchi[i].limite);
	}
	printf("\n");

	// Chiamo la funzione di backtracking
	CostruisciTorre(n, elencoPacchi, 0, &corrente, &best, listaUso);

	if (best.altezza == 0)
		printf("Impossibile costruire la torre\n");
	else {
		printf("La torre piu' alta e' alta %d, ed e' formata dai seguenti pacchi (dall'alto al basso):\n", best.altezza);
		for (int i = 0; i < n; i++) {
			if (best.pacchiTorre[i] >= 0) {
				printf("%4d\n", best.pacchiTorre[i]);
			}
		}
	}

	free(corrente.pacchiTorre);
	free(best.pacchiTorre);
	free(listaUso);

	return 0;
}
