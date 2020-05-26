#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int element;

typedef struct list_element {
	element value;
	struct list_element *next;
} item;

typedef item* list;

//firme
list emptylist();
list cons(element e, list l);
bool empty(list l);
element head(list l);
list tail(list l);

element getElement();
element copy(element e);
void printElement(element);

void dealloc(list l);
void showlist(list l);
bool contain(list l, element e);
list difference(list l1, list l2);

//primitive
list emptylist() {
	return NULL;
}

list cons(element e, list l) {
	list t;
	t = (list)malloc(sizeof(item));
	t->value = copy(e);
	t->next = l;
	return t;
}

bool empty(list l) {
	return (l == NULL);
}

element head(list l) {
	if (empty(l))
		abort();
	else
		return l->value;
}

list tail(list l) {
	if (empty(l))
		abort();
	else
		return l->next;
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
	printf("%d", el);
}

// DEALLOCAZIONE
void dealloc(list l) {
	list temp;
	while (!empty(l)) {
		temp = l;
		l = tail(l);
		free(temp);
	}
}

// Non primitive

void showlist(list l) {
	printf("[");
	while (!empty(l)) {
		printElement(head(l));
		l = tail(l);
		if (!empty(l))
			printf(", ");
	}
	printf("]\n");
}



// Non utilizza le primitive
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

list difference(list l1, list l2)
{
	element cur;
	list diff = NULL, temp;
	while (l1 != NULL)
	{
		cur = l1->value;
		if (!contain(l2, cur))
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



int main() {

	list l1 = emptylist();
	list l2 = emptylist();
	list l3 = emptylist();
	int el;
	do {
		printf("\n Introdurre valore:\t");
		el = getElement();
		if (el != 0)
			l1 = cons(el, l1);
	} while (el != 0);
	do {
		printf("\n Introdurre valore:\t");
		el = getElement();
		if (el != 0)
			l2 = cons(el, l2);
	} while (el != 0);


	printf("\nEcco la lista 1:\n");
	showlist(l1);
	printf("\nEcco la lista 2:\n");
	showlist(l2);


	l3 = difference(l1, l2);
	showlist(l3);

	dealloc(l1);
	dealloc(l2);
	dealloc(l3);
}