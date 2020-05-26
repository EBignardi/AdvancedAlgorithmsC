#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
	char Nome[20];
	char CF[17];
	char Referto[100];
	int CodiceAccesso;
	int Ora;
} Persona;

typedef Persona element;

// Confronta due element a e b e restituisce 0 se sono uguali ('a' e 'b' hanno lo stesso codice di accesso), 1 se a > b ('a' ha codice di accesso con priorità maggiore rispetto a 'b') e -1 se a < b ('a' ha codice di accesso con priorità minore rispetto a 'b')
int elecmp(const element *a, const element *b) {
	if (a->CodiceAccesso == b->CodiceAccesso) {
		if (a->Ora == b->Ora) {
			return 0;
		}
		else if (a->Ora > b->Ora) {
			return -1;
		}
		else {
			return 1;
		}
	}
	else if (a->CodiceAccesso > b->CodiceAccesso) {
		return 1;
	}
	else {
		return -1;
	}
}

// Scambia i valori degli element specificati
void swap(element *a, element *b) {
	element temp = *a;
	*a = *b;
	*b = temp;
	return;
}

/** @brief Restituisce l'indice del padre del nodo 'i'

@param[in] 'i' - indice di un nodo

@return indice del padre del nodo 'i'
*/
static unsigned parent(unsigned i) {
	return i / 2;
}

/** @brief Restituisce l'indice del figlio sinistro del nodo 'i'

@param[in] 'i' - indice di un nodo

@return indice del figlio sinistro del nodo 'i'
*/
static unsigned left(unsigned i) {
	return 2 * i;
}

/** @brief Restituisce l'indice del figlio destro del nodo 'i'

@param[in] 'i' - indice di un nodo

@return indice del figlio destro del nodo 'i'
*/
static unsigned right(unsigned i) {
	return 2 * i + 1;
}

