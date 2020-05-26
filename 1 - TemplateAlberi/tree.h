#if !defined ALBERI_H
#define ALBERI_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* ------- DEFINIZIONI -------- */

typedef int element;

//definizione nel caso di più dati
typedef struct sito {
	char nomehost[50];
	int numeroaccessi;
}sito;

typedef struct item {
	sito value;
	struct item *left, *right;
} node;

typedef node *tree;

//definizione nel caso di un singolo valore
typedef struct valore {
	int id;
}valore;

typedef struct itemval {
	valore val;
	struct itemval *left, *right;
} nodeval;

typedef nodeval *treeval;
/*------------------------------*/

/*	CONFRONTI E FUNZIONI DI APPOGGIO */
bool isEqual(sito e1, sito e2);
bool isLess(sito e1, sito e2);
sito copy(sito e);
void showEl(sito e);
sito getEl();
int height(tree t); //calcola l'altezza di un albero

/*	PRIMITIVE 	*/
bool empty(tree t);
tree emptyTree(void);
sito root(tree t);
tree left(tree t);
tree right(tree t);
tree consTree(sito e, tree l, tree r);

/*	 VISITE		*/
void preOrder(tree t);
void inOrder(tree t);
void postOrder(tree t);
void stampalvl(tree t, size_t lvl); //funzione che serve per visitaInAmpiezza
void visitaInAmpiezza(tree t);

/*	 SECONDARIE	*/
bool memberTree(sito e, tree t);
tree createTree(void); //crea un albero in pre-order
tree trova_padre(tree t, sito e);
bool diversi(sito e1, sito e2);

/* INSERIMENTI */
tree insertBinOrd(sito e, tree t); //INSERISCE l elemento confrontando con un parametro di e
tree CreaAlberoBST();  //crea un albero prendendo valori da STDINPUT
tree BSTread(FILE *f); // costruisce un albero leggendo i dati da un FILE aperto passato

/*  ALBERI BST	*/
tree insOrdTree(sito e, tree t); //costruttore per alberi BST
bool memberTreeOrd(sito e, tree t);
tree delete(tree t, sito e); //delete di un elemento completa con tutti i casi

/////////////////////////////////////////////////////////////////////////////////////////////////
/*					                  PER VALORE SINGOLO                                       */
/////////////////////////////////////////////////////////////////////////////////////////////////
/*	PRIMITIVE 	*/
bool empty1(treeval t);
treeval emptyTree1(void);
valore root1(treeval t);
treeval left1(treeval t);
treeval right1(treeval t);
treeval consTree1(valore e, treeval l, treeval r);

/*	 VISITE		*/
void preOrder1(treeval t);
void inOrder1(treeval t);
void postOrder1(treeval t);
void stampalvl1(treeval t, size_t lvl); //funzione che serve per visitaInAmpiezza
void visitaInAmpiezza1(treeval t);

/*	 SECONDARIE	*/
bool memberTree1(valore e, treeval t);
treeval createTree1(void); //crea un albero in pre-order
treeval trova_padre1(treeval t, valore e);
bool diversi1(valore e1, valore e2);

/* INSERIMENTI */
treeval insertBinOrd1(valore e, treeval t); //INSERISCE l elemento confrontando con un parametro di e
treeval CreaAlberoBST1();  //crea un albero prendendo valori da STDINPUT
treeval BSTread1(FILE *f); // costruisce un albero leggendo i dati da un FILE aperto passato

/*  ALBERI BST	*/
treeval insOrdTree1(valore e, treeval t); //costruttore per alberi BST
bool memberTreeOrd1(valore e, treeval t);
treeval delete1(treeval t, valore e); //delete di un elemento completa con tutti i casi
void contaDominanti1(treeval t, int *num); //il valore della radice deve essere maggiore della somma del figlio destro e sinistro
#endif