#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 15 //articoli passati

typedef struct {
	char nome[10]; // puo comparire un solo articolo per nome
	int prezzo;
} Articolo;

// visualizzi tutti i possibili insiemi di 4 articoli il cui costo totale sia esattamente 30 Euro
void CalcolaArticoli(int n, int s, int v[], Articolo articoli[], int sommaparziale, int conta, int costoTot, int k) {
	int i; //usato come contatore nei vari cicli for

	//caso in cui ho finito e trovato la soluzione
	if (sommaparziale == costoTot && conta == k) {
		for (i = s; i < n; i++) v[i] = 0;

		printf("\nSoluzione: ");
		for (i = 0; i < n; i++) printf("%d ", v[i]);

		printf("\nArticoli selezionati: ");
		for (i = 0; i < n; i++) {
			if (v[i] == 1) {
				printf("\n%s %d", articoli[i].nome, articoli[i].prezzo);
			}
		}
		return;
	}
	
	//caso in cui sono arrivato alla fine 
	if (s == n)
		return;


	v[s] = 0;
	CalcolaArticoli(n, s + 1, v, articoli, sommaparziale, conta, costoTot, k);

	conta++;
	sommaparziale += articoli[s].prezzo;
	if (sommaparziale <= costoTot && conta <= k) {
		v[s] = 1;
		CalcolaArticoli(n, s + 1, v, articoli, sommaparziale, conta, costoTot, k);
	}


}

int main(void)
{
	FILE *file;  // file dove sara presente la lista degli articoli

	Articolo articoli[N]; //vettore dei 15 articoli
	int v[N]; //vettore composto da 0-1 in base se larticolo e preso o meno
	int tot = 0, costoTot = 30, k = 4; // costotot indica il prezzo a cui devo arrivare e k quanti articoli prendere

	int i = 0, dim;

	file = fopen("magazzino.txt", "r");

	//scannerizzo il file per averli nel vettore articoli[]
	while (!feof(file))
	{
		fscanf(file, "%s", articoli[i].nome);
		fscanf(file, "%d", &articoli[i].prezzo);
		i++;
	}

	dim = i ;

	CalcolaArticoli(dim, 0, v, articoli, 0, 0, costoTot, k);

}