#include "tree.h"

int main(void) {
	FILE *f1 = fopen("siti.txt", "rt");
	FILE *f2 = fopen("valori.txt", "rt");

	if (f1 == NULL)
		return NULL;

	if (f2 == NULL)
		return NULL;

	//albero contenente i siti con NomeHost e NumeroAccesso
	tree t1 = emptyTree();

	//albero contenente SOLO valori numerici
	treeval t2 = emptyTree1();

	//n1 = numero di siti letti correttamente
	sito a;
	int n1 = 0;
	while (1) {
		int letti1 = fscanf(f1, "%s %d", a.nomehost, &a.numeroaccessi);
		if (letti1 != 2)
			break;
		n1++;
		t1 = insertBinOrd(a, t1);
	}

	//n2 = numero di valori letti correttamente
	valore b;
	int n2 = 0;
	while (1) {
		int letti2 = fscanf(f2, "%d", &b.id);
		if (letti2 != 1)
			break;
		n2++;
		t2 = insertBinOrd1(b, t2);
	}

	printf("Vista del primo albero: ");
	visitaInAmpiezza(t1);

	printf("Visita del secondo albero");
	visitaInAmpiezza1(t2);
	return;
}