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
	n->c = normalizar(c);
	n->fin = false;
	return n;
}


nodo *insertar_nodo_en_nivel(nodo **nivel, char c){
	c = normalizar(c);

	while(((*nivel) != NULL) && ((*nivel)->c < c))
		nivel = &((*nivel)->sig);

	if(((*nivel) != NULL) && ((*nivel)->c == c)){
		printf("Nodo insertado: NO\tP: %p\tHijos: %p\tSig: %p\tChar: %c\n", (void*)(*nivel), (void*)(*nivel)->hijos, (void*)(*nivel)->sig, (*nivel)->c);
		return (*nivel); //El nodo ya estaba insertado
	}

	nodo* n = nodo_crear(c);
	n->sig = *nivel;
	*nivel = n;
	printf("Nodo insertado: SI\tP: %p\tHijos: %p\tSig: %p\tChar: %c\n", (void*)(*nivel), (void*)(*nivel)->hijos, (void*)(*nivel)->sig, (*nivel)->c);
	return n;
}
*/

void trie_agregar_palabra(trie *t, char *p){
	nodo **n = &t->raiz;
	int i = 0;
	nodo* h;

	while(p[i] != '\0'){
		h = insertar_nodo_en_nivel(n,p[i]);
		n = &h->hijos;
		i++;
	}
	h->fin = true;
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
	int i = 0, sum = 0, count = 0;
	double avg = 0;
	while(palabra[i] != '\0'){
		sum = sum + (int)palabra[i];
		count++;
	}
	if(count > 0) avg = sum/count;
	return avg;
}

listaP *palabras(nodo** n, char *prefijo){
	char palabra[strlen(prefijo) + 2];
	strncpy(palabra, prefijo, strlen(prefijo) + 1);
	strncat(palabra, &(*n)->c,1);
	listaP* l = lista_crear();

	if((*n)->fin == true)
		lista_agregar(l, palabra);

	if((*n)->hijos != NULL)
		lista_concatenar(l, palabras(&(*n)->hijos, palabra));

	if((*n)->sig != NULL)
		lista_concatenar(l, palabras(&(*n)->sig, prefijo));

	return l;
}