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

// Completar las funciones en C.

listaP *predecir_palabras(trie *t, char *teclas) {
	// COMPLETAR CODIGO ACA!!
}

double peso_palabra(char *palabra) {
	int i = 0, sum = 0, count = 0;
	double avg = 0;
	while(palabra[i] != '\0'){
		sum = sum + (int)palabra[i];
		count++;
	}
	if(count > 0) avg = sum/count;
	return avg;
}