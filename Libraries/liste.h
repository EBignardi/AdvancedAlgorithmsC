#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int element;
typedef int boolean;
typedef struct list_element {
	element value;
	struct list_element *next;
} item;
typedef item* list;

/* ---- PRIMITIVE ---- */
list    emptylist();
boolean    empty(list);
element head(list);
list    tail(list);
list    cons(element, list);
/* ---- NON PRIMITIVE ---- */
void    showlist(list);
boolean isLess(element, element);
boolean isEqual(element, element);
element copy(element e);
element getElement(void);
void    printElement(element);
boolean member(element, list);
int lenght(list);
list append(list, list);
list copylist(list);
list delete (element, list);
void  InserisciCodaLista(list*, element);
list deletemin(element, list);
list deletemax(element, list);
list insord(element, list);
list inscoda(element, list);
list intersect(list , list );
list inverti(list );
list ordina(list );