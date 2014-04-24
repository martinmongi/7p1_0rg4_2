#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

int main(void) {
	trie* t = trie_crear();
	trie_agregar_palabra(t,"casa");
	trie_agregar_palabra(t,"casco");
	trie_agregar_palabra(t,"ala");
	trie_agregar_palabra(t,"cama");
	trie_imprimir(t,"trie.out");
	char* prefijo = malloc(1024);
	prefijo[0] = '\0';
	listaP* l = palabras(&t->raiz, prefijo);
	lista_imprimir(l);
	lista_borrar(l);
	trie_borrar(t);
	free(prefijo);

    return 0;
}

