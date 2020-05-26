#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

//________________________CONFRONTI E FUNZIONI DI APPOGGIO______________________________________
bool isEqual(professore e1, professore e2) {
	if (strcmp(e1.cognome, e2.cognome) == 0)
		return 1;
	return 0;
}

bool isLess(professore e1, professore e2) {
	if (strcmp(e1.cognome, e2.cognome)<0)
		return 1;
	return 0;
}

professore copy(professore e) {
	professore el;
	el = e;
	return el;
}
void showEl(professore e) {
	printf("L'elemento e ha valore: %s %s %d %d\n", e.cognome, e.nome, e.eta, e.id);
}

professore getEl() {
	professore e;
	printf("\n Inserire il valore da assegnare: ");
	scanf("%s %s %d %d", e.cognome, e.nome, &e.eta, &e.id);
	return e;
}

//_______________________________________________PRIMITIVE______________________________________
bool empty(tree t) {
	return (t == NULL);
}

tree emptyTree(void) {
	return NULL;
}
professore root(tree t) {
	if (empty(t))
		abort();
	else
		return t->value;
}

tree left(tree t) {
	if (empty(t)) return NULL;
	else return t->left;
}

tree right(tree t) {
	if (empty(t)) return NULL;
	else return t->right;
}

tree consTree(professore e, tree l, tree r) {
	tree t = (node*)malloc(sizeof(node));
	t->value = e;
	t->left = l;
	t->right = r;
	return t;
}
//_______________________________________________VISITE ALBERI______________________________________

void preOrder(tree t) {
	if (!empty(t)) {
		printf("\t");
		showEl(root(t));
		preOrder(left(t));
		preOrder(right(t));
	}
}

void inOrder(tree t) {
	if (!empty(t)) {
		inOrder(left(t));
		printf("\t");
		showEl(root(t));
		inOrder(right(t));
	}
}

void postOrder(tree t) {
	if (!empty(t)) {
		postOrder(left(t));
		postOrder(right(t));
		printf("\t"); showEl(root(t));
	}
}

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

int height(tree t) //altezza di un albero
{
	if (empty(t)) return 0;
	if (empty(left(t)) && empty(right(t))) return 0;
	else {
		int hl = height(left(t)), hr = height(right(t));
		return 1 + (hl>hr ? hl : hr);
	}
}

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

bool memberTree(professore e, tree t) {
	if (empty(t)) return false;
	else if (isEqual(e, root(t))) return true;
	else return (memberTree(e, left(t)) || memberTree(e, right(t)));
}

