#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

////////////////////////////////////////////////////

boolean isEqual(element e1, element e2);
boolean isLess(element e1, element e2);
list emptylist();
boolean empty(list l);
list tail(list l);
list cons(stringa s, int p, list l); // list cons(element e, list l)
element head(list l);
element getElement();
element copy(element e);
void printElement(element el);
void showlist(list l);
void dealloc(list l);
void showMaggiori(list l, int prezzo);
bool contain(list l, element e);
void CercaCoppie(list l, int somma);
list inserisciElementoInCoda(element e, list l);
list inserisciOrdinato(element e, list l);
list difference(list l1, list l2);  // lista contenente valori differenti tra le due TAB
element maxelement(list l);
list insertBack(element e, list l);
element	*cercaOggetto(const char* nome, const list lista);
void showListConditional(const list l, double N);
bool elementExists(const list l, const element* e);
indirizzo *sort(indirizzo *start);
indirizzo *list_switch(indirizzo *l1, indirizzo *l2);
////////////////////////////////////////////////////
			//LISTA COMUNE
typedef int element;

typedef struct list_element {
	element value;
	struct list_element *next;
} item;

typedef item* list;

////////////////////////////////////////////////////
			//LISTA CON STRINGA
typedef char stringa[20];

typedef struct {
	stringa nomeArticolo;
	int prezzo;

} element; /* DEFINIZIONE */

typedef struct list_element {
	element e;
	struct list_element *next;
} articolo;

typedef articolo *list;
//////////////////////////////////////////////////
			
/* Struttura dati indirizzo */
typedef struct indirizzo {
	char nome[40];
	char via[50];
	int numero;
	char citta[30];
	char provincia[3];
	char cap[6];
	struct indirizzo* prossimo;
}indirizzo;
//////////////////////////////////////////////////

boolean isEqual(element e1, element e2) {
	if (strcmp(e1.nomeArticolo, e2.nomeArticolo) == 0)
		return 1;
	else
		return 0;
}

boolean isLess(element e1, element e2) {
	if ((strcmp(e1.nomeArticolo, e2.nomeArticolo)<0)) {
		return 1;
	}
	else {
		return 0;
	}
}

list emptylist() {
	return NULL;
}

boolean empty(list l) {
	return (l == NULL);
}

list tail(list l) {
	if (empty(l))
		abort();
	else
		return l->next;
}

list cons(stringa s, int p, list l) {			//list cons(element e, list l) {
	list t;										//list t;
	t = (list)malloc(sizeof(articolo));			//t = (list)malloc(sizeof(item));
	strcpy(t->e.nomeArticolo, s);				//t->value = copy(e);
	t->e.prezzo = p;							//t->next = l;
	t->next = l;								//return t;
	return t;									//}
}												//

element head(list l) {
	if (empty(l)) abort();
	else
		return l->e;
}

element getElement() {
	element el;
	scanf("%d", &el);
	return el;
}

element copy(element e) {
	element el;
	el = e;
	return el;
}

void printElement(element el) {
	printf("\n%s %d", el.nomeArticolo, el.prezzo);
}

void showlist(list l) {
	printf("[");

	while (!empty(l)) {
		printElement(head(l));
		l = tail(l);
		if (!empty(l)) printf(", ");
	}
	printf("]\n");
}

void dealloc(list l) {
	list temp;
	while (!empty(l)) {
		temp = l;
		l = tail(l);
		free(temp);
	}
}

void showMaggiori(list l, int prezzo) {
	printf("[");

	while (!empty(l)) {
		if (head(l).prezzo > prezzo) {
			printElement(head(l));
		}
		l = tail(l);
	}
	printf("]\n");
}

bool contain(list l, element e)
{
	bool found = false;
	while (l != NULL && !found)
	{
		found = (l->value == e);
		l = l->next;
	}
	return found;
}

