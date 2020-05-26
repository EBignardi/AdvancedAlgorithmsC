#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

list emptylist() { return NULL; }

boolean empty(list l) { return (l == NULL); }

element head(list l) {
	if (empty(l)) abort();
	else return  l->value;
}

list tail(list l) {
	if (empty(l)) abort();
	else return l->next;
}

list  cons(element e, list l) {
	list t;
	t = (list)malloc(sizeof(item));
	t->value = copy(e);
	t->next = l;
	return t;
}

boolean isEqual(element e1, element e2) {
	return (e1 == e2);
}

boolean isLess(element e1, element e2) {
	return (e1 < e2);
}

element copy(element e) {
	element el;
	el = e;
	return el;
}

element getElement() {
	element el;
	scanf("%d", &el);
	return el;
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

void printElement(element el) {
	printf("%d", el);
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

void showMaggiori(list l, int valore) {
	printf("[");

	while (!empty(l)) {
		if (head(l).value > valore) {
			printElement(head(l));
		}
		l = tail(l);
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

//cerca coppie di elementi che danno il risultato desiderato
void CercaCoppie(list l, int somma) {

	element e1, e2;
	list l1 = l;
	printf("[");

	while (!empty(l)) {
		e1 = head(l);
		l1 = tail(l);
		while (!empty(l1)) {
			e2 = head(l1);
			if (e1.value + e2.value == somma) {
				printf("\nCoppia: ");
				printElement(e1);

				printElement(e2);
			}
			l1 = tail(l1);
		}
		l = tail(l);
	}
}

//restituisce vero se l'elemento è presente nella lista
boolean member(element el, list l) {
	if (empty(l)) return 0;
	else
		if (isEqual(el, head(l))) return 1;
		else return member(el, tail(l));
}

//restituisce la lunghezza della lista
int length(list l) {
	if (empty(l)) return 0;
	else return 1 + length(tail(l));
}

//unisce due liste
list append(list l1, list l2) {
	if (empty(l1)) return l2;
	else
		return cons(head(l1), append(tail(l1), l2));
}

//copia una lista
list copylist(list l) {
	if (empty(l)) return l;
	else return cons(head(l), copylist(tail(l)));
}

//elimina un elemento di una lista
list delete(element el, list l) {
	if (empty(l)) return emptylist();
	else
		if (isEqual(el, head(l))) return tail(l);
		else
			return cons(head(l), delete(el, tail(l)));
}

//inserisci in coda un elemento
void InserisciCodaLista(list *l, element elem)
/* Versione iterativa. */
{
	list paux;
	paux = malloc(sizeof(item));
	paux->value = elem;
	paux->next = NULL;
	*l = append(*l, paux);
}

//elimina tutti i valori della lista inferiori a el
list deletemin(element el, list l) {
	if (empty(l)) return emptylist();
	else
		if (isLess(head(l), el)) {
			l = delete(head(l), l);
			l = deletemin(el, l);
		}

	return cons(head(l), deletemin(el, tail(l)));
}

//elimina tutti gli elementi della lista superiori a el
list deletemax(element el, list l) {
	if (empty(l)) return emptylist();
	else
		if (!isEqual(el, head(l)) && !isLess(head(l), el)) {
			l = delete(head(l), l);
			l = deletemax(el, l);
			if (empty(l))
				return l;
		}
	return cons(head(l), deletemax(el, tail(l)));
}

//testa maggiore dell'elemento = inserisci (ordine CRESCENTE)
//la testa sara sempre l elemento MINORE
list insord(element e, list l) { 
	list t;
	if (empty(l) || isLess(e, head(l))) {
		t = cons(e, l);
		//t->next = l;
		return t;
	}
	return cons(head(l), insord(e, tail(l)));
}

//inserisco l elemento passato SEMPRE per ultimo (in coda)
list inscoda(element e, list l) {
	list a = l, t;
	t = malloc(sizeof(item));
	t->value = e;
	t->next = NULL;
	if (empty(l) == 1) return t;
	while (empty(tail(l)) != 1) {
		l = tail(l);
	}
	l->next = t;
	return a;
}

//costruisce la lista INTERSEZIONE date due liste (con ripetizioni)
list intersect(list l1, list l2) {
	element cur;
	list intersection = emptylist();
	while (!empty(l1)) {
		cur = head(l1);
		if (member(cur, l2))					//no ripetizioni:	if (member(cur, l2) && !member(cur, intersection))
			intersection = cons(cur, intersection);
		l1 = tail(l1);
	}
	return intersection;
}

//restituisce la lista contenente gli elementi differenti tra le 2 liste
list difference(list l1, list l2)
{
	element cur;
	list diff = NULL, temp;
	while (l1 != NULL)
	{
		cur = l1->value;
		if (!contain(l2, cur))				  //no ripetizioni:	if (member(cur, l2) && !member(cur, intersection))
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

//restituisce una lista al contrario
list inverti(list l) {
	if (empty(l)) return l;
	return inscoda(head(l), inverti(tail(l)));
}

//la funzione ordina in modo decrescente (per il crescente invertire gli elementi di isless)
list ordina(list l)
{
	bool flag = true;
	while (flag)
	{
		list p = l;
		flag = false;
		while (p->next != NULL)
		{
			if (isLess(head(p), head(tail(p))))
			{
				element tmp = p->value;
				p->value = (p->next)->value;
				(p->next)->value = tmp;
				flag = true;
			}
			p = tail(p);
		}
	}
	return l;
}
