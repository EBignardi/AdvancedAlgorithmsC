#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#define MAX 20

void zaino(int n, float peso[], float valore[], float peso_max) {
	float x[MAX], tv = 0; //valore parziale
	int i, j, p;
	p = peso_max; // rappresenta il mio peso rimasto disponibile

				  // x � il mio vettore per la soluzione
	for (i = 0; i < n; i++)
		x[i] = 0.0;

	//Prendo unitariamente
	for (i = 0; i < n; i++) {
		if (peso[i] > p)
			break;
		else {
			x[i] = 1.0;
			tv = tv + valore[i];
			p = p - peso[i];
		}
	}

	//Se sono qui posso prendere solo frazioni
	if (i < n)
		x[i] = p / peso[i];

	tv = tv + (x[i] * valore[i]);

	printf("\nLa scelta risultante e\' la seguente: ");
	for (i = 0; i < n; i++)
		printf("%f\t", x[i]);

	printf("\nIl valore massimo acquisito nello zaino e\':- %f", tv);

}

int main(void) {
	float peso[MAX], valore[MAX], peso_max;
	int num, i, j;
	float frazioni[MAX], temp;

	printf("\nQuanti oggetti sono disponibili? ");
	scanf("%d", &num);

	printf("\nInserire il peso e il valore di ogni oggetto\n");
	for (i = 0; i < num; i++) {
		scanf("%f %f", &peso[i], &valore[i]);
	}

	printf("\nInserire il peso massimo dello zaino: ");
	scanf("%f", &peso_max);

	for (i = 0; i < num; i++) {
		frazioni[i] = valore[i] / peso[i];
	}

	// Ordino in base al rapporto valore/peso --> ordino tutti i vettori
	for (i = 0; i < num; i++) {
		for (j = i + 1; j < num; j++) {
			if (frazioni[i] < frazioni[j]) {
				temp = frazioni[j];
				frazioni[j] = frazioni[i];
				frazioni[i] = temp;

				temp = peso[j];
				peso[j] = peso[i];
				peso[i] = temp;

				temp = valore[j];
				valore[j] = valore[i];
				valore[i] = temp;
			}
		}
	}

	zaino(num, peso, valore, peso_max);

	return(0);
}