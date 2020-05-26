#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# define MAX 20

void zaino_d(int n, int peso[], int valore[], int peso_max) {
	int x[MAX], tv = 0; //valore parziale
	int i, j, p;
	p = peso_max; // rappresenta il mio peso rimasto disponibile

				  // x � il mio vettore per la soluzione
	for (i = 0; i < n; i++)
		x[i] = 0;

	//Prendo unitariamente
	for (i = 0; i < n; i++) {
		if (peso[i] > p)
			break;
		else {
			x[i] = 1;
			tv = tv + valore[i];
			p = p - peso[i];
		}
	}

	printf("\nLa scelta risultante e\' la seguente: ");
	for (i = 0; i < n; i++)
		printf("%d\t", x[i]);

	printf("\nIl valore massimo acquisito nello zaino e\':- %d", tv);

}

int main() {
	int peso[MAX], valore[MAX], peso_max;
	int num, i, j, t;
	float frazioni[MAX], temp;

	printf("\nQuanti oggetti sono disponibili? ");
	scanf("%d", &num);

	printf("\nInserire il peso e il valore di ogni oggetto\n");
	for (i = 0; i < num; i++) {
		scanf("%d %d", &peso[i], &valore[i]);
	}

	printf("\nInserire il peso massimo dello zaino: ");
	scanf("%d\n", &peso_max);

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

				t = peso[j];
				peso[j] = peso[i];
				peso[i] = t;

				t = valore[j];
				valore[j] = valore[i];
				valore[i] = t;
			}
		}
	}

	zaino_d(num, peso, valore, peso_max);

	return(0);
}