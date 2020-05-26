#include <stdio.h>
#include <stdlib.h>

typedef int element; /* DEFINIZIONE */
typedef int boolean; /* DEFINIZIONE */

typedef struct list_element {
element value;
struct list_element *next;
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
return (e1 < e2);
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


list seekDestroyNoRestart(list l, int k) {

	list t=l, f=t, s = emptylist();
	int i, val=0;

	val=0;
	while(!empty(f)){
		while(!empty(f) && val < k){
			val += head(f);
			f = tail(f);
		}
		if(val == k){
	        if(empty(s))
				return f;
			else{
			    s->next = f;
				return l;
			}
		}


		do {
			if(empty(s))
			    s=l;
			else {
				s = tail(s);
			}
			val -= head(s);
		} while(!empty(s) && val > k);

	}

	return l;

}


list seekDestroy(list l, int k) {

	list t=l, f, s = emptylist();
	int i, val=0;

	while(!empty(t)){
		val=0;
		f=t;
		while(!empty(f) && val < k){
			val += head(f);
			f = tail(f);
		}
		if(val == k){
	        if(empty(s))
				return f;
			else{
			    s->next = f;
				return l;
			}
		}
		s=t;
		t = tail(t);

	}

	return l;

}

list seekDestroyFisso(list l, int n, int k) {

	list t=l, f, s = emptylist();
	int i, val=0;

	while(!empty(t)){
		val=0;
		f=t;
		for(i=0; i < k && !empty(f); i++){
			val += head(f);
			f = tail(f);
		}
		if(i==k && val == n){
	        if(empty(s))
				return f;
			else{
			    s->next = f;
				return l;
			}
		}
		s=t;
		t = tail(t);

	}

	return l;

}

void main(void) {
	list l = emptylist();
	int el;
	int scelta;
	char invio;
	FILE *f;
	int n=35;
	int k=4;

	f = fopen("../Valori2.txt", "r");
	if (f == NULL) {
		printf("Errore Apertura file");
		return;
	}

	while (fscanf(f, "%d", &el)>0) {
		l = cons(el, l);
	}

	fclose(f);

	showlist(l);

	printf("Tolgo %d su %d elementi consecutivi\n", n,k);
	l=seekDestroyFisso(l, n, k);
	showlist(l);

	n=12;
	printf("Tolgo %d\n", n);
	l=seekDestroy(l, n);
	showlist(l);

	printf("Tolgo %d\n", n);
	l=seekDestroyNoRestart(l, n);
	showlist(l);

}
