#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

//_______________________________________________CONFRONTI E FUNZIONI DI APPOGGIO______________________________________
bool isEqual(sito e1, sito e2) {
	if (e1.numeroaccessi = e2.numeroaccessi)
		return 1;
	return 0;
}

bool isLess(sito e1, sito e2) {
	if (e1.numeroaccessi < e2.numeroaccessi)	
		return 1;
	return 0;
}

sito copy(sito e) {
	sito el;
	el = e;
	return el;
}

void showEl(sito e) {
	printf("L'elemento e ha valore: %s %d\n", e.nomehost, &e.numeroaccessi);
}

sito getEl() {
	sito e;
	printf("\n Inserire il valore da assegnare: ");
	scanf("%s %d", e.nomehost, &e.numeroaccessi);
	return e;
}

//_______________________________________________PRIMITIVE______________________________________

//controlla se lalbero passato e' vuoto
bool empty(tree t) {
	return (t == NULL);
}

//restituisce un albero NULLO, per fare confronti
tree emptyTree(void) {
	return NULL;
}

//restituisce la radice
sito root(tree t) {
	if (empty(t))
		abort();
	else
		return t->value;
}

//figlio sinistro
tree left(tree t) {
	if (empty(t)) return NULL;
	else return t->left;
}

//figlio destro
tree right(tree t) {
	if (empty(t)) return NULL;
	else return t->right;
}

//costruisce lalbero
tree consTree(sito e, tree l, tree r) {
	tree t = (node*)malloc(sizeof(node));
	t->value = e;
	t->left = l;
	t->right = r;
	return t;
}

//_______________________________________________VISITE ALBERI______________________________________

//visita in PRE ORDINE
void preOrder(tree t) {
	if (!empty(t)) {
		printf("\t");
		showEl(root(t));
		preOrder(left(t));
		preOrder(right(t));
	}
}

//visita in IN ORDINE
void inOrder(tree t) {
	if (!empty(t)) {
		inOrder(left(t));
		printf("\t");
		showEl(root(t));
		inOrder(right(t));
	}
}


//visita in POST ORDINE
void postOrder(tree t) {
	if (!empty(t)) {
		postOrder(left(t));
		postOrder(right(t));
		printf("\t"); showEl(root(t));
	}
}

//stampa gli elementi del livello
void stampalvl(tree t, size_t lvl) {
	if (!empty(t)) {
		if (lvl == 0) {
			printf(" ");
			showEl(root(t));
		}
		else if (lvl >= 1) {
			stampalvl(left(t), lvl - 1);
			stampalvl(right(t), lvl - 1);
		}
	}
}

//restituisce l altezza di un albero
int height(tree t) 
{
	if (empty(t)) return 0;
	if (empty(left(t)) && empty(right(t))) return 0;
	else {
		int hl = height(left(t)), hr = height(right(t));
		return 1 + (hl > hr ? hl : hr);
	}
}

//vista in AMPIEZZA
void visitaInAmpiezza(tree t) {
	printf("\n Visita in ampiezza:\n");
	int h = height(t);
	for (int i = 0; i <= h; i++) {
		stampalvl(t, i);
		printf("\n");
	}
	printf("\n");
}

//_______________________________________________SECONDARIE ______________________________________

//true se l elemento passato e' parte dell albero
bool memberTree(sito e, tree t) {
	if (empty(t)) return false;
	else if (isEqual(e, root(t))) return true;
	else return (memberTree(e, left(t)) || memberTree(e, right(t)));
}

//creare un albero con inserimento da tastiera
tree createTree(void) {
	sito e;
	sito stop;  /* arbitrario */
	stop.eta = 0;
	printf("Inserisci elemento:\t");
	e = getEl();

	if (isEqual(e, stop)) return emptyTree();
	else {
		tree l, r;
		l = createTree();
		r = createTree();
		return consTree(e, l, r);
	}
}

//_______________________________________________ALBERI BST______________________________________

//inserisce l elemento passato nell albero (in ordine), in base al PARAMETRO di e
tree insOrdTree(sito e, tree t) {
	if (empty(t)) {
		return consTree(e, emptyTree(), emptyTree());
	}
	if (isLess(e, root(t)) || isEqual(e, root(t)))
	{
		return consTree(root(t), insOrdTree(e, left(t)), right(t));
	}
	return consTree(root(t), left(t), insOrdTree(e, right(t)));
}

//restituisce true se e fa parte dell albero
bool memberTreeOrd(sito e, tree t) {
	if (empty(t)) return false;
	if (isEqual(e, root(t))) return true;
	if (isLess(e, root(t)))
	{
		return memberTreeOrd(e, left(t));
	}
	return memberTreeOrd(e, right(t));
}

