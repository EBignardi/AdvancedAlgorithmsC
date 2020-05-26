#include "tree.h"
void costrisci_albero(tree a, tree *b, int somma)
{
	if (a == NULL) // passo base
	{
		return;
	}

	if (a->left == NULL && a->right == NULL) // se è una foglia, controlla il livello del percorso
	{
		somma += a->value.livello;
		if (somma <= 7) // invece di eliminare, viene semplicemnte non aggiunto al BST
			return;
		else
		{
			b[0] = insert(a->value, b[0]);
		}
	}
	else // se non è una foglia, aggiungi il livello e poi itera a Sx e Dx
	{
		b[0] = insert(a->value, b[0]);
		somma += a->value.livello;
		costrisci_albero(left(a), b, somma);
		costrisci_albero(right(a), b, somma);
	}
	return;
}


int main()
{

	char nomefile[50];
	scanf("%s", nomefile);
	FILE *f = fopen(nomefile, "rt");
	if (f == NULL)
		printf("errore lettura file");

	// lettura da file e creazione 1° BST
	elementTree p;
	tree t = NULL;
	while (fscanf(f, "%s%s%s%d", &p.cognome, &p.nome, &p.materia, &p.livello) == 4)
	{
		t = insert(p, t);
	}

	// creazione 2° BST
	tree n = NULL;
	costrisci_albero(t, &n, 0); // passaggio del secondo albero per riferimento e non per copia

	// Output
	printf("visita in pre ordine dell'albero t: \n");
	preOrder(t);
	printf("\n \n");
	printf("visita in post ordine dell'albero n: \n");
	postOrder(n);


	return 0;

}