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

nodo *nodo_crear(char c){
	nodo* n = malloc(sizeof(nodo));
	n->sig = NULL;
	n->hijos = NULL;
	if(c < '0')
		n->c = 'a';
	else if(c <= '9')
		n->c = c;
	else if(c < 'A')
		n->c = 'a';
	else if(c <= 'Z')
		n->c = c + 32;
	else if(c < 'a')
		n->c = 'a';
	else if(c <= 'z')
		n->c = c;
	else
		n->c = 'a';
	n->fin = false;
	return n;
}
*/

nodo *insertar_nodo_en_nivel(nodo **nivel, char c){
	while((*nivel) != NULL)
		nivel = &((*nivel)->sig); 
	nodo* n = nodo_crear(c);
	*nivel = n;
	return n;
}

/*
void nodo_borrar(nodo* n){
	if(n == NULL) return;
	nodo_borrar(n->hijos);
	nodo_borrar(n->sig);
	free(n);
}
*/

// Completar las funciones en C.

listaP *predecir_palabras(trie *t, char *teclas) {
	// COMPLETAR AQUI EL CODIGO
}

double peso_palabra(char *palabra) {
	// COMPLETAR AQUI EL CODIGO
}
