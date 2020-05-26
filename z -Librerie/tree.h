#if !defined ALBERI_H
#define ALBERI_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct sito {
	char nomehost[50];
	int numeroaccessi;
}sito;

typedef struct item {
	sito value;
	struct item *left, *right;
} node;
typedef node *tree;

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
tree createTree(void); //crea un albero in pre order
tree trova_padre(tree t, sito e); 
bool diversi(sito e1, sito e2);

/* INSERIMENTI */
tree insertBinOrd(sito e, tree t); //Inserisce l elemento confrontando con un parametro di e
tree CreaAlberoBST();  //crea un albero prendendo valori da stdinput
tree BSTread(FILE *f); // costruisce un albero leggendo i dati da un file aperto passato

/*  ALBERI BST	*/
tree insOrdTree(sito e, tree t); //costruttore per alberi BST
bool memberTreeOrd(sito e, tree t);
tree delete(tree t, sito e); //delete di un elemento completa con tutti i casi


typedef int element;
#endif