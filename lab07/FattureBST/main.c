#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef char stringa[20];

typedef struct
{
	int CodArt;
	stringa Descrizione;
	stringa Tipologia;
} Articolo;

typedef struct
{
	int CodFatt;
	char Data[11];
	stringa TipoPagamento;
	int IVA;
	char PIVA[16];
} Fattura;

typedef struct
{
	int CodFatt;
	int NRiga;
	int CodArt;
	int Quantita;
	float PrezzoUnitario;
} RigaFattura;


typedef struct nodea_
{
	Articolo a;
	struct nodea_ *left;
	struct nodea_ *right;
} nodea;

typedef nodea *treea;

typedef struct nodel_
{
	struct nodel_ *next;
	RigaFattura r;

}nodel;

typedef nodel* list;

typedef struct nodef_
{
	Fattura f;
	list l;
	struct nodef_ *left;
	struct nodef_ *right;
} nodef;

typedef nodef* treef;

bool isLess(RigaFattura e1, RigaFattura e2) {
	return (e1.NRiga < e2.NRiga);
}

RigaFattura copy(RigaFattura e) {
	RigaFattura el;
	el = e;
	return el;
}

bool empty(list l) {
	return (l == NULL);
}

RigaFattura head(list l) {
	if (empty(l)) abort();
	else
		return  l->r;
}

list tail(list l) {
	if (empty(l)) abort();
	else
		return l->next;
}

list  cons(RigaFattura e, list l) {
	list t;
	t = (list)malloc(sizeof(nodel));
	t->r = copy(e);
	t->next = l;
	return t;
}

// primitive BST degli articoli

bool isLessArticolo(Articolo e1, Articolo e2) {
	return (e1.CodArt < e2.CodArt);
}

treea emptyTreeArticolo(void) { return NULL; }
bool emptyArticolo(treea t) { return (t == NULL); }

treea leftArticolo(treea t) {
	if (emptyArticolo(t)) return NULL;
	else return t->left;
}

treea rightArticolo(treea t) {
	if (emptyArticolo(t)) return NULL;
	else return t->right;
}


//bool empty(tree t) { return (t == NULL); }



Articolo rootArticolo(treea t) {
	if (emptyArticolo(t)) abort();
	else return t->a;
}

treea consTreeArticolo(Articolo e, treea l, treea r) {
	treea t = (nodea*)malloc(sizeof(nodea));
	t->a = e;
	t->left = l;	t->right = r;
	return t;
}

// fine primitive BST degli articoli


// inserimento ordinato in BST degli articoli
treea inserisciArticolo(Articolo a, treea t)
{
	treea k, n, father;

	k = consTreeArticolo(a, emptyTreeArticolo(), emptyTreeArticolo());

	if (emptyArticolo(t))
		return k;

	n = t;
	father = n;
	while (!emptyArticolo(n))
	{
		father = n;
		if (isLessArticolo(n->a, a))
			n = rightArticolo(n);
		else
			n = leftArticolo(n);
	}

	if (isLessArticolo(father->a, a))
		father->right = k;
	else
		father->left = k;

	return t;
}





// primitive BST Fatture

bool isLessFattura(Fattura e1, Fattura e2) {

	if (strcmp(e1.PIVA, e2.PIVA)<0)
		return 1;

	return 0;
}

treef emptyTreeFattura(void) { return NULL; }

bool emptyFattura(treef t) { return (t == NULL); }

treef leftFattura(treef t) {
	if (emptyFattura(t)) return NULL;
	else return t->left;
}

treef rightFattura(treef t) {
	if (emptyFattura(t)) return NULL;
	else return t->right;
}



Fattura rootFattura(treef t) {
	if (emptyFattura(t)) abort();
	else return t->f;
}

treef consTreeFattura(Fattura e, treef l, treef r) {

	treef t = (nodef*)malloc(sizeof(nodef));
	t->f = e;
	t->l = NULL;
	t->left = l;	t->right = r;
	return t;
}

// fine primitive BST Fatture

// inserimento ordinato in BST degli articoli
treef inserisciFattura(Fattura f, treef t)
{
	treef k, n, father;

	k = consTreeFattura(f, emptyTreeFattura(), emptyTreeFattura());

	if (emptyFattura(t))
		return k;

	n = t;
	father = n;
	while (!emptyFattura(n))
	{
		father = n;
		if (isLessFattura(n->f, f))
			n = rightFattura(n);
		else
			n = leftFattura(n);
	}

	if (isLessFattura(father->f, f))
		father->right = k;
	else
		father->left = k;

	return t;
}


list inserisciRiga(RigaFattura e, list l) {

	list l1 = NULL, root = l;
	list t;

	t = cons(e, l);

	if (empty(l) || !isLess(head(l), e))
		return t;

	while (!empty(l) && isLess(head(l), e)) {
		l1 = l;
		l = tail(l);
	}

	l1->next = t;
	t->next = l;

	return root;

}


