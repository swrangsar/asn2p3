#ifndef _splayTree_h
#define _splayTree_h

#define EMPTYNODEKEY 0  /* the key which identifies a temporary empty node */

typedef struct splayNode {
	int key;
	void* data;
	struct splayNode* left;
	struct splayNode* right;
} splayNode;

typedef struct splayTree {
	splayNode* root;
	splayNode* min;
	splayNode* max;
} splayTree;

splayNode* createSplayNode();
splayTree* createSplayTree();
int getSplayNodeKey(splayNode* node);
void linkToLeftTree(splayTree* tree, splayTree* leftTree);
void linkToRightTree(splayTree* tree, splayTree* rightTree);
void rotateSplayTreeLeft(splayTree* tree);
void rotateSplayTreeRight(splayTree* tree);
void assembleSplayTree(splayTree* tree, splayTree* leftTree, splayTree* rightTree);
void splay(splayTree* tree, int key);
void insert(splayTree* tree, int key);
int getMaximumSplayNodeKey(splayNode* node);
void delete(splayTree* tree, int key);
void search(splayTree* tree, int key);
void printSplayTree(splayTree* tree);
void printSplayNode(splayNode* node);
void destroySplayNode(splayNode* node);
void destroySplayNodeRecursive(splayNode* node);
void destroySplayTree(splayTree* tree);

#endif