#include <stdio.h>
#include <stdlib.h>


typedef  int  element;

typedef struct	treeElement {
	element	value;
	struct treeElement  *left, *right;
} node;

typedef  node *tree;

typedef  enum {false, true} boolean;


void showEl(char a) {

	printf("%d", a);
}

boolean empty(tree t) {	return (t==NULL); }

tree emptyTree(void) {	return NULL; }

element root(tree t){
	if (empty(t)) abort();
	else return t->value;
}

tree left(tree t){
	if (empty(t)) return NULL;
	else return t->left;
}

tree right(tree t){
	if (empty(t)) return NULL;
	else return t->right;
}

tree consTree(element e, tree l, tree r) {
 	tree t = (node*) malloc(sizeof(node));
   	t->value = e;
  	t->left = l;	t->right = r;
	return t;
}



void preOrder(tree t) {
  if (!empty(t)) {
	printf("\t"); showEl(root(t));
	preOrder(left(t)); preOrder(right(t));
  }
}

void inOrder(tree t) {
  if (!empty(t)) {
	inOrder(left(t));
	printf("\t"); showEl(root(t));
	inOrder(right(t));
  }
}


void postOrder(tree t) {
  if (!empty(t)) {
    postOrder(left(t)); postOrder(right(t));
    printf("\t"); showEl(root(t));
  }
}


tree succ(tree t){
	t = right(t);
	if (!empty(t))
	    while(!empty(left(t))){
			t= left(t);
		}
	return t;
	}

tree copy(tree t){

	return consTree(root(t),emptyTree(),emptyTree());
}

tree delete(tree t, element e){

	tree l=t, s, next;
	tree pl= NULL, pr=NULL;

	while (root(t) != e && !empty(t)) {
		if (e < root(t)){
			pl = t;
			pr = emptyTree();
			t = left(t);
		} else {
			pl = emptyTree();
			pr = t;
			t = right(t);
		}
	}

	//printf("\ntrovato %d", root(t));
	if (!empty(t)){

		// Il nodo da eliminare è una foglia
		if (empty(left(t)) && empty(right(t))){
			// Se e' la root ritorno un albero vuoto
			if(t==l)
				return emptyTree();
			next = emptyTree();

		} else {
			// Il nodo da eliminare ha un solo figlio
			if (empty(left(t))) {
				// Se e' la root ritorno il figlio
				if(t==l)
					return right(t);
				next = right(t);
			} else {
				if (empty(right(t))) {
					// Se e' la root ritorno il figlio
					if(t==l)
						return left(t);
					next = left(t);
				} else {
				// Il nodo da eliminare ha due figli

					pr = t;
					pl = emptyTree();

					next = right(t);
					if (!empty(next))
					    while(!empty(left(next))){
							pr = emptyTree();
							pl = next;
							next= left(next);
						}
					t->value = root(next);
					if (right(next) != NULL) {
						next = right(next);
					} else
						next = emptyTree();
				}
			}

		}

		if(!empty(pl))
			pl->left = next;

		if(!empty(pr))
			pr->right = next;

	}

	return l;

}


tree insertBinOrd(element e, tree t){

	tree l = t;

	if (empty(t))
		return consTree(e,emptyTree(),emptyTree());

	while (!empty(t)) {
		if (e >= root(t)){
			if (empty(left(t))){
				t->left = consTree(e,emptyTree(),emptyTree());
				t = left(t);
			}
			t = left(t);
		} else {
			if (empty(t->right)){
				t->right = consTree(e,emptyTree(),emptyTree());
				t = right(t);
			}
			t = right(t);
		}
	}

	return l;
}


typedef int  element;
boolean isEqual(element e1,element e2) {
return (e1 == e2);}
boolean isLess(element e1, element e2) {
return (e1 < e2);}
element copyL(element e){
element el;
el=e;
return el;}
element getElement(){
element el;
scanf("%d", &el);
return el;}
void printElement(element el){
printf("%d", el);}

typedef struct list_element {
element value;
struct list_element *next;
} item;
typedef  item* list;


list emptylist() { return NULL; }
boolean emptyL(list l) { return (l==NULL); }
element head(list l) {
if (emptyL(l)) abort();
else return  l->value;}
list tail(list l) {
if (emptyL(l)) abort();
else return l->next; }


list  cons(element e, list l) {
list t;
t = (list) malloc(sizeof(item));
t->value=copyL(e);
t->next=l;
return t;}


void showlist(list l) {
printf("[");
while (!emptyL(l)) {
printElement(head(l));
l = tail(l);
if (!emptyL(l)) printf(", ");
}
printf("]\n");}




list costruisciLista(tree t, list l) {


  if (!empty(t)) {
	l = costruisciLista(left(t),l);
    l = cons(root(t),l);
	l = costruisciLista(right(t),l);
  }

  return l;


}


void main () {
	tree t1;
	FILE *f;
	element el;
	list l= NULL;

	f = fopen("../Valori2.txt", "r");
	if (f == NULL) {
		printf("Errore Apertura file");
		return;
	}
	t1 = emptyTree();

	while (fscanf(f, "%d", &el)>0) {
		t1 = insertBinOrd(el, t1);
	}

  printf("\nVisita in ordine anticipato\n");
  preOrder(t1);
  printf("\nVisita in ordine\n");
  inOrder(t1);
  printf("\nVisita in ordine posticipato\n");
  postOrder(t1);


  l = costruisciLista(t1, l);

  printf("\nMostra la Lista\n");
  showlist(l);

}