int PrintHeap_VectorImplemented_Auxiliary(element * H, unsigned i, size_t heap_size, bool is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width = 7;

	if (i > heap_size) {
		return 0;
	}

	sprintf(b, "(%2d-%2d)", H[i].CodiceAccesso, H[i].Ora);

	int leftDim = PrintHeap_VectorImplemented_Auxiliary(H, left(i), heap_size, true, offset, depth + 1, s);
	int rightDim = PrintHeap_VectorImplemented_Auxiliary(H, right(i), heap_size, false, offset + leftDim + width, depth + 1, s);

	for (int i = 0; i < width; i++) {
		s[2 * depth][offset + leftDim + i] = b[i];
	}

	if (depth && is_left) {

		for (int i = 0; i < width + rightDim; i++)
			s[2 * depth - 1][offset + leftDim + width / 2 + i] = '-';

		s[2 * depth - 1][offset + leftDim + width / 2] = '+';
		s[2 * depth - 1][offset + leftDim + width + rightDim + width / 2] = '+';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < leftDim + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';

		s[2 * depth - 1][offset + leftDim + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}

	return leftDim + width + rightDim;
}

// Funzione per la stampa di un albero heap in ASCII
void PrintHeap_VectorImplemented(element *H, unsigned i, size_t heap_size)
{
	char s[20][255];
	for (int i = 0; i < 20; i++) {
		sprintf(s[i], "%80s", " ");
	}

	PrintHeap_VectorImplemented_Auxiliary(H, i, heap_size, false, 0, 0, s);

	for (int i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}

// Funzione di supporto per la spiegazione, non utile ai fini della risoluzione dell'esercizio
int RiempiVettore(element *V, size_t size) {
	for (unsigned i = 1; i < size; i++) {
		strcpy(V[i].CF, "CF");
		V[i].CodiceAccesso = i;
		strcpy(V[i].Nome, "Nome");
		strcpy(V[i].Referto, "Referto");
		V[i].Ora = i;
	}
	return size - 1;
}

// Funzione di supporto per la spiegazione, non utile ai fini della risoluzione dell'esercizio
void StampaVettore(element *V, size_t size) {
	printf("\n");
	for (unsigned i = 1; i < size; i++)
		printf(" %d", V[i].CodiceAccesso);
	return;
}

// MoveUp iterativa per una max heap 
void MoveUp_MaxHeap(element *H, unsigned i, size_t heap_size) {
	while (i != 1 && elecmp(&H[i], &H[parent(i)]) > 0) {
		swap(&H[i], &H[parent(i)]);
		i = parent(i);
	}
}

// MoveUp ricorsiva per una max heap
void MoveUp_MaxHeap_Recursive(element *H, unsigned i, size_t heap_size) {
	if (i == 1) {
		return; // I'm the root!
	}

	if (elecmp(&H[i], &H[parent(i)]) > 0) {
		swap(&H[i], &H[parent(i)]);
		MoveUp_MaxHeap_Recursive(H, parent(i), heap_size);
	}

	return;
}

// MoveDown iterativa per una max heap 
void MoveDown_MaxHeap(element *H, unsigned i, size_t heap_size) {

	unsigned l, r, largest = i;
	bool done;
	do {
		done = true;
		l = left(i);
		r = right(i);

		if ((l <= heap_size) && elecmp(&H[l], &H[largest]) > 0) {
			largest = l;
		}

		if ((r <= heap_size) && elecmp(&H[r], &H[largest]) > 0) {
			largest = r;
		}

		if (largest != i) {
			swap(&H[i], &H[largest]);
			i = largest;
			done = false;
		}

	} while (!done);

	return;
}

// MoveDown ricorsiva per una max heap 
void MoveDown_MaxHeap_Recursive(element *H, unsigned i, size_t heap_size) {
	if (i > heap_size) {
		abort();
	}

	unsigned l, r, largest = i;
	l = left(i);
	r = right(i);

	if ((l <= heap_size) && elecmp(&H[l], &H[largest]) == 1)
		largest = l;

	if ((r <= heap_size) && elecmp(&H[r], &H[largest]) == 1)
		largest = r;

	if (largest != i) {
		swap(&H[i], &H[largest]);
		MoveDown_MaxHeap_Recursive(H, largest, heap_size);
	}

	return;
}

// Trasforma un vettore qualsiasi H in una coda MaxHeap utilizando un metodo iterativo
void Heapify_MaxHeap(element *H, size_t heap_size) {
	for (int i = heap_size / 2; i >= 1; i--) {
		MoveDown_MaxHeap(H, i, heap_size);
	}

	return;
}

// Funzione ausiliaria per la funzione heapify ricorsiva
void Heapify_MaxHeap_Recursive_Auxiliary(element *H, unsigned i, size_t heap_size) {
	if (left(i) > heap_size && right(i) > heap_size) {
		// Sono una foglia quindi termino
		return;
	}

	Heapify_MaxHeap_Recursive_Auxiliary(H, left(i), heap_size);
	Heapify_MaxHeap_Recursive_Auxiliary(H, right(i), heap_size);
	MoveDown_MaxHeap_Recursive(H, i, heap_size);
}

// Trasforma un vettore qualsiasi H in una coda MaxHeap utilizando un funzione ricorsiva ausiliaria (Heapify_MaxHeap_Recursive_Auxiliary)
void Heapify_MaxHeap_Recursive(element *H, size_t heap_size) {
	if (heap_size > 1) {
		// Inizia la ricorsione a partire dalla root della coda heap
		Heapify_MaxHeap_Recursive_Auxiliary(H, 1, heap_size);
	}
	return;
}

// Aggiunge un nuovo elemeneto ad una coda MaxHeap e ripristina la priorità eseguento la MoveUp. La funzione restituisce poi il puntatore alla nuova MaxHeap
element *Push_MaxHeap(const element *new_e, element *H, size_t *heap_size) {
	(*heap_size)++;
	H = realloc(H, (*heap_size + 1) * sizeof(element));
	H[*heap_size] = *new_e;
	MoveUp_MaxHeap(H, *heap_size, *heap_size);

	return H;
}

// Estrae l'elemento massimo da una coda MaxHeap (salvandolo in popped), lo scambia con l'ultimo valore della code e ripristina la priorità eseguento la MoveDown. La funzione restituisce poi il puntatore alla nuova coda MaxHeap
element *Pop_MaxHeap(element *H, size_t *heap_size, element *popped) {

	*popped = H[1];
	swap(&H[1], &H[*heap_size]);

	(*heap_size)--;
	MoveDown_MaxHeap_Recursive(H, 1, *heap_size);

	return realloc(H, (*heap_size + 1) * sizeof(element));
}

// Crea una Heap vuota (la prima posizione non viene utilizzata)
element *CreateHeap() {
	element *H = malloc(1 * sizeof(element));
	return H;
}

// Elimina il valore massimo da una MaxHeap senza dire qual è e restituisce il puntatore alla nuova coda MaxHeap
element *DeleteMax_MaxHeap(element *H, size_t *heap_size) {
	swap(&H[1], &H[*heap_size]);
	(*heap_size)--;
	MoveDown_MaxHeap_Recursive(H, 1, *heap_size);
	return realloc(H, (*heap_size + 1) * sizeof(element));
}

// Restituisce il valore massimo di una MaxHeap senza eliminarlo dalla coda 
element FindMax_MaxHeap(element *H, size_t heap_size) {
	if (heap_size < 1) {
		abort();
	}

	return H[1];
}

// Elimina un nodo arbitrario (specificato) da una coda MaxHeap restituisce il puntatore alla nuova coda MaxHeap
element *Delete_MaxHeap(element *to_delete, element *H, size_t *heap_size) {
	for (unsigned i = 1; i <= *heap_size; ++i) {
		if (elecmp(&H[i], to_delete) == 0) {
			swap(&H[i], &H[*heap_size]);
			MoveDown_MaxHeap(H, i, --(*heap_size));
			return realloc(H, (*heap_size + 1) * sizeof(element));
		}
	}

	return H;
}

void DeleteHeap(element *H) {
	free(H);
}

// Algoritmo di ordinamo basato su coda heap
void Heapsort_MaxHeap(element *H, size_t heap_size) {
	int dim = heap_size;
	for (int i = heap_size; i >= 2; i--) {
		swap(&H[1], &H[i]);
		MoveDown_MaxHeap(H, 1, --dim);
	}
}

element GetElement() {
	element el;
	printf("Inserisci il nome del paziente: ");
	scanf(" %19[^\n]%*c", el.Nome);

	printf("Inserisci il CF del paziente: ");
	scanf("%16[^\n]%*c", el.CF);

	printf("Inserisci il referto del paziente: ");
	scanf("%99[^\n]%*c", el.Referto);

	printf("Inserisci il codice di accesso del paziente (chiave della heap): ");
	scanf("%d", &el.CodiceAccesso);

	printf("Inserisci l'ora di accesso del paziente (chiave della heap): ");
	scanf("%d", &el.Ora);

	return el;
}

void ShowElement(element el) {
	printf("Nome: %s\nCF: %s\nReferto: %s\nCodiceAccesso: %d\nOra: %d\n", el.Nome, el.CF, el.Referto, el.CodiceAccesso, el.Ora);
}

//int main(void) {
//
//	size_t heap_size = 9; 
//	element *H = malloc(sizeof(element)*(heap_size + 1));
//	RiempiVettore(H, heap_size + 1);
//	printf("Albero originale:\n");
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//
//	printf("Heap:\n");
//	Heapify_MaxHeap_Recursive(H, heap_size);
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//	
//	printf("Heap con radice modificata:\n");
//	H[1].CodiceAccesso = 0; 
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//
//	printf("Heap dopo moveDown:\n");
//	MoveDown_MaxHeap(H, 1, heap_size);
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//
//	//printf("Dimensione heap prima dell'aggiunta: %u\n", _msize(H)/sizeof(element)); 
//	printf("Aggiunta di un nuovo elemento con priorita' 20:\n");
//	element e; 
//	strcpy(e.CF, "CF");
//	strcpy(e.Nome, "Nome");
//	strcpy(e.Referto, "Referto");
//	e.CodiceAccesso = 20;
//
//	H = Push_MaxHeap(&e, H, &heap_size);
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//	//printf("Dimensione heap dopo l'aggiunta: %u\n", _msize(H)/sizeof(element));
//
//	printf("Aggiunta di un nuovo elemento con priorita' 15:\n");
//	strcpy(e.CF, "CF");
//	strcpy(e.Nome, "Nome");
//	strcpy(e.Referto, "Referto");
//	e.CodiceAccesso = 15;
//	
//	H = Push_MaxHeap(&e, H, &heap_size);
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//
//	//printf("Dimensione heap prima dell'eliminazione: %u\n", _msize(H) / sizeof(element));
//	printf("Eliminazione dell'elemento con priorita' 15:\n");
//	H = Delete_MaxHeap(&e, H, &heap_size); 
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//	//printf("Dimensione heap dopo l'eliminazione: %u\n", _msize(H) / sizeof(element));
//
//	printf("Eliminazione dell'elemento con priorita' massima:\n");
//	H = DeleteMax_MaxHeap(H, &heap_size);
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//
//	printf("Pop:\n");
//	H = Pop_MaxHeap(H, &heap_size, &e);
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//	printf("Elemento Estratto:\n");
//	ShowElement(e); 
//
//	printf("Ricerca dell'elemento a priorita' massima:\n");
//	e = FindMax_MaxHeap(H, heap_size);
//	PrintHeap_VectorImplemented(H, 1, heap_size);
//	ShowElement(e);
//
//	Heapsort_MaxHeap(H, heap_size);
//	StampaVettore(H, heap_size + 1); 
//
//}


int main(void)
{
	element *H = CreateHeap();
	size_t heap_size = 0; // numero di elementi nella heap

	unsigned scelta;
	element e;

	do {
		printf("\n\nMenu' Principale - CODA HEAP\n\nScegli l'operazione da eseguire: \n");
		printf("1. Inserisci elemento in coda\n");
		printf("2. Visualizza il prossimo elemento\n");
		printf("3. Servi il prossimo elemento\n");
		printf("4. Visualizza coda heap\n");
		printf("0. Termina il programma\n");

		// acquisizione scelta utente
		scanf("%d", &scelta);

		// interpretazione scelta ed esecuzione della relativa operazione
		switch (scelta) {

		case 0:
			printf("Uscita dal programma!\n");
			break;

		case 1:
			printf("INSERIMENTO DI UN NUOVO PAZIENTE \n");
			e = GetElement();
			H = Push_MaxHeap(&e, H, &heap_size);
			break;

		case 2:
			if (heap_size == 0) {
				printf("Nessun paziente in coda!\n");
			}
			else {
				printf("Il prossimo paziente e' (NON SERVITO):\n");
				ShowElement(FindMax_MaxHeap(H, heap_size));
			}
			break;

		case 3:
			if (heap_size == 0) {
				printf("Nessun paziente in coda!\n");
			}
			else {
				printf("Il prossimo paziente e' (SERVITO):\n");
				H = Pop_MaxHeap(H, &heap_size, &e);
				ShowElement(e);
			}
			break;
		case 4:
			if (heap_size == 0) {
				printf("Nessun paziente in coda!\n");
			}
			else {
				PrintHeap_VectorImplemented(H, 1, heap_size);
			}
			break;

		default:
			printf("La scelta non e' corretta, inserirne un'altra\n");
		}
	} while (scelta != 0);

	DeleteHeap(H);
}