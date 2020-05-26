#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef char stringa[20];

typedef struct {
	stringa nomeArticolo;
	int prezzo;

} element; /* DEFINIZIONE */

typedef int boolean; /* DEFINIZIONE */

typedef struct list_element {
	element e;
	struct list_element *next;
} articolo;

typedef articolo *list;


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

list cons(stringa s, int p, list l) {
	list t;
	t = (list)malloc(sizeof(articolo));
	strcpy(t->e.nomeArticolo, s);
	t->e.prezzo = p;
	t->next = l;
	return t;
}


element head(list l) {
	if (empty(l)) abort();
	else
		return l->e;
}


void printElement(element el) {
	printf("\n %s %d", el.nomeArticolo, el.prezzo);
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



void main(void) {
	FILE *file;
	char nomeArticolo[20];
	int prezzo;
	list lista = emptylist();
	int i = 0;
	element e;

	file = fopen("magazzino.txt", "r");

	while (!feof(file))
	{
		fscanf(file, "%s", e.nomeArticolo);
		fscanf(file, "%d", &e.prezzo);

		// inserisci Elemento InCoda
		//lista = inserisciElementoInCoda(e, lista);
		// inserisci Elemento In Testa
		//lista = cons(e.nomeArticolo, e.prezzo, lista);
		// inserisci Elemento Ordinato rispetto al nome
		lista = inserisciOrdinato(e, lista);
		i++;
	}

	showlist(lista);



	printf("Inserisci il prezzo minimo: ");
	fscanf(stdin, "%d", &prezzo);

	printf("Cerco i prezzo maggiori di: %d\n", prezzo);

	showMaggiori(lista, prezzo);

	CercaCoppie(lista, 20);

}