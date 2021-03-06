#ifndef _T9_H_
#define _T9_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "listaP.h"

typedef struct nodo_t {
	struct nodo_t *sig;
	struct nodo_t *hijos;
	char c;
	bool fin;
} __attribute__((packed)) nodo;

typedef struct trie_t {
	nodo *raiz;
} __attribute__((packed)) trie;

#ifdef __cplusplus 
extern "C" {
#endif

/* Funciones basicas */
double peso_palabra(char *palabra);
trie *trie_crear(void);
void trie_borrar(trie *t);
nodo *nodo_crear(char c);
nodo *insertar_nodo_en_nivel(nodo **nivel, char c);
void trie_agregar_palabra(trie *t, char *p);
trie *trie_construir(char *nombre_archivo);
void trie_imprimir(trie *t, char *nombre_archivo);


/* Funciones Avanzadas */
bool buscar_palabra(trie *t, char *p);
double trie_pesar(trie *t, double (*funcion_pesaje)(char*));
listaP *palabras_con_prefijo(trie *t, char *pref);
listaP *predecir_palabras(trie *t, char *teclas);
const char *caracteres_de_tecla(char tecla);

/* Funciones Auxiliares */
void nodo_borrar(nodo *n);
char normalizar(char c);
listaP *palabras(nodo **n, char *prefijo);
nodo *nodo_prefijo(nodo *n, char *p);
nodo *nodo_buscar(nodo *n, char c);
void combinar(char *teclas, char* pref, listaP* l, int i);
void reset_string();
int str_len(char* str);
void str_cpy(char* des, char* str);
void str_cat(char* des, char* str);

#ifdef __cplusplus 
}
#endif

#endif //_T9_H_
