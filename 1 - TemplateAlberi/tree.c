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
	printf("L'elemento e ha valore: %s %d\n", e.nomehost, e.numeroaccessi);
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
	stop.numeroaccessi = 0;
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

//inserisce l elemento passato nell albero in ordine GENERALE (comprende tutti i parametri)
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
		if (feof(f) || ctrl != 2)
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
	stop.numeroaccessi = 0;
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
		if (e.nomehost < root(t).nomehost) {
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

//Inserisce l elemento confrontando con un parametro di e
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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* ----------------------------------------------- PER IL SINGOLO VALORE -------------------------------------------------------------*/

//_______________________________________________CONFRONTI E FUNZIONI DI APPOGGIO______________________________________
bool isEqual1(valore e1, valore e2) {
	if (e1.id = e2.id)
		return 1;
	return 0;
}

bool isLess1(valore e1, valore e2) {
	if (e1.id < e2.id)
		return 1;
	return 0;
}

valore copy1(valore e) {
	valore el;
	el = e;
	return el;
}

void showEl1(valore e) {
	printf("L'elemento e ha valore: %d\n", e.id);
}

valore getEl1() {
	valore e;
	printf("\n Inserire il valore da assegnare: ");
	scanf("%s %d", &e.id);
	return e;
}

//_______________________________________________PRIMITIVE______________________________________

//controlla se lalbero passato e' vuoto
bool empty1(treeval t) {
	return (t == NULL);
}

//restituisce un albero NULLO, per fare confronti
treeval emptyTree1(void) {
	return NULL;
}

//restituisce la radice
valore root1(treeval t) {
	if (empty1(t))
		abort();
	else
		return t->val;
}

//figlio sinistro
treeval left1(treeval t) {
	if (empty1(t)) return NULL;
	else return t->left;
}

//figlio destro
treeval right1(treeval t) {
	if (empty1(t)) return NULL;
	else return t->right;
}

//costruisce lalbero
treeval consTree1(valore e, treeval l, treeval r) {
	treeval t = (node*)malloc(sizeof(node));
	t->val = e;
	t->left = l;
	t->right = r;
	return t;
}

//_______________________________________________VISITE ALBERI______________________________________

//visita in PRE ORDINE
void preOrder1(treeval t) {
	if (!empty1(t)) {
		printf("\t");
		showEl1(root1(t));
		preOrder1(left1(t));
		preOrder1(right1(t));
	}
}

//visita in IN ORDINE
void inOrder1(treeval t) {
	if (!empty1(t)) {
		inOrder1(left1(t));
		printf("\t");
		showEl1(root1(t));
		inOrder1(right1(t));
	}
}


//visita in POST ORDINE
void postOrder1(treeval t) {
	if (!empty1(t)) {
		postOrder1(left1(t));
		postOrder1(right1(t));
		printf("\t"); showEl1(root1(t));
	}
}

//stampa gli elementi del livello
void stampalvl1(treeval t, size_t lvl) {
	if (!empty1(t)) {
		if (lvl == 0) {
			printf(" ");
			showEl1(root1(t));
		}
		else if (lvl >= 1) {
			stampalvl1(left1(t), lvl - 1);
			stampalvl1(right1(t), lvl - 1);
		}
	}
}

//restituisce l altezza di un albero
int height1(treeval t)
{
	if (empty1(t)) return 0;
	if (empty1(left1(t)) && empty1(right1(t))) return 0;
	else {
		int hl = height1(left1(t)), hr = height1(right1(t));
		return 1 + (hl > hr ? hl : hr);
	}
}

//vista in AMPIEZZA
void visitaInAmpiezza1(treeval t) {
	printf("\n Visita in ampiezza:\n");
	int h = height1(t);
	for (int i = 0; i <= h; i++) {
		stampalvl1(t, i);
		printf("\n");
	}
	printf("\n");
}

//_______________________________________________SECONDARIE ______________________________________

//true se l elemento passato e' parte dell albero
bool memberTree1(valore e, treeval t) {
	if (empty1(t)) return false;
	else if (isEqual1(e, root1(t))) return true;
	else return (memberTree1(e, left1(t)) || memberTree1(e, right1(t)));
}

//creare un albero con inserimento da tastiera
//si ferma quando si inserisce un ID = 0
treeval createTree1(void) {
	valore e;
	valore stop;  /* arbitrario */
	stop.id = 0;
	printf("Inserisci elemento:\t");
	e = getEl1();

	if (isEqual1(e, stop)) return emptyTree1();
	else {
		treeval l, r;
		l = createTree1();
		r = createTree1();
		return consTree1(e, l, r);
	}
}

//_______________________________________________ALBERI BST______________________________________

//inserisce l elemento passato nell albero (in ordine), in base al PARAMETRO di e
treeval insOrdTree1(valore e, treeval t) {
	if (empty1(t)) {
		return consTree1(e, emptyTree1(), emptyTree1());
	}
	if (isLess1(e, root1(t)) || isEqual1(e, root1(t)))
	{
		return consTree1(root1(t), insOrdTree1(e, left1(t)), right1(t));
	}
	return consTree1(root1(t), left1(t), insOrdTree1(e, right1(t)));
}

//restituisce true se e fa parte dell albero
bool memberTreeOrd1(valore e, treeval t) {
	if (empty1(t)) return false;
	if (isEqual1(e, root1(t))) return true;
	if (isLess1(e, root1(t)))
	{
		return memberTreeOrd1(e, left1(t));
	}
	return memberTreeOrd1(e, right1(t));
}

treeval DeleteElement1(treeval t, valore e)
{

	treeval l = t;
	treeval next = emptyTree1();
	treeval pl = emptyTree1();
	treeval pr = emptyTree1();
	//cerco l'elemento salvandomi il padre(pl e pr) sapendo se e' figlio dx o sx
	while (!empty1(t)) {
		if (isEqual1(root1(t), e)) break;
		if (isLess1(e, root1(t))) {
			pl = t;
			pr = emptyTree1();
			t = left1(t);
		}
		else {
			pl = emptyTree1();
			pr = t;
			t = right1(t);
		}
	}
	//Eliminazione vera e propria solo sel'ho trovato
	if (!empty1(t))
	{
		// Il nodo da eliminare e' una foglia
		if (empty1(left1(t)) && empty1(right1(t))) {
			// Se e' la root ritorno un albero vuoto
			if (t == l)
			{
				//free(t);
				return emptyTree1();
			}
			if (!empty1(pl)) //se è figlio sinistro metto che il padre ha figlio empty
			{
				pl->left = emptyTree1();
			}
			else //se è figlio destrp metto che il padre ha figlio empty
			{
				pr->right = emptyTree1();
			}
			//next = emptyTree();
		}
		// Il nodo da eliminare ha un solo figlio destro
		else if (empty1(left1(t))) {
			// Se e' la root ritorno il figlio
			if (t == l) return right1(t);
			next = right1(t);
			if (!empty1(pl)) pl->left = next; //se è figlio sinistro metto che il padre ha come figlio sx l'unico figlio dx del nodo
			else pr->right = next;
		}
		else if (empty1(right1(t))) {
			// Se e' la root ritorno il figlio
			if (t == l)
			{
				return left1(t);
			}
			next = left1(t);
			if (!empty1(pl)) pl->left = next;
			else pr->right = next;
		}

		else {
			// Il nodo da eliminare ha due figli
			pr = t;
			pl = emptyTree1();
			next = right1(t); //selezioniamo il figlio destro del nodo
			if (!empty1(next))
				while (!empty1(left1(next))) { //scendiamo tutto a sinistra
					pr = emptyTree1();
					pl = next;
					next = left1(next);
				}
			t->val = root1(next); // assegnamo al nodo il valore del figlio minore 
			if (right1(next) != NULL) {
				next = right1(next); //chiamo next il nodo che è figlio eventuale del nodo prescelto cosi trovato (può avere solo figlio destro)
			}
			else next = emptyTree1();
		}
		//attacchiamo il padre del nodo che ho sostituito  al figlio destro di next
		if (!empty1(pl))
		{
			//free(pl->left);
			pl->left = next;
		}
		//vuol dire che il nodo da eliminare ha un solo figlio destro
		if (!empty1(pr))
		{
			//free(pr->right);
			pr->right = next;
		}
	}
	return l;
}

// costruisce un albero leggendo i dati da un file aperto passato
treeval BSTread1(FILE *f)
{
	treeval t = emptyTree1();
	valore e;
	//element stop; /* arbitrario */
	//stop.valore = 0;
	while (1)
	{
		int ctrl = fscanf(f, "%d", &e.id);
		if (feof(f) || ctrl != 1)
			break;

		t = insOrdTree1(e, t);
	}
	return t;
}

//crea un albero prendendo valori da stdinput
//termina con id = 0
treeval CreaAlberoBST1()
{
	treeval t = emptyTree1();
	valore e;
	valore stop;
	stop.id = 0;
	printf("\nCreazione alberoBST:\n");
	while (1) {
		printf("inserisci valore:\t");
		scanf("%d", &e.id);
		if (isEqual1(e, stop))
			break;
		t = insOrdTree1(e, t);
	}
	return t;
}

//confronta tutti i valori dei due elementi per vedere se sono diversi
bool diversi1(valore e1, valore e2) {
	if (e1.id != e2.id)
		return true;
	return false;
}

//delete element degli alberi normali
treeval delete1(treeval t, valore e) {
	treeval l = t, next;
	treeval pl = NULL, pr = NULL;
	while (diversi1(root1(t), e) && !empty1(t)) {
		if (e.id < root1(t).id) {
			pl = t;
			pr = emptyTree1();
			t = left1(t);
		}
		else {
			pl = emptyTree1();
			pr = t;
			t = right1(t);
		}
	}
	//printf("\ntrovato %d", root(t));
	if (!empty1(t)) {
		// Il nodo da eliminare  una foglia
		if (empty1(left1(t)) && empty1(right1(t))) {
			// Se e' la root ritorno un albero vuoto
			if (t == l)
				return emptyTree1();
			next = emptyTree1();
		}
		else {
			// Il nodo da eliminare ha un solo figlio
			if (empty(left1(t))) {
				// Se e' la root ritorno il figlio
				if (t == l)
					return right1(t);
				next = right1(t);
			}
			else {
				if (empty(right1(t))) {
					// Se e' la root ritorno il figlio
					if (t == l)
						return left1(t);
					next = left1(t);
				}
				else {
					// Il nodo da eliminare ha due figli
					pr = t;
					pl = emptyTree1();
					next = right1(t);
					if (!empty1(next))
						while (!empty1(left1(next))) {
							pr = emptyTree1();
							pl = next;
							next = left1(next);
						}
					t->val = root1(next);
					if (right1(next) != NULL) {
						next = right1(next);
					}
					else
						next = emptyTree1();
				}
			}
		}
		if (!empty1(pl))
			pl->left = next;
		if (!empty1(pr))
			pr->right = next;
	}
	return l;
}

//La funziona ritorna empty treeval in caso non trovi l'elemento o l'elemento è la radice
treeval trova_padre1(treeval t, valore e) {
	if (empty1(t)) return emptyTree1();
	if (isEqual1(root1(t), e)) return emptyTree1();
	if ((!empty1(left1(t)) && isEqual1(root1(left1(t)), e)) || (!empty1(right1(t)) && isEqual1(root1(right1(t)), e))) return t;
	treeval l = trova_padre1(left1(t), e);
	treeval r = trova_padre1(right1(t), e);
	if (!empty1(l)) return l;
	if (!empty1(r)) return r;
	return emptyTree1(); // fondamentale altrimenti non ritorno nulla se non lo trovo in uno dei due rami
}

//Inserisce l elemento confrontando con un parametro di e.
treeval insertBinOrd1(valore e, treeval t) {
	treeval l = t;
	if (empty1(t))
		return consTree1(e, emptyTree1(), emptyTree1());
	while (!empty1(t)) {
		if (e.id <= root1(t).id) {
			if (empty1(left1(t))) {
				t->left = consTree1(e, emptyTree1(), emptyTree1());
				t = left1(t);
			}
			t = left1(t);
		}
		else {
			if (empty1(right1(t))) {
				t->right = consTree1(e, emptyTree1(), emptyTree1());
				t = right1(t);
			}
			t = right1(t);
		}
	}
	return l;
}

void contaDominanti1(treeval t, int *num) {
	if (!empty1(t)) {
		element l = 0, r = 0;

		if (!empty1(left1(t)))
			l = root1(left1(t)).id;

		if (!empty1(right1(t)))
			r = root1(right1(t)).id;

		if (root1(t).id >= r + l && r + l > 0) {
			(*num)++;
		}

		contaDominanti1(left1(t), num);
		contaDominanti1(right1(t), num);
	}
}