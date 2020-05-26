#include "tree.h"

void showelementTree(elementTree a) {
	//INSERIRE A SECONDA DI ELEMENTTREE
	printf("\n %s, %s, %s, %d", a.nome, a.cognome, a.materia, a.livello);
}

bool isLess(elementTree a, elementTree b) {

	//INSERIRE A SECONDA DI ELEMENTTREE
	if (strcmp(a.materia, b.materia) < 0)
		return true;

	if (strcmp(a.materia, b.materia) > 0)
		return false;

	if (strcmp(a.materia, b.materia) == 0) {
		if (strcmp(a.cognome, b.cognome) < 0)
			return true;
		else
			return false;
	}
	return false;
}

bool isEqual(elementTree a, elementTree b) {

	//INSERIRE A SECONDA DI ELEMENTTREE
	if ((strcmp(a.materia, b.materia) == 0) && (strcmp(a.cognome, b.cognome) == 0))
		return true;
	else
		return false;
}

//PRIMITIVE
bool empty(tree t) { return (t == NULL); }

tree emptyTree(void) { return NULL; }

elementTree root(tree t) {
	if (empty(t)) abort();
	else return t->value;
}

tree left(tree t) {
	if (empty(t)) return NULL;
	else return t->left;
}

tree right(tree t) {
	if (empty(t)) return NULL;
	else return t->right;
}

tree consTree(elementTree e, tree l, tree r) {
	tree t = (node*)malloc(sizeof(node));
	t->value = e;
	t->left = l;    t->right = r;
	return t;
}

tree insert(elementTree el, tree t) {  //Si inserisce un intero el, nell'albero t

	if (empty(t)) {  //Se l'albero è vuoto, allora verrà creata una foglia
		return consTree(el, NULL, NULL);
	}

	if (isLess(el, t->value) == true || isEqual(el, t->value) == true) {  //Altrimenti si procede da direttive, ovvero se il valore della radice è >= dell'elemento
		return consTree(t->value, insert(el, left(t)), right(t));  //Andrà a sinistra
	}

	if (isLess(t->value, el) == true) {  //Ae la radice è invece minore dell'elemento, verrà inserita a destra.
		return consTree(t->value, left(t), insert(el, right(t)));
	}
	else {
		return t;
	}
}

//ESPLORAZIONE
void preOrder(tree t) {
	if (!empty(t)) {
		printf("\t"); showelementTree(root(t));
		preOrder(left(t)); preOrder(right(t));
	}
}
void preOrderes2(tree t) {
	if (!empty(t)) {

		preOrder(left(t)); preOrder(right(t));
	}
}
void inOrder(tree t) {
	if (!empty(t)) {
		inOrder(left(t));
		printf("\t"); showelementTree(root(t));
		inOrder(right(t));
	}
}

void postOrder(tree t) {
	if (!empty(t)) {
		postOrder(left(t)); postOrder(right(t));
		printf("\t"); showelementTree(root(t));
	}
}










void showelementTree2(int a) {
	//INSERIRE A SECONDA DI ELEMENTTREE
	printf("\nID: %d\n", a);
}

bool isLess2(int a, int b) {

	//INSERIRE A SECONDA DI ELEMENTTREE
	if (a < b)
		return true;

	if (a >= b)
		return false;
	return false;
}

bool isEqual2(int a, int b) {

	//INSERIRE A SECONDA DI ELEMENTTREE
	if (a == b)
		return true;
	else
		return false;
}

//PRIMITIVE
bool empty2(tree2 t) { return (t == NULL); }

tree2 emptyTree2(void) { return NULL; }

int root2(tree2 t) {
	if (empty2(t)) abort();
	else return t->value;
}

tree2 left2(tree2 t) {
	if (empty2(t)) return NULL;
	else return t->left;
}

tree2 right2(tree2 t) {
	if (empty2(t)) return NULL;
	else return t->right;
}

tree2 consTree2(int e, tree2 l, tree2 r) {
	tree2 t = (node2*)malloc(sizeof(node2));
	t->value = e;
	t->left = l;    t->right = r;
	return t;
}

tree2 insert2(int el, tree2 t) {  //Si inserisce un intero el, nell'albero t

	if (empty2(t)) {  //Se l'albero è vuoto, allora verrà creata una foglia
		return consTree2(el, NULL, NULL);
	}

	if (isLess2(el, t->value) == true || isEqual2(el, t->value) == true) {  //Altrimenti si procede da direttive, ovvero se il valore della radice è >= dell'elemento
		return consTree2(t->value, insert2(el, left2(t)), right2(t));  //Andrà a sinistra
	}

	if (isLess2(t->value, el) == true) {  //Ae la radice è invece minore dell'elemento, verrà inserita a destra.
		return consTree2(t->value, left2(t), insert2(el, right2(t)));
	}
	else {
		return t;
	}
}

//ESPLORAZIONE
void preOrder2(tree2 t) {
	if (!empty2(t)) {
		printf("\t"); showelementTree2(root2(t));
		preOrder2(left2(t)); preOrder2(right2(t));
	}
}

void inOrder2(tree2 t) {
	if (!empty2(t)) {
		inOrder2(left2(t));
		printf("\t"); showelementTree2(root2(t));
		inOrder2(right2(t));
	}
}