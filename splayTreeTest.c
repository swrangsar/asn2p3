#include <stdio.h>
#include <stdlib.h>
#include "splayTree.h"

int main(int argc, const char* argv[])
{
	splayTree* tree = createSplayTree();
	int i = 1;
	for (; i <= 15; i++) {
		insert(tree, i);
	}
	printSplayTree(tree);	
	printf("Initialized the splay tree with keys 1-15.\n");
	
	for (i = 15; i > 0; i--) {
		search(tree, i);
		printSplayTree(tree);
	}
	printf("Searched the splay tree with keys 15-1.\n\n");
	delete(tree, 15);
	printSplayTree(tree);	
	delete(tree, 14);
	printSplayTree(tree);
	delete(tree, 4);
	printSplayTree(tree);
	delete(tree, 5);
	printSplayTree(tree);
	delete(tree, 1);
	printSplayTree(tree);
	destroySplayTree(tree);
	return 0;	
}