#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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



int main(void)
{
	FILE *fp;
	list startList, lowList, highList, temp;
	element voto, soglia;
	if ((fp = fopen("voti.txt", "r")) == NULL)
	{
		printf("Attenzione! Il file non esiste");
		exit(-1);
	}
	startList = emptylist();
	while (fscanf(fp, "%d", &voto)>0)
	{
		startList = cons(voto, startList);
	}
	fclose(fp);

	printf("\nLista dei voti:\n");
	showlist(startList);

	printf("\nInserisci il valore soglia");
	scanf("%d", &soglia);
	lowList = emptylist();
	highList = emptylist();
	//costruzione delle due liste SENZA primitive
	while (startList != NULL)
	{
		if (startList->value < soglia)
		{
			temp = (list)malloc(sizeof(item));
			temp->value = startList->value;
			temp->next = lowList;
			lowList = temp;
		}
		else
		{
			temp = (list)malloc(sizeof(item));
			temp->value = startList->value;
			temp->next = highList;
			highList = temp;
		}
		startList = startList->next;
	} //fine costruzione liste

	  /*
	  //costruzione delle due liste CON primitive
	  //(alternativo al precedente)
	  while (!empty(startList))
	  {
	  element value = head(startList);
	  if (value < soglia)
	  lowList = cons(value, lowList);
	  else
	  highList = cons(value, highList);
	  startList = tail(startList);
	  }
	  //fine costruzione liste
	  */
	showlist(lowList);
	showlist(highList);

	// deallocazione delle liste (senza primitive)
	while (!empty(lowList))
	{
		temp = lowList;
		lowList = tail(lowList);
		free(temp);
	}
	while (!empty(highList))
	{
		temp = highList;
		highList = tail(highList);
		free(temp);
	}
}