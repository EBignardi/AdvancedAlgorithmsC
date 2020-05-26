#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

indirizzo* primo = NULL;
indirizzo* ultimo = NULL;


// firme
void compilaIndirizzo(indirizzo*);
void stampaIndirizzo(indirizzo);
void visualizzaTutti();
indirizzo *sort(indirizzo *);
indirizzo *list_switch(indirizzo*, indirizzo *);

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


void compilaIndirizzo(indirizzo* info) {
	printf("Inserisci il nome: \n");
	gets(info->nome);
	printf("Inserisci la via: \n");
	gets(info->via);
	printf("Inserisci il numero civico: \n");
	scanf("%d", &(info->numero));
	fflush(stdin);
	printf("Inserisci la citta\': \n");
	gets(info->citta);
	printf("Inserisci la provincia: \n");
	gets(info->provincia);
	printf("Inserisci il cap: \n");
	gets(info->cap);
	info->prossimo = NULL;
}

void stampaIndirizzo(indirizzo info) {
	printf("-------------------- \n");
	printf("Nome: %s \n", info.nome);
	printf("Via: %s \n", info.via);
	printf("Numero civico: %d \n", info.numero);
	printf("Citta\': %s \n", info.citta);
	printf("Provincia: %s \n", info.provincia);
	printf("Cap: %s \n", info.cap);
}

/* inserisco il nuovo elemento in ultima posizione */
void inserisciIndirizzo(indirizzo* info) {
	if (primo == NULL) {
		primo = info;
		ultimo = info;
	}
	else {
		ultimo->prossimo = info;
		ultimo = info;
	}
}

void visualizzaTutti() {
	indirizzo* i;
	if (primo == NULL) {
		printf("Nessun indirizzo presente\n");
	}
	else {
		for (i = primo; i != NULL; i = i->prossimo) {
			stampaIndirizzo(*i);
		}
	}
}

void ordina() {
	primo = sort(primo);
}


/* cerca un indirizzo con un certo nome, torna NULL se non lo trova*/
indirizzo* cercaIndirizzo(char* nome) {
	indirizzo* i;
	if (primo != NULL) {
		for (i = primo; i != NULL; i = i->prossimo) {
			if (strcmp(nome, i->nome) == 0) {
				return i;
			}
		}
	}
	return NULL;
}

/* elimina un indirizzo dalla lista */
int eliminaIndirizzo(char* nome) {
	int eliminato = 0;
	indirizzo* i;
	indirizzo* precedente = primo;
	if (primo != NULL) {
		for (i = primo; i != NULL; i = i->prossimo) {
			if (strcmp(nome, i->nome) == 0) {
				if (ultimo == i) {
					ultimo = precedente;
				}
				if (primo == i) {
					primo = primo->prossimo;
				}
				precedente->prossimo = i->prossimo;
				eliminato = 1;
				break;
			}
			precedente = i;
		}
	}
	return eliminato;
}

int main() {

	indirizzo* info;
	int menu;
	char nome[40];
	do {
		printf("1. Inserisci un nuovo indirizzo\n");
		printf("2. Stampa tutti gli indirizzi\n");
		printf("3. Cerca un indirizzo\n");
		printf("4. Elimina un indirizzo\n");
		printf("5. Ordina la rubrica\n");
		printf("0. Esci\n");

		scanf("%d", &menu);
		fflush(stdin);

		switch (menu) {
		case 1:
			info = malloc(sizeof(indirizzo));
			compilaIndirizzo(info);
			inserisciIndirizzo(info);
			break;
		case 2:
			visualizzaTutti();
			break;
		case 3:
			printf("Inserisci un nome da cercare: \n");
			gets(nome);
			info = cercaIndirizzo(nome);
			if (info != NULL) {
				printf("Nome trovato, via: %s \n", info->via);
			}
			else {
				printf("Nome non trovato.\n");
			}
			break;
		case 4:
			printf("Inserisci un nome da eliminare: \n");
			gets(nome);
			if (eliminaIndirizzo(nome)) {
				printf("Nome eliminato. \n");
			}
			else {
				printf("Nome non trovato, impossibile l'eliminazione. \n");
			}
			break;
		case 5:
			printf("Rubrica oridnata: \n");
			ordina();
			visualizzaTutti();
			break;
		}

	} while (menu != 0);
}

