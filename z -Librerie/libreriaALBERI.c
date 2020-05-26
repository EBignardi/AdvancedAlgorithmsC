#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
////////////////////////////////////////

void showEl(char a);
bool empty(tree t);
tree emptyTree(void);
element root(tree t);
tree left(tree t);
tree right(tree t);
tree consTree(element e, tree l, tree r);
void preOrder(tree t);
void postOrder(tree t);
void inOrder(tree t);
tree succ(tree t);  //cancellazione
tree copy(tree t);
tree delete(tree t, element e);
tree insertBinOrd(element e, tree t);
void contaDominanti(tree t, int *num);

////////////////////////////////////////
typedef  int  element;

typedef struct	treeElement {
	element	value;
	struct treeElement  *left, *right;
} node;

typedef  node *tree;
///////////////////////////////////////

//mostra l elemento dell albero
void showEl(char a) {

	printf("%d", a);
}

//mi dice se lalbero e vuoto
bool empty(tree t) { return (t == NULL); }

//mi restituisce un albero vuoto (per fare confronti)
tree emptyTree(void) { return NULL; }

//restituisce la radice dellalbero
element root(tree t) {
	if (empty(t)) abort();
	else return t->value;
}

//restituisce la foglia sinistra
tree left(tree t) {
	if (empty(t)) return NULL;
	else return t->left;
}

//restituisce la foglia destra
tree right(tree t) {
	if (empty(t)) return NULL;
	else return t->right;
}

//costruisce lalbero data la radice e le due foglie
tree consTree(element e, tree l, tree r) {
	tree t = (node*)malloc(sizeof(node));
	t->value = e;
	t->left = l;	t->right = r;
	return t;
}


// VISITE
//visita in modo ordinato (scendo dalla radice fino alla foglia di sinistra
void preOrder(tree t) {
	if (!empty(t)) {
		printf("\t");
		showEl(root(t));
		preOrder(left(t));
		preOrder(right(t));
	}
}

//leggo le foglie di sinistra e poi la loro radice e continuo con le foglie della seconda radice 
//concludo la lettura con la RADICE
void postOrder(tree t) {
	if (!empty(t)) {
		postOrder(left(t));
		postOrder(right(t));
		printf("\t");
		showEl(root(t));
	}
}

//leggo la foglia di sinistra, la radice, laltra foglia e infine la RADICE, continuo da
//un altro sottoalbero, lultimo elemento letto sara la foglia di destra 
void inOrder(tree t) {
	if (!empty(t)) {
		inOrder(left(t));
		printf("\t");
		showEl(root(t));
		inOrder(right(t));
	}
}

// Per cancellazione
tree succ(tree t) {
	t = right(t);
	if (!empty(t))
		while (!empty(left(t))) {
			t = left(t);
		}
	return t;
}

//copia lalbero
tree copy(tree t) {

	return consTree(root(t), emptyTree(), emptyTree());
}

//elimina un elemento dallalbero
tree delete(tree t, element e) {

	tree l = t, s, next;
	tree pl = NULL, pr = NULL;

	while (root(t) != e && !empty(t)) {
		if (e < root(t)) {
			pl = t;
			pr = emptyTree();
			t = left(t);
		}
		else {
			pl = emptyTree();
			pr = t;
			t = right(t);
		}
	}

	//printf("\ntrovato %d", root(t));
	if (!empty(t)) {

		// Il nodo da eliminare � una foglia
		if (empty(left(t)) && empty(right(t))) {
			// Se e' la root ritorno un albero vuoto
			if (t == l)
				return emptyTree();
			next = emptyTree();

		}
		else {
			// Il nodo da eliminare ha un solo figlio
			if (empty(left(t))) {
				// Se e' la root ritorno il figlio
				if (t == l)
					return right(t);
				next = right(t);
			}
			else {
				if (empty(right(t))) {
					// Se e' la root ritorno il figlio
					if (t == l)
						return left(t);
					next = left(t);
				}
				else {
					// Il nodo da eliminare ha due figli

					pr = t;
					pl = emptyTree();

					next = right(t);
					if (!empty(next))
						while (!empty(left(next))) {
							pr = emptyTree();
							pl = next;
							next = left(next);
						}
					t->value = root(next);
					if (right(next) != NULL) {
						next = right(next);
					}
					else
						next = emptyTree();
				}
			}

		}

		if (!empty(pl))
			pl->left = next;

		if (!empty(pr))
			pr->right = next;
	}

	return l;

}


tree insertBinOrd(element e, tree t) {

	tree l = t;

	if (empty(t))
		return consTree(e, emptyTree(), emptyTree());

	while (!empty(t)) {
		if (e <= root(t)) {
			if (empty(left(t))) {
				t->left = consTree(e, emptyTree(), emptyTree());
				t = left(t);
			}
			t = left(t);
		}
		else {
			if (empty(t->right)) {
				t->right = consTree(e, emptyTree(), emptyTree());
				t = right(t);
			}
			t = right(t);
		}
	}

	return l;
}



void contaDominanti(tree t, int *num) {
	if (!empty(t)) {
		element l = 0, r = 0;

		if (!empty(left(t)))
			l = root(left(t));

		if (!empty(right(t)))
			r = root(right(t));

		if (root(t) >= r + l && r + l > 0) {
			(*num)++;
		}

		contaDominanti(left(t), num);
		contaDominanti(right(t), num);
	}
}
