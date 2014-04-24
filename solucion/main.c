#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

char prefijo[1024];

int main(void) {
	// trie* t = trie_crear();
	// trie_agregar_palabra(t,"casa");
	// trie_agregar_palabra(t,"casco");
	// trie_agregar_palabra(t,"ala");
	// trie_agregar_palabra(t,"cama");
	trie *t = trie_construir("trie.in");
	trie_imprimir(t,"trie.out");

	if(buscar_palabra(t, "ala")) printf("BIEN\n");
	else printf("TODO MAL MEN\n");

	prefijo[0] = '\0';
	listaP* l = palabras(&t->raiz, prefijo);
	lista_imprimir(l);
	lista_borrar(l);
	trie_borrar(t);

    return 0;
}

