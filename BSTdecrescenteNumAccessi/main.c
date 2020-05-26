#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"


int main(void) {
	FILE *f = fopen("internet.txt", "rt");
	if (f == NULL)
		return;

	sito a;
	tree t = emptyTree();

	int n = 0;
	while (1) {
		int letti = fscanf(f, "%s %d", a.nomehost, &a.numeroaccessi);
		if (letti != 2)
			break;
		n++;

		t = insertBinOrd(a, t);
	}

	printf("Visita in DEorder (decrescente): \n");
	inDEOrder(t);

	//seconda parte
	rewind(f);
	tree nt = emptyTree();
	char stringaconfronto[50];
	printf("inserire stringa iniziale da confrontare: ");
	scanf("%s", stringaconfronto);

	n = 0;
	while (1) {
		int letti = fscanf(f, "%s %d", a.nomehost, &a.numeroaccessi);
		if (letti != 2)
			break;
		n++;

		//controllo se le prime lettere sono uguali, se Si la aggiungo al nuovo albero
		if (strncmp(stringaconfronto, a.nomehost, strlen(stringaconfronto)) == 0) {
			nt = insertBinOrd(a, nt);
		}
	}
	
	printf("Vista degli host che iniziano con %s, in ordine decrescente: \n", stringaconfronto);
	inDEOrder(nt);
	return;
}