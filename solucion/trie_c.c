#include "trie.h"
#include "listaP.h"

//Funciones para pasar a ASM

/*
trie *trie_crear(void){
	trie* t = malloc(sizeof(trie));
	return t;
}

void trie_borrar(trie *t){
	free(t);
}

void trie_imprimir(trie *t, char *nombre_archivo){
	FILE *f;
	f = fopen(nombre_archivo, "a");
	if(t->raiz == NULL)
		fprintf(f, "<vacio> \n");
	fclose(f);
}
*/

// Completar las funciones en C.

listaP *predecir_palabras(trie *t, char *teclas) {
	// COMPLETAR AQUI EL CODIGO
}

double peso_palabra(char *palabra) {
	// COMPLETAR AQUI EL CODIGO
}
