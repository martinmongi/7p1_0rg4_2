#include "trie.h"
#include "listaP.h"

//Funciones para pasar a ASM

// double trie_pesar(trie *t, double (*funcion_pesaje)(char*)){
	
// 	char string[1024];

// 	string[0] = '\0';
// 	listaP* l = palabras(&(t->raiz),string);
// 	lsnodo* lscan = l->prim;

// 	double sum = 0
// 	int count = 0;
	

// 	while(lscan != NULL){
// 		sum += (*funcion_pesaje)(lscan->valor);
// 		count++;
// 		lscan = lscan->sig;
// 	}
// 	lista_borrar(l);
// 	return sum/count;
// }

// Completar las funciones en C.

listaP *predecir_palabras(trie *t, char *teclas) {
	listaP *l = lista_crear();
	
	return l;
	// COMPLETAR CODIGO ACAA!!!

}

void combinar(char *teclas, char* pref, listaP* l, int i){
	if(i == str_len(teclas)){
		lista_agregar(l, pref);
		return;
	}
	int cant_posibles = strlen(caracteres_de_tecla(teclas[i]));
	for(int c = 0; c < cant_posibles; c++){
		pref[i] = caracteres_de_tecla(teclas[i])[c];
		pref[i+1] = '\0';
		combinar(teclas, pref, l, i+1);
	}
	pref[i] = '\0';
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

