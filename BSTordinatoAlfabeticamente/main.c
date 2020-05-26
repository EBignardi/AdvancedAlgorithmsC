#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

void insVec(professore a, int*v, int *c, int min, int max) {
	if (a.id >= min && a.id <= max) {
		int k = *c;
		v[k] = a.id;
		(*c)++;
	}
}

void preOrder3(tree t, int min, int max, int *c, int v[]) {
	if (!empty(t)) {
		printf("\t");
		insVec(root(t), v, c, min, max);
		preOrder3(left(t), min, max, c, v);
		preOrder3(right(t), min, max, c, v);
	}

}

void insVec2(professore a, int*c, int v[]) {
	int k = *c;
	v[k] = a.id;
	(*c)++;
}

void postOrder3(tree t, int *c, int v[]) {
	if (!empty(t)) {
		postOrder3(left(t), c, v);
		postOrder3(right(t), c, v);
		printf("\t");
		insVec2(root(t), c, v);
	}
}


void funz(tree1 t1, int v[], int j, int n) {
	if (j == n)
		return;
	if (t1->left == NULL && t1->right == NULL) {
		tree1 tmp = consTree1(v[j], emptyTree1(), emptyTree1());
		if (v[j] > root1(t1)) {
			t1->right = tmp;
			funz(t1->right, v, j + 1, n);
		}
		else {
			t1->left = tmp;
			funz(t1->left, v, j + 1, n);
		}
	}
	else {
		if (t1->left == NULL)
			funz(t1->right, v, j, n);
		else
			funz(t1->left, v, j, n);
	}
	return;
}

void contaFoglie(tree1 t, int *n) {
	if (!empty1(t)) {
		printf("\t");
		if (left1(t) == NULL && right1(t) == NULL)
			(*n)++;
		contaFoglie(left1(t), n);
		contaFoglie(right1(t), n);
	}
}





int main(void) {
	FILE *f = fopen("prova.txt", "rt");
	if (f == NULL)
		return;

	professore a;
	tree t = emptyTree();

	int n = 0;
	while (1) {
		int letti = fscanf(f, "%s %s %d %d", a.cognome, a.nome, &a.eta, &a.id);
		if (letti != 4)
			break;
		n++;
		t = insOrdTree(a, t);
	}

	preOrder(t);

	int min = 30, max = 110;
	//scanf("%d %d", &min, &max);
	tree1 t1 = emptyTree1();

	int c = 0;

	int *v = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		v[i] = -1;

	//metto in un vettore i dati in ordine richiesto
	preOrder3(t, min, max, &c, v);

	int h = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] != -1)
			h++;
	}
	int l = n;
	n = h;
	//devo inserire i dati in t1
	int j = 0;
	if (v[j] != -1) {
		t1 = insOrdTree1(v[j], t1);
		j++;
		if (v[j] != -1)
			funz(t1, v, j, n);
	}

	printf("\n\n\n\n lista finale = \n ");
	preOrder1(t1);

	int altezzaT1 = height1(t1);
	printf("\nL'altezza di t2 e' = %d (tenendo conto che l altezza della radice dell albero vale 0)", altezzaT1);

	printf("\n\nora parte 2 dell esercizio!\n\n");
	n = l;
	int *p = malloc(n * sizeof(int));
	c = 0;
	postOrder3(t, &c, p);
	tree1 t2 = emptyTree1();
	j = 0;
	t2 = insOrdTree1(p[j], t2);
	j++;
	if (p[j] != -1)
		funz(t2, p, j, n);


	printf("\nlista t2 in post order = \n");
	postOrder1(t2);
	int altezzaT2 = height1(t2);
	printf("\nL'altezza di t2 e' = %d (tenendo conto che l altezza della radice dell albero vale 0)", altezzaT2);

	int nFoglie = 0;
	contaFoglie(t2, &nFoglie);

	printf("il numero di foglie di t2 e' = %d", nFoglie);

	fclose(f);


	return;
}



