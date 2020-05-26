#define _CRT_SECURE_NO_WARNINGS

// Creare un file binario “oro.dat” contenente dati relativi al mercato azionario, secondo la seguente 
// struttura dati:
//
// typedef struct
// {
//		int Codice;
//		float Peso;
//		float Prezzo;
// } Gioielli;
//
// nella quale Codice indica l’identificatore di un gioiello, Peso il suo peso in grammi e Prezzo il suo
// prezzo di vendita in euro.
//
// Avendo a disposizione un valore massimo di budget B acquisito da standard input, scrivere un programma 
// che scelga i gioielli da comprare(un gioiello si deve comprare per intero senza frazionamenti) in modo 
// da massimizzare il peso complessivo dei gioielli acquistati.Si leggano i dati dei gioielli dal file “oro.dat".

// N.B. La soluzione proposta NON sfrutta l'ordinamento 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
	int Codice;
	float Peso;
	float Prezzo;
} Gioielli;


int TrovaMigliore(Gioielli *g, size_t n)
{
	size_t i = 0;
	for (; g[i].Peso == 0; ++i);

	if (i >= n) {
		return -1;
	}

	float valoreMigliore = g[i].Peso / g[i].Prezzo;
	int pezzoMigliore = i;

	for (; i < n; i++)
	{
		float valoreCorrente = g[i].Peso / g[i].Prezzo;
		if (valoreCorrente > valoreMigliore)
		{
			valoreMigliore = valoreCorrente;
			pezzoMigliore = i;
		}
	}

	return pezzoMigliore;
}

// Scrivo sul file la/e struttura/e dati inserita/e dall'utente
int ScriviDati(void) {
	FILE *f;

	f = fopen("oro.dat", "ab");
	if (f == NULL) {
		return -1;
	}

	Gioielli g;

	char continua = 'y';
	int i = 1;
	do {

		printf("Vuoi inserire gioielli nel file (s/n)?");
		scanf(" %c", &continua);

		if (continua != 's' && continua != 'S') {
			if (continua == 'n' || continua == 'N') {
				break; // Termino l'inserimento di nuovi gioielli
			}
			else {
				continue; // Carattere non riconosciuto
			}
		}
		printf("Codice: ");
		scanf("%d, ", &g.Codice);
		printf("Peso: ");
		scanf("%f, ", &g.Peso);
		printf("Prezzo: ");
		scanf("%f, ", &g.Prezzo);
		fwrite(&g, sizeof(g), 1, f);
		i++;
	} while (true);

	fclose(f);
	return 0;
}

// Leggo i dati dei gioielli da file
int LeggiDati(Gioielli **g)
{
	FILE *f;

	f = fopen("oro.dat", "rb");
	if (f == NULL) {
		return -1;
	}

	Gioielli *nuovo = NULL;
	Gioielli tmp;

	int i = 0;
	while (fread(&tmp, sizeof(Gioielli), 1, f) == 1) {
		nuovo = realloc(nuovo, (++i) * sizeof(Gioielli));
		nuovo[i - 1] = tmp;
	}

	*g = nuovo;

	fclose(f);
	return i; // Restituisco il numero di gioielli letti da file
}

// Funzione per la stampa a video dei gioelli in un vettore
void StampaGioielli(Gioielli *g, size_t s) {

	for (size_t i = 0; i < s; ++i) {
		printf("Codice - %2d, Peso - %8.4f, Prezzo - %4.4f;\n", g[i].Codice, g[i].Peso, g[i].Prezzo);
	}
}

int main(void)
{

	Gioielli *g;
	Gioielli *acquistati;
	int n; // Numero di gioielli disponibili sul mercato azionario

	if (ScriviDati() < 0) {
		printf("Impossibile scrivere sul file!");
	}
	n = LeggiDati(&g);
	if (n <= 0) {
		printf("Impossibile leggere i dati da file!");
	}

	acquistati = malloc(n * sizeof(Gioielli));

	printf("Elenco gioielli disponibili:\n");
	StampaGioielli(g, n);

	float budget;

	printf("Inserire il budget: ");
	scanf("%f", &budget);

	float soldi_rimasti = budget;
	int contatore_acquisto = 0, migliore;
	
	while (soldi_rimasti > 0)
	{
		migliore = TrovaMigliore(g, n);
		if (migliore == -1)
			break;
		else
		{
			if (g[migliore].Prezzo <= soldi_rimasti)
			{
				acquistati[contatore_acquisto++] = g[migliore];
				soldi_rimasti -= g[migliore].Prezzo;
			}
			// Setto il peso del gioiello a zero per ricordarmi che è già stato preso o che non può essere preso perchè sfora il budget
			g[migliore].Peso = 0;
		}
	}

	printf("Budget: %f, Soldi rimasti: %f, elenco dei gioielli acquistati:\n", budget, soldi_rimasti);

	StampaGioielli(acquistati, contatore_acquisto);

	return 0;
}