tree DeleteElement(tree t, sito e)
{

	tree l = t;
	tree next = emptyTree();
	tree pl = emptyTree();
	tree pr = emptyTree();
	//cerco l'elemento salvandomi il padre(pl e pr) sapendo se e' figlio dx o sx
	while (!empty(t)) {
		if (isEqual(root(t), e)) break;
		if (isLess(e, root(t))) {
			pl = t;
			pr = emptyTree();
			t = left(t);
		}
		else {
			pl = emptyTree();
			pr = t;
			t = right(t);
		}
	}
	//Eliminazione vera e propria solo sel'ho trovato
	if (!empty(t))
	{
		// Il nodo da eliminare e' una foglia
		if (empty(left(t)) && empty(right(t))) {
			// Se e' la root ritorno un albero vuoto
			if (t == l)
			{
				//free(t);
				return emptyTree();
			}
			if (!empty(pl)) //se è figlio sinistro metto che il padre ha figlio empty
			{
				pl->left = emptyTree();
			}
			else //se è figlio destrp metto che il padre ha figlio empty
			{
				pr->right = emptyTree();
			}
			//next = emptyTree();
		}
		// Il nodo da eliminare ha un solo figlio destro
		else if (empty(left(t))) {
			// Se e' la root ritorno il figlio
			if (t == l) return right(t);
			next = right(t);
			if (!empty(pl)) pl->left = next; //se è figlio sinistro metto che il padre ha come figlio sx l'unico figlio dx del nodo
			else pr->right = next;
		}
		else if (empty(right(t))) {
			// Se e' la root ritorno il figlio
			if (t == l)
			{
				return left(t);
			}
			next = left(t);
			if (!empty(pl)) pl->left = next;
			else pr->right = next;
		}

		else {
			// Il nodo da eliminare ha due figli
			pr = t;
			pl = emptyTree();
			next = right(t); //selezioniamo il figlio destro del nodo
			if (!empty(next))
				while (!empty(left(next))) { //scendiamo tutto a sinistra
					pr = emptyTree();
					pl = next;
					next = left(next);
				}
			t->value = root(next); // assegnamo al nodo il valore del figlio minore 
			if (right(next) != NULL) {
				next = right(next); //chiamo next il nodo che è figlio eventuale del nodo prescelto cosi trovato (può avere solo figlio destro)
			}
			else next = emptyTree();
		}
		//attacchiamo il padre del nodo che ho sostituito  al figlio destro di next
		if (!empty(pl))
		{
			//free(pl->left);
			pl->left = next;
		}
		//vuol dire che il nodo da eliminare ha un solo figlio destro
		if (!empty(pr))
		{
			//free(pr->right);
			pr->right = next;
		}
	}
	return l;
}

// costruisce un albero leggendo i dati da un file aperto passato
tree BSTread(FILE *f)
{
	tree t = emptyTree();
	sito e;
	//element stop; /* arbitrario */
	//stop.valore = 0;
	while (1)
	{
		int ctrl = fscanf(f, "%s %d", e.nomehost, &e.numeroaccessi);
		if (feof(f) || ctrl != 4)
			break;

		t = insOrdTree(e, t);
	}
	return t;
}

//crea un albero prendendo valori da stdinput
tree CreaAlberoBST()
{
	tree t = emptyTree();
	sito e;
	sito stop;
	stop.eta = 0;
	printf("\nCreazione alberoBST:\n");
	while (1) {
		printf("inserisci valore:\t");
		scanf("%s %d", e.nomehost, &e.numeroaccessi);
		if (isEqual(e, stop))
			break;
		t = insOrdTree(e, t);
	}
	return t;
}

//confronta tutti i valori dei due elementi per vedere se sono diversi
bool diversi(sito e1, sito e2) {
	if (e1.numeroaccessi != e2.numeroaccessi && e1.nomehost != e2.nomehost)
		return true;
	return false;
}

//delete element degli alberi normali
tree delete(tree t, sito e) {
	tree l = t, next;
	tree pl = NULL, pr = NULL;
	while (diversi(root(t), e) && !empty(t)) {
		if (e.cognome < root(t).cognome) {
			pl = t;
			pr = emptyTree();
			t = left(t);
		}
		else {
			pl = emptyTree();
			pr = t;
			t = right(t);
		}
	}
	//printf("\ntrovato %d", root(t));
	if (!empty(t)) {
		// Il nodo da eliminare  una foglia
		if (empty(left(t)) && empty(right(t))) {
			// Se e' la root ritorno un albero vuoto
			if (t == l)
				return emptyTree();
			next = emptyTree();
		}
		else {
			// Il nodo da eliminare ha un solo figlio
			if (empty(left(t))) {
				// Se e' la root ritorno il figlio
				if (t == l)
					return right(t);
				next = right(t);
			}
			else {
				if (empty(right(t))) {
					// Se e' la root ritorno il figlio
					if (t == l)
						return left(t);
					next = left(t);
				}
				else {
					// Il nodo da eliminare ha due figli
					pr = t;
					pl = emptyTree();
					next = right(t);
					if (!empty(next))
						while (!empty(left(next))) {
							pr = emptyTree();
							pl = next;
							next = left(next);
						}
					t->value = root(next);
					if (right(next) != NULL) {
						next = right(next);
					}
					else
						next = emptyTree();
				}
			}
		}
		if (!empty(pl))
			pl->left = next;
		if (!empty(pr))
			pr->right = next;
	}
	return l;
}

//La funziona ritorna empty tree in caso non trovi l'elemento o l'elemento è la radice
tree trova_padre(tree t, sito e) {
	if (empty(t)) return emptyTree();
	if (isEqual(root(t), e)) return emptyTree();
	if ((!empty(left(t)) && isEqual(root(left(t)), e)) || (!empty(right(t)) && isEqual(root(right(t)), e))) return t;
	tree l = trova_padre(left(t), e);
	tree r = trova_padre(right(t), e);
	if (!empty(l)) return l;
	if (!empty(r)) return r;
	return emptyTree(); // fondamentale altrimenti non ritorno nulla se non lo trovo in uno dei due rami
}

//Inserisce l elemento confrontando con un parametro di e.
tree insertBinOrd(sito e, tree t) {
	tree l = t;
	if (empty(t))
		return consTree(e, emptyTree(), emptyTree());
	while (!empty(t)) {
		if (e.numeroaccessi <= root(t).numeroaccessi) {
			if (empty(left(t))) {
				t->left = consTree(e, emptyTree(), emptyTree());
				t = left(t);
			}
			t = left(t);
		}
		else {
			if (empty(right(t))) {
				t->right = consTree(e, emptyTree(), emptyTree());
				t = right(t);
			}
			t = right(t);
		}
	}
	return l;
}