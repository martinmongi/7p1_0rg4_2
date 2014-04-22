#include <stdio.h>
#include "trie.h"

int main(void) {
	trie* t = trie_crear();
	insertar_nodo_en_nivel(&(t->raiz),'a');
	insertar_nodo_en_nivel(&(t->raiz),'b');
	insertar_nodo_en_nivel(&(t->raiz),'c');
	trie_imprimir(t,"trie.out");
	trie_borrar(t);

    return 0;
}

