#if !defined ALBERI_H
#define ALBERI_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct professore {
	char cognome[20];
	char nome[20];
	int eta;
	int id;
}professore;

typedef struct item {
	professore value;
	struct item *left, *right;
} node;

typedef node *tree;

/*	CONFRONTI E FUNZIONI DI APPOGGIO 	*/
bool isEqual(professore e1, professore e2);
bool isLess(professore e1, professore e2);
professore copy(professore e);
void showEl(professore e);
professore getEl();
int height(tree t); //calcola l'altezza di un albero

/*	PRIMITIVE 	*/
bool empty(tree t);
tree emptyTree(void);
professore root(tree t);
tree left(tree t);
tree right(tree t);
tree consTree(professore e, tree l, tree r);

/*	 VISITE		*/
void preOrder(tree t);
void inOrder(tree t);
void postOrder(tree t);
void stampalvl(tree t, size_t lvl); //funzione che serve per visitaInAmpiezza
void visitaInAmpiezza(tree t);

/*	 SECONDARIE	*/
bool memberTree(professore e, tree t);
tree createTree(void); //crea un albero in pre order

/*	 ALBERI BST */
tree CreaAlberoBST(); //inserimento albero da input
tree insOrdTree(professore e, tree t); //costruttore per alberi BST
bool memberTreeOrd(professore e, tree t);
tree delete(tree t, professore e); //delete di un elemento completa con tutti i casi
tree insertBinOrd(professore e, tree t);

typedef int element;

typedef struct item1 {
	element value;
	struct item1 *left, *right;
} node1;

typedef node1 *tree1;


/*	CONFRONTI E FUNZIONI DI APPOGGIO 	*/
bool isEqual1(element e1, element e2);
bool isLess1(element e1, element e2);
element copy1(element e);
void showEl1(element e);
element getEl1();
int height1(tree1 t); //calcola l'altezza di un albero

					  /*	PRIMITIVE 	*/
bool empty1(tree1 t);
tree1 emptyTree1(void);
element root1(tree1 t);
tree1 left1(tree1 t);
tree1 right1(tree1 t);
tree1 consTree1(element e, tree1 l, tree1 r);

/*	 VISITE		*/
void preOrder1(tree1 t);
void inOrder1(tree1 t);
void postOrder1(tree1 t);
void stampalvl1(tree1 t, size_t lvl); //funzione che serve per visitaInAmpiezza
void visitaInAmpiezza1(tree1 t);

/*	 SECONDARIE	*/
bool memberTree1(element e, tree1 t);
tree1 createTree1(void); //crea un albero in pre order

						 /*	    ALBERI BST		*/
tree1 CreaAlberoBST1(); //inserimento albero da input
tree1 insOrdTree1(element e, tree1 t1); //costruttore per alberi BST
bool memberTreeOrd1(element e, tree1 t1);
tree1 delete1(tree t1, element e); //delete di un elemento completa con tutti i casi
tree1 insertBinOrd1(element e, tree1 t1);
#endif