//creare un albero con inserimento da tastiera
tree createTree(void) {
	professore e;
	professore stop;  /* arbitrario */
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

//crea un albero BST dati gli  elementi
tree insOrdTree(professore e, tree t) {
	if (empty(t)) {
		return consTree(e, emptyTree(), emptyTree());
	}
	if (isLess(e, root(t)) || isEqual(e, root(t)))
	{
		return consTree(root(t), insOrdTree(e, left(t)), right(t));
	}
	return consTree(root(t), left(t), insOrdTree(e, right(t)));
}


bool memberTreeOrd(professore e, tree t) {
	if (empty(t)) return false;
	if (isEqual(e, root(t))) return true;
	if (isLess(e, root(t)))
	{
		return memberTreeOrd(e, left(t));
	}
	return memberTreeOrd(e, right(t));
}

tree DeleteElement(tree t, professore e)
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

// legge da un file aperto in modalia testo e legge interi
tree BSTread(FILE *f)
{
	tree t = emptyTree();
	professore e;
	//element stop; /* arbitrario */
	//stop.valore = 0;
	while (1)
	{
		int ctrl = fscanf(f, "%s %s %d %d", e.cognome, e.nome, &e.eta, &e.id);
		if (feof(f) || ctrl != 4)
			break;

		t = insOrdTree(e, t);
	}
	return t;
}

tree CreaAlberoBST()
{
	tree t = emptyTree();
	professore e;
	professore stop;
	stop.eta = 0;
	printf("\nCreazione alberoBST:\n");
	while (1) {
		printf("inserisci valore:\t");
		scanf("%s %s %d %d", e.cognome, e.nome, &e.eta, &e.id);
		if (isEqual(e, stop))
			break;
		t = insOrdTree(e, t);
	}
	return t;
}

bool diversi(professore e1, professore e2) {
	if (e1.cognome != e2.cognome&&e1.nome != e2.nome&&e1.eta != e2.eta&&e1.id != e2.id)
		return true;
	return false;
}

//delete element degli alberi normali
tree delete(tree t, professore e) {
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
tree trova_padre(tree t, professore e) {
	if (empty(t)) return emptyTree();
	if (isEqual(root(t), e)) return emptyTree();
	if ((!empty(left(t)) && isEqual(root(left(t)), e)) || (!empty(right(t)) && isEqual(root(right(t)), e))) return t;
	tree l = trova_padre(left(t), e);
	tree r = trova_padre(right(t), e);
	if (!empty(l)) return l;
	if (!empty(r)) return r;
	return emptyTree(); // fondamentale altrimenti non ritorno nulla se non lo trovo in uno dei due rami
}

tree insertBinOrd(professore e, tree t) {
	tree l = t;
	if (empty(t))
		return consTree(e, emptyTree(), emptyTree());
	while (!empty(t)) {
		if (e.cognome <= root(t).cognome) {
			if (empty(left(t))) {
				t->left =
					consTree(e, emptyTree(), emptyTree());
				t = left(t);
			}
			t = left(t);
		}
		else {
			if (empty(right(t))) {
				t->right =
					consTree(e, emptyTree(), emptyTree());
				t = right(t);
			}
			t = right(t);
		}
	}
	return l;
}


//_______________________________________________CONFRONTI E FUNZIONI DI APPOGGIO______________________________________
bool isEqual1(element e1, element e2) {
	if (e1 == e2)	return 1;
	return 0;
}

bool isLess1(element e1, element e2) {
	if (e1<e2)	return 1;
	return 0;
}

element copy1(element e) {
	element el;
	el = e;
	return el;
}
void showEl1(element e) {
	printf("L'elemento e ha valore: %d\n", e);
}

element getEl1() {
	element e;
	printf("\n Inserire il valore da assegnare: ");
	scanf("%d", &e);
	return e;
}

//_______________________________________________PRIMITIVE______________________________________
bool empty1(tree1 t) {
	return (t == NULL);
}

tree1 emptyTree1(void) {
	return NULL;
}
element root1(tree1 t) {
	if (empty1(t)) abort();
	else return t->value;
}

tree1 left1(tree1 t) {
	if (empty1(t)) return NULL;
	else return t->left;
}

tree1 right1(tree1 t) {
	if (empty1(t)) return NULL;
	else return t->right;
}

tree1 consTree1(element e, tree1 l, tree1 r) {
	tree1 t = (node1*)malloc(sizeof(node1));
	t->value = e;
	t->left = l;
	t->right = r;
	return t;
}

//_______________________________________________VISITE ALBERI______________________________________
void preOrder1(tree1 t) {
	if (!empty1(t)) {
		printf("\t");
		showEl1(root1(t));
		preOrder1(left1(t));
		preOrder1(right1(t));
	}
}

void inOrder1(tree1 t) {
	if (!empty1(t)) {
		inOrder1(left1(t));
		printf("\t");
		showEl1(root1(t));
		inOrder1(right1(t));
	}
}

void postOrder1(tree1 t) {
	if (!empty1(t)) {
		postOrder1(left1(t));
		postOrder1(right1(t));
		printf("\t");
		showEl1(root1(t));
	}
}
void stampalvl1(tree1 t, size_t lvl) {
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
int height1(tree1 t) //altezza di un albero
{
	if (empty1(t)) return 0;
	if (empty1(left1(t)) && empty1(right1(t))) return 0;
	else {
		int hl = height1(left1(t)), hr = height1(right1(t));
		return 1 + (hl>hr ? hl : hr);
	}
}
void visitaInAmpiezza1(tree1 t) {
	printf("\n Visita in ampiezza:\n");
	int h = height1(t);
	for (int i = 0; i <= h; i++) {
		stampalvl1(t, i);
		printf("\n");
	}
	printf("\n");
}

//_______________________________________________SECONDARIE ______________________________________

bool memberTree1(element e, tree1 t) {
	if (empty1(t)) return false;
	else if (isEqual1(e, root1(t))) return true;
	else return (memberTree1(e, left1(t)) || memberTree1(e, right1(t)));
}

//creare un albero con inserimento da tastiera
tree1 createTree1(void) {
	element e;
	element stop;  /* arbitrario */
	stop = 0;
	printf("Inserisci elemento:\t");
	e = getEl1();

	if (isEqual1(e, stop)) return emptyTree1();
	else {
		tree1 l, r;
		l = createTree1();
		r = createTree1();
		return consTree1(e, l, r);
	}
}



//_______________________________________________ALBERI BST______________________________________

//crea un albero BST dati gli  elementi
tree1 insOrdTree1(element e, tree1 t) {
	if (empty1(t)) {
		return consTree1(e, emptyTree1(), emptyTree1());
	}
	if (isLess1(e, root1(t)) || isEqual1(e, root1(t)))
	{
		return consTree1(root1(t), insOrdTree1(e, left1(t)), right1(t));
	}
	return consTree1(root1(t), left1(t), insOrdTree1(e, right1(t)));
}

bool memberTreeOrd1(element e, tree1 t) {
	if (empty1(t)) return false;
	if (isEqual1(e, root1(t)))
		return true;
	if (isLess1(e, root1(t)))
	{
		return memberTreeOrd1(e, left1(t));
	}
	return memberTreeOrd1(e, right1(t));
}

tree1 DeleteElement1(tree1 t, element e)
{

	tree1 l = t;
	tree1 next = emptyTree1();
	tree1 pl = emptyTree1();
	tree1 pr = emptyTree1();
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
			t->value = root1(next); // assegnamo al nodo il valore del figlio minore 
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
// legge da un file aperto in modalia testo e legge interi
tree1 BSTread1(FILE *f)
{
	tree1 t = emptyTree1();
	element e;
	//element stop; /* arbitrario */
	//stop.valore = 0;
	while (1)
	{
		int ctrl = fscanf(f, "%d", &e);
		if (feof(f) || ctrl != 1)
			break;

		t = insOrdTree1(e, t);
	}
	return t;
}
tree1 CreaAlberoBST1()
{
	tree1 t = emptyTree1();
	element e;
	element stop;
	stop = 0;
	printf("\nCreazione alberoBST:\n");
	while (1) {
		printf("inserisci valore:\t");
		scanf("%d", &e);
		if (isEqual1(e, stop))
			break;
		t = insOrdTree1(e, t);
	}
	return t;
}


//delete element degli alberi normali
tree1 delete1(tree1 t, element e) {
	tree1 l = t, next;
	tree1 pl = NULL, pr = NULL;
	while (root1(t) != e && !empty1(t)) {
		if (e < root1(t)) {
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
			if (empty1(left1(t))) {
				// Se e' la root ritorno il figlio
				if (t == l)
					return right1(t);
				next = right1(t);
			}
			else {
				if (empty1(right1(t))) {
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
					t->value = root1(next);
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
//La funziona ritorna empty tree in caso non trovi l'elemento o l'elemento è la radice
tree1 trova_padre1(tree1 t, element e) {
	if (empty1(t)) return emptyTree1();
	if (isEqual1(root1(t), e)) return emptyTree1();
	if ((!empty1(left1(t)) && isEqual1(root1(left1(t)), e)) || (!empty1(right1(t)) && isEqual1(root1(right1(t)), e))) return t;
	tree1 l = trova_padre1(left1(t), e);
	tree1 r = trova_padre1(right1(t), e);
	if (!empty1(l)) return l;
	if (!empty1(r)) return r;
	return emptyTree1(); // fondamentale altrimenti non ritorno nulla se non lo trovo in uno dei due rami
}

tree1 insertBinOrd1(element e, tree1 t) {
	tree1 l = t;
	if (empty1(t))
		return consTree1(e, emptyTree1(), emptyTree1());
	while (!empty1(t)) {
		if (e <= root1(t)) {
			if (empty1(left1(t))) {
				t->left =
					consTree1(e, emptyTree1(), emptyTree1());
				t = left(t);
			}
			t = left(t);
		}
		else {
			if (empty1(right1(t))) {
				t->right =
					consTree1(e, emptyTree1(), emptyTree1());
				t = right(t);
			}
			t = right(t);
		}
	}
	return l;
}