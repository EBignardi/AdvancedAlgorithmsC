#include <stdio.h>
#include <stdlib.h>

typedef int element; /* DEFINIZIONE */
typedef int boolean; /* DEFINIZIONE */

typedef struct list_element {
element value;
struct list_element *next;
struct list_element *prev;
} item;


typedef item* list;

boolean isLess(element, element);
boolean isEqual(element, element);
element copy(element e);
element getElement(void);

void printElement(element);

/* ---- PRIMITIVE ---- */
list emptylist(void);
boolean empty(list);
element head(list);
list tail(list);
list cons(element, list);

/* ---- NON PRIMITIVE ---- */
void showlist(list);


boolean isEqual(element e1,element e2) {
	return (e1 == e2);
}

boolean isLess(element e1, element e2) {

	printf("\nVerifico da %d %d", e1, e2);
	if (e1 < e2) {
		printf("\nTorno 1");
		return 1;
	}
	else {
		printf("\nTorno 0");
		return 0;
	}
}

element copy(element e){
	element el;
	el=e;
	return el;
}

element getElement(){
	element el;
	scanf("%d", &el);
	return el;
}

void printElement(element el){
	printf("%d", el);
}

list emptylist() {
	return NULL;
}


boolean empty(list l) {
	return (l==NULL);
}

element head(list l) {
	if (empty(l)) abort();
	else
		return l->value;
}

list tail(list l) {
	if (empty(l)) abort();
	else
		return l->next;
}

list cons(element e, list l) {
	list t;
	t = (list) malloc(sizeof(item));
	t->value=copy(e);
	t->next=l;
	if(!empty(l))
		l->prev=t;
	return t;
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

list InsertCliente(element e, list l){
	list l1 = NULL, root = l;
	list t;
	t = cons(e, emptylist());
	if(empty(l)){
		return t;
	}
	while(!empty(l->next)){
	l = tail(l);
	}
	l->next = t;
	t->prev = l;
	return root;
}

list InsertOrdinato(element e, list l){
	list l1 = NULL, root = l;
	list t;
	t = cons(e, emptylist());
	if(empty(l)){
		return t;
	}
	if(!isLess(head(l),e)){
		t->next = l;
		l->prev = t;
		return t;
	}


	while(!empty(l) && isLess(head(l),e)){
		l = tail(l);
	}

	l1=l->prev;
	l1->next = t;
	t->next = l;
	return root;
}



void main(void) {
list l = emptylist();
int el;
int scelta;
char invio;
do {
	printf("\n\nMenu' Principale - CODA FIFO\n\nScegli l'operazione da eseguire: \n");
	printf("1. Inserisci cliente in coda\n");
	printf("2. Visualizza tutta la coda \n");
	printf("3. Visualizza il prossimo cliente\n");
	printf("4. Servi il prossimo cliente\n");
	printf("5. Inserisci in modo ordinato\n");
	printf("0. Termina il programma\n");
	// acquisizione scelta utente
	scanf("%d", &scelta);
	scanf("%c", &invio);
	// interpretazione scelta ed esecuzione della relativa operazione
	switch (scelta) {
		case 0:
			printf("Uscita dal programma\n");
			break;
		case 1:
			printf("Inserire il numero del cliente: ");
			el=getElement();
			l = InsertCliente(el,l);
			break;
		case 2:
			showlist(l);
			break;
		case 3:
			printf("\nIl prossimo cliente e': %d", head(l));
			break;
		case 4:
			l = tail(l);
			printf("Coda rimasta:");
			showlist(l);
		break;
			case 5:
			printf("Inserire il numero del cliente: ");
			el=getElement();
			l = InsertOrdinato(el,l);
			printf("Coda attuale:");
			showlist(l);
			break;
		default:
			printf("la scelta non e' corretta, inserirne un'altra\n");
	}
	} while(scelta != 0);
}
