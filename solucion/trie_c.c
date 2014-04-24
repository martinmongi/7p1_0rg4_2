#include "trie.h"
#include "listaP.h"

//Funciones para pasar a ASM

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
	char tecla = teclas[0];
	nodo *n = t->raiz;
	return l;
	// COMPLETAR CODIGO ACAA!!!

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

