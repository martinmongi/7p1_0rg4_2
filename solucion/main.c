#include <stdio.h>
#include "trie.h"

int main(void) {
	trie* t = trie_crear();
	trie_borrar(t);
    return 0;
}