void scriviRigaFattura(RigaFattura r, treef t)
{
	if (t == NULL)
		return;
	if (r.CodFatt == t->f.CodFatt)
	{
		t->l = inserisciRiga(r, t->l);
		return;
	}
	scriviRigaFattura(r, t->left);
	scriviRigaFattura(r, t->right);
}

treea leggiArticoli(stringa nome_file)
{
	Articolo a;
	treea ta;
	FILE *f;
	ta = NULL;

	f = fopen(nome_file, "rb");
	if (f == NULL)
		return NULL;
	while (fread(&a, sizeof(Articolo), 1, f) > 0)
	{
		ta = inserisciArticolo(a, ta);
	}
	fclose(f);
	return ta;
}


treef leggiFatture(stringa nome_file)
{
	Fattura fatt;
	treef tf;
	FILE *f;
	tf = NULL;

	f = fopen(nome_file, "rb");
	if (f == NULL)
		return NULL;
	printf("Fatture presenti: \n");
	while (fread(&fatt, sizeof(Fattura), 1, f) > 0)
	{
		printf("PIVA: %s\n", fatt.PIVA);
		tf = inserisciFattura(fatt, tf);

	}
	fclose(f);
	return tf;
}

treef leggiRighe(treef tf, stringa nome_file)
{
	RigaFattura r;
	FILE *f;
	f = fopen(nome_file, "rb");
	if (f == NULL)
		return NULL;
	while (fread(&r, sizeof(RigaFattura), 1, f) > 0)
	{
		scriviRigaFattura(r, tf);
	}
	fclose(f);
	return tf;
}


Articolo ricercaArticolo(treea ta, int CodArt)
{
	Articolo a;

	treea n;
	n = ta;
	while (n != NULL)
	{
		if (CodArt == n->a.CodArt)
		{
			a = n->a;
			n = NULL;
		}
		else
			if (CodArt > n->a.CodArt)
				n = rightArticolo(n);
			else
				n = leftArticolo(n);
	}
	return a;
}


void stampaRiga(RigaFattura r, treea ta)
{
	Articolo a;
	a = ricercaArticolo(ta, r.CodArt);
	printf("n Riga %d\t Descrizione: %s Tipologia: %s, Quantita: %d PrezzoUnitario: %f\n", r.NRiga, a.Descrizione, a.Tipologia, r.Quantita, r.PrezzoUnitario);

}

void stampaSingolaFattura(nodef* n, treea ta)
{
	Fattura f;
	list l;


	f = n->f;
	printf("Codice %d Data %s TipoPagamento %s IVA %d PIVA %s\n", f.CodFatt, f.Data, f.TipoPagamento, f.IVA, f.PIVA);

	l = n->l;
	while (!empty(l))
	{
		stampaRiga(l->r, ta);
		l = tail(l);
	}
}


void stampaFatture(stringa piva, treef tf, treea ta)
{

	treef n;
	n = tf;
	while (!emptyFattura(n) && strcmp(n->f.PIVA, piva) != 0)
	{
		if (strcmp(piva, n->f.PIVA) > 0)
			n = rightFattura(n);
		else
			n = leftFattura(n);
	}
	if (emptyFattura(n))
		return;


	stampaSingolaFattura(n, ta);

	stampaFatture(piva, leftFattura(n), ta);
	stampaFatture(piva, rightFattura(n), ta);

}

/*
// DA COMPLETRE PER UN INSERIMENTO SU FILE
void inserisciDati(void)
{
FILE *f1;
Fattura f;
RigaFattura r;
Articolo a;

f1 = fopen("fatture.dat", "ab");
if (f1 == NULL)
return;
do{
printf("Inserisci fattura:\n");
printf("CodFatt(int): ");
printf("Data(string): ");
printf("TipoPagamento(string): ");
printf("IVA(int): ");
printf("PIVA(string): ");
scanf("%d", &f.CodFatt);
scanf("%s", f.Data);
scanf("%s", f.TipoPagamento);
scanf("%d", &f.IVA);
scanf("%s", f.PIVA);
fwrite(&f, sizeof(Fattura), 1, f1);
} while (f.IVA > 0);

fclose(f1);



return;
}
*/



int main()
{
	treef tf;
	treea ta;
	stringa piva;

	//inserisciDati();
	tf = leggiFatture("fatture.dat");
	if (tf == NULL)
		return -1;

	tf = leggiRighe(tf, "righefattura.dat");
	if (tf == NULL)
		return -1;

	ta = leggiArticoli("articoli.dat");
	if (ta == NULL)
		return -1;

	printf("Di che Partita iva vuoi i dati?\t");
	scanf("%s", piva);

	printf("\nElenco fatture con PIVA: %d:\n", piva);
	stampaFatture(piva, tf, ta);

	printf("\nPremi un tasto per terminare");
	getchar();
	getchar();
	return 0;
}