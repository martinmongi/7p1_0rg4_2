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

void nodo_borrar(nodo* n){
	if(n == NULL) return;
	nodo_borrar(n->hijos);
	nodo_borrar(n->sig);
	free(n);
}

nodo *nodo_buscar(nodo* n, char c){
	while((n != NULL) && (n->c != c)){
		n = n->sig;
	}
	return n;
}


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

bool buscar_palabra(trie *t, char *p){
	nodo* n = nodo_prefijo(t->raiz,p);
	return (n != NULL) && (n->fin == true);
}

void trie_imprimir(trie *t, char *nombre_archivo){
	char prefijo[1024];
	prefijo[0] = '\0';
	FILE *f = fopen(nombre_archivo, "a");
	if(t->raiz == NULL)
		fprintf(f,"<vacio>\n");
	else{
		listaP* l;
		l = palabras(&t->raiz, prefijo);
		lsnodo* lscan = l->prim;
		while(lscan != NULL){
			fprintf(f,"%s ", lscan->valor);
			lscan = lscan->sig;
		}
		lista_borrar(l);
	}
	fprintf(f,"\n");
	fclose(f);
}


listaP *palabras_con_prefijo(trie *t, char *pref){
	nodo* n = nodo_prefijo(t->raiz, pref);
	listaP* l = lista_crear();
	if(n == NULL) return l;
	if(n->fin) lista_agregar(l,pref);
	lista_concatenar(l,palabras(&n->hijos,pref));
	return l;
}

nodo *nodo_prefijo(nodo *n, char *p){
	int i = 0;

	while((n != NULL) && (p[i+1] != '\0')){
		n = nodo_buscar(n, p[i]);
		if (n != NULL) n = n->hijos;
		i++;
	}
	n = nodo_buscar(n, p[i]);
	return n;
}

trie *trie_construir(char *nombre_archivo){
	trie* t = trie_crear();
	char p[1024];
	FILE * f = fopen(nombre_archivo, "r");
	while(fscanf(f, "%s", p) != EOF){
		trie_agregar_palabra(t,p);
	}
	fclose(f);
	return t;
}



listaP *palabras(nodo** n, char *prefijo){

	int len = str_len(prefijo);
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

double trie_pesar(trie *t, double (*funcion_pesaje)(char*)){

 	char string[1024];

 	string[0] = '\0';
 	listaP* l = palabras(&(t->raiz),string);
 	lsnodo* lscan = l->prim;

 	double sum = 0
 	int count = 0;


 	while(lscan != NULL){
 		sum += (*funcion_pesaje)(lscan->valor);
 		count++;
 		lscan = lscan->sig;
 	}
 	lista_borrar(l);
 	return sum/count;
 }