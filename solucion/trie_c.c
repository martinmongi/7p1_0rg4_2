#include "trie.h"
#include "listaP.h"

//Funciones para pasar a ASM

listaP *palabras(nodo** n, char *prefijo){

	int len = strlen(prefijo);
	listaP* l = lista_crear();

	if((*n) == NULL) return l;

	prefijo[len] = (*n)->c;
	prefijo[len + 1] = '\0';

	if((*n)->fin == true)
		lista_agregar(l, prefijo);

	if((*n)->hijos != NULL)
		lista_concatenar(l, palabras(&(*n)->hijos, prefijo));

	prefijo[len] = '\0';

	if((*n)->sig != NULL)
		lista_concatenar(l, palabras(&(*n)->sig, prefijo));

	return l;
}

listaP *palabras_con_prefijo(trie *t, char *pref){
	nodo* n = nodo_prefijo(t->raiz, pref);
	listaP* l = lista_crear();
	if(n == NULL) return l;
	if(n->fin == true) lista_agregar(l,pref);
	lista_concatenar(l,palabras(&n->hijos,pref));
	return l;
}

double trie_pesar(trie *t, double (*funcion_pesaje)(char*)){
	
	char string[1024];
	double sum = 0, count = 0;
	string[0] = '\0';
	listaP* l = palabras(&(t->raiz),string);
	lsnodo* lscan = l->prim;
	while(lscan != NULL){
		sum += (*funcion_pesaje)(lscan->valor);
		count++;
		lscan = lscan->sig;
	}
	lista_borrar(l);
	return sum/count;
}

// Completar las funciones en C.

listaP *predecir_palabras(trie *t, char *teclas) {
	listaP *l = lista_crear();
	// COMPLETAR CODIGO ACA!!
}

double peso_palabra(char *palabra) {
	int count = 0;
	double sum = 0, avg = 0;
	while(palabra[count] != '\0'){
		sum = sum + (int)palabra[count];
		count++;
	}
	if(count > 0) avg = sum/count;
	return avg;
}

