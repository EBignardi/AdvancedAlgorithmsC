#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define MAX_STR_LENGHT 256
/* Struttura dati oggetto (element) della lista della spesa */
typedef struct element {
	char nome[MAX_STR_LENGHT];
	char unita[MAX_STR_LENGHT];
	double qta;
}element;

typedef struct list_element {
	element value;
	struct list_element *next;
} item;

typedef item* list;

// Firme
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

list insertBack(element e, list l);
element* cercaOggetto(const char* nome, const list lista);


// Primitive
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
	element el = e;
	return el;
}

void dealloc(list l) {
	list temp;
	while (!empty(l)) {
		temp = l;
		l = tail(l);
		free(temp);
	}
}
// Primitive

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

void printElement(element el) {
	printf("%s %.2lf %s", el.nome, el.qta, el.unita);
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

void acquisiciOggettoDaStdin(element* oggetto) {
	//oggetto = malloc(sizeof(element));

	printf("Nome dell'oggetto da aggiungere al carrello: ");
	scanf("%s", oggetto->nome);

	printf("Quantita': ");
	scanf("%lf", &oggetto->qta);

	printf("Unita' di misura: ");
	scanf("%s", oggetto->unita);

	return;
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

int main() {

	list carrello = NULL;
	element oggetto;

	char nomeOggetto[MAX_STR_LENGHT];
	double quantita;

	int menu;

	do {
		printf("1. Inserisci un nuovo oggetto al carello\n");
		printf("2. Inserisci un nuovo oggetto (in coda) al carello\n");
		printf("3. Visualizza i dati dell'oggetto X (stdin)\n");
		printf("4. Visualizza tutti gli oggetti nel carrello\n");
		printf("5. Visualizza tutti gli oggetti nel carrello con quantita maggiore di N (stdin)\n");
		printf("0. Esci\n");

		scanf("%d", &menu);
		fflush(stdin);

		switch (menu) {
		case 1:
			acquisiciOggettoDaStdin(&oggetto);
			if (elementExists(carrello, &oggetto)) {
				printf("Esiste gia' un elemento con nome '%s'\n", oggetto.nome);
			}
			else {
				carrello = cons(oggetto, carrello);
			}
			break;
		case 2:
			acquisiciOggettoDaStdin(&oggetto);
			if (elementExists(carrello, &oggetto)) {
				printf("Esiste gia' un elemento con nome '%s'\n", oggetto.nome);
			}
			else {
				carrello = insertBack(oggetto, carrello);
			}
			break;
		case 3:
			printf("Inserisci il nome dell'oggetto che vuoi cercare: ");
			scanf("%s", nomeOggetto);
			element* trovato = cercaOggetto(nomeOggetto, carrello);
			if (trovato == NULL) {
				printf("Non esiste nessun oggetto con il nome specificato!\n");
			}
			else {
				printElement(*trovato);
				printf("\n");
			}
			break;
		case 4:
			showlist(carrello);
			break;
		case 5:
			printf("Inserisci una quantita': ");
			scanf("%lf", &quantita);
			showListConditional(carrello, quantita);
			break;
		}

	} while (menu != 0);
}