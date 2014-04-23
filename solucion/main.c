#include <stdio.h>
#include "trie.h"

int main(void) {
	trie* t = trie_crear();
	trie_agregar_palabra(t,"casa");
	trie_agregar_palabra(t,"casco");
	trie_agregar_palabra(t,"ala");
	trie_agregar_palabra(t,"cama");
	trie_imprimir(t,"trie.out");
	trie_borrar(t);

    return 0;
}