void CercaCoppie(list l, int somma) {

	element e1, e2;
	list l1 = l;
	printf("[");

	while (!empty(l)) {
		e1 = head(l);
		l1 = tail(l);
		while (!empty(l1)) {
			e2 = head(l1);
			if (e1.prezzo + e2.prezzo == somma) {
				printf("\nCoppia: ");
				printElement(e1);

				printElement(e2);
			}
			l1 = tail(l1);
		}
		l = tail(l);
	}
}

list inserisciElementoInCoda(element e, list l) {

	list l1 = NULL, root = l;
	list t;

	if (empty(l)) {
		t = cons(e.nomeArticolo, e.prezzo, l);
		return t;
	}

	t = cons(e.nomeArticolo, e.prezzo, NULL);

	while (!empty(l)) {
		l1 = l;
		l = tail(l);
	}

	l1->next = t;
	t->next = l;

	return root;
}

list inserisciOrdinato(element e, list l) {

	list l1 = emptylist(), root = l;
	list t;

	t = cons(e.nomeArticolo, e.prezzo, l);

	if (empty(l) || !isLess(head(l), e)) {
		return t;
	}

	while (!empty(l) && isLess(head(l), e)) {
		l1 = l;
		l = tail(l);
	}

	l1->next = t;
	t->next = l;

	return root;

}

list difference(list l1, list l2)
{
	element cur;
	list diff = NULL, temp;
	while (l1 != NULL)
	{
		cur = l1->value;
		if (!contain(l2, cur))   //no ripetizioni:	if (member(cur, l2) && !member(cur, intersection))
		{
			temp = (list)malloc(sizeof(item));
			temp->value = cur;
			temp->next = diff;
			diff = temp;
		}
		l1 = l1->next;
	}
	return diff;
}

element maxelement(list l)
{
	element max = l->value;
	while (!(l == NULL))
	{
		if (l->value > max)
			max = l->value;
		l = l->next;
	}
	return max;
}

list insertBack(element e, list l) {

	if (empty(l)) {
		return cons(e, l);
	}

	list root = l, temp = 0;

	while (!empty(l)) {
		temp = l;
		l = l->next;
	}

	temp->next = cons(e, l);

	return root;
}

// Cerca un oggetto di cui � noto il nome nella lista specificata
element* cercaOggetto(const char* nome, const list lista) {

	for (list i = lista; i != NULL; i = i->next) {
		if (strcmp(nome, i->value.nome) == 0) {
			return &(i->value);
		}
	}
	return NULL; // Non trovato
}

//Visualizza tutti gli oggetti nel carrello con quantit� maggiore di N
void showListConditional(const list l, double N) {
	printf("[");
	bool start = true;
	for (list i = l; i != NULL; i = i->next) {
		if (i->value.qta > N) {
			if (!start) {
				printf(", ");
			}
			printElement(i->value);
			start = false;
		}
	}
	printf("]\n");
	return;
}

bool elementExists(const list l, const element* e) {

	for (list i = l; i != NULL; i = i->next) {
		if (strcmp(e->nome, i->value.nome) == 0) {
			return true;
		}
	}
	return false; // Non trovato
}

//ordina la lista di indirizzi
indirizzo *sort(indirizzo *start)
{
	if (start == NULL) return NULL;
	/* First push the larger items down
	if (start->prossimo != NULL && strcmp(start->nome, start->prossimo->nome)>0)
	start = list_switch(start, start->prossimo);
	/* Always sort from second item on */
	start->prossimo = sort(start->prossimo);
	/* bubble smaller items up */
	if (start->prossimo != NULL && strcmp(start->nome, start->prossimo->nome)>0) {
		start = list_switch(start, start->prossimo);
		start->prossimo = sort(start->prossimo);
	}
	return start;
}

// Scambio i due elementi
indirizzo *list_switch(indirizzo *l1, indirizzo *l2)
{
	l1->prossimo = l2->prossimo;
	l2->prossimo = l1;
	return l2;
}