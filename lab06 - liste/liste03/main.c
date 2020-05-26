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
element maxelement(list l);


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

int main() {

	list l1 = emptylist();
	int el;
	do {
		printf("\n Introdurre valore:\t");
		el = getElement();
		if (el != 0)
			l1 = cons(el, l1);
	} while (el != 0);


	printf("\nEcco la lista:\n");
	showlist(l1);
	printf("\nIl suo elemento massimo:\n");
	printElement(maxelement(l1));

	dealloc(l1);
}