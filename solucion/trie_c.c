#include "trie.h"
#include "listaP.h"

//Funciones para pasar a ASM

// Completar las funciones en C.

listaP *palabras_con_prefijo(trie *t, char *pref){
	char str[1024];
	nodo* n = nodo_prefijo(t->raiz, pref);
	listaP* l = lista_crear();
	if(n == NULL) return l;
	if(n->fin) lista_agregar(l,pref);
	listaP * lista_sufijos = palabras(&n->hijos,pref);
	lsnodo * lscan = lista_sufijos->prim;
	while(lscan != NULL){
		str[0] = '\0';
		strcpy(str,pref);
		strcat(str,lscan->valor);
		lista_agregar(l,str);
		lscan = lscan->sig;
	}
	lista_borrar(lista_sufijos);
	return l;
}

//CHOTEA POR PALABRAS CON PREFIJO
listaP *predecir_palabras(trie *t, char *teclas) {

	listaP *l = lista_crear();
	char str[1024];
	str[0] = '\0';
	combinar(teclas,str,l,0);
	
	lsnodo *lscan = l->prim;
	listaP *listaFinal = lista_crear();
	while(lscan != NULL){
		listaP *lTemp = palabras_con_prefijo(t, lscan->valor);
		lista_concatenar(listaFinal, lTemp);
		lscan = lscan->sig;
	}
	lista_borrar(l);
	return listaFinal;

}

//OK
void combinar(char *teclas, char* pref, listaP* l, int i){
	if(i == (int)strlen(teclas)){
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

//OK
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

