#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

char prefijo[1024];

int main(void) {
	char hola[5] = "hola";
	char martin[10] = " martin";
	char hola2[20];
	
	str_cpy(hola2,hola);
	printf("%s\n",hola);
	printf("%s\n",hola2);
	str_cat(hola2, martin);
	printf("%s\n",hola2);

    return 0;
}

