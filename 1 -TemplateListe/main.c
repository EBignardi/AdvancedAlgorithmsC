#include "liste.h"

int main(void) {

	list lista = emptylist();

	for (int i = 0; i < 10; i++) {
		lista = cons(rand(), lista);
	}

	printf("Lista: ");
	showlist(lista);

	return;
}