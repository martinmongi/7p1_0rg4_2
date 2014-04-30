#include "trie.h"
#include "listaP.h"

listaP *predecir_palabras(trie *t, char *teclas) {


	//printf(" QUIERO PREDECIR: %s\n",teclas);
	listaP *l = lista_crear();
	char str[1024];
	str[0] = (char)0;
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
	if(i == (int)str_len(teclas)){
		lista_agregar(l, pref);
		return;
	}
	int cant_posibles = str_len(caracteres_de_tecla(teclas[i]));
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

