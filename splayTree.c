#include <stdio.h>
#include <stdlib.h>
#include "splayTree.h"

splayNode* createSplayNode()
{
	splayNode* node = malloc(sizeof(splayNode));
	node->key = 0;
	node->data = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

splayTree* createSplayTree()
{
	splayTree* tree = malloc(sizeof(splayTree));
	tree->root = NULL;
	tree->min = NULL;
	tree->max = NULL;
	return tree;
}

int getSplayNodeKey(splayNode* node)
{
	if (node) {
		return node->key;
	} else {
		printf("The node that you are trying to get a key from doesn't exist.");
		exit(1);	
	}
}

void linkToLeftTree(splayTree* tree, splayTree* leftTree)
{
	/* put into maximum node in the tree */
	if (!leftTree->max) {
		leftTree->root = tree->root;
		tree->root = tree->root->right;
		leftTree->max = leftTree->root;
		leftTree->max->right = NULL;
	} else {
		leftTree->max->right = tree->root;
		tree->root = tree->root->right;
		leftTree->max = leftTree->max->right;
		leftTree->max->right = NULL;
	}
	return;
}

void linkToRightTree(splayTree* tree, splayTree* rightTree)
{
	/* put into minimum node in the tree */
	if (!rightTree->min) {
		rightTree->root = tree->root;
		tree->root = tree->root->left;
		rightTree->min = rightTree->root;
		rightTree->min->left = NULL;
	} else {
		rightTree->min->left = tree->root;
		tree->root = tree->root->left;
		rightTree->min = rightTree->min->left;
		rightTree->min->left = NULL;
	}
	return;
}

void rotateSplayTreeLeft(splayTree* tree)
{
	if (!tree || !tree->root || !tree->root->right) {
		printf("Cannot rotate a Null tree or a tree without proper configuration!\n");
		exit(1);
	} else {
		splayNode* top = tree->root;
		tree->root = tree->root->right;
		top->right = tree->root->left;
		tree->root->left = top;
		return;
	}
}

void rotateSplayTreeRight(splayTree* tree)
{
	if (!tree || !tree->root || !tree->root->left) {
		printf("Cannot rotate a Null tree or a tree without proper configuration!\n");
		exit(1);
	} else {
		splayNode* top = tree->root;
		tree->root = tree->root->left;
		top->left = tree->root->right;
		tree->root->right = top;
		return;
	}
}

void assembleSplayTree(splayTree* tree, splayTree* leftTree, splayTree* rightTree)
{
	if (rightTree->min) {
		rightTree->min->left = tree->root->right;
	} else {
		rightTree->min = tree->root->right;
		rightTree->root = tree->root->right;
	}
	if (leftTree->max) {
		leftTree->max->right = tree->root->left;	
	} else {
		leftTree->max = tree->root->left;
		leftTree->root = tree->root->left;
	}		
	tree->root->left = leftTree->root;
	tree->root->right = rightTree->root;
	if (leftTree) {
		free(leftTree);
		leftTree = NULL;
	}
	if (rightTree) {
		free(rightTree);
		rightTree = NULL;
	}		
}

void splay(splayTree* tree, int key)
{
	/* using top down method */
	if (!tree) {
		printf("The tree to be splayed does not exist!\n");
		exit(1);
	}
	if (!tree->root) {
		return;
	}
	splayTree* leftTree = createSplayTree();
	splayTree* rightTree = createSplayTree();
	while (1) {
		if (key < getSplayNodeKey(tree->root)) {
			if (!tree->root->left) break;
			if (key < getSplayNodeKey(tree->root->left)) {
				/* rotate right and then link right */
				rotateSplayTreeRight(tree);
				if (!tree->root->left) break;
			}
			linkToRightTree(tree, rightTree);			
		} else if (key > getSplayNodeKey(tree->root)){
			if (!tree->root->right) break;
			if (key > getSplayNodeKey(tree->root->right)) {
				/* rotate left and then link left */
				rotateSplayTreeLeft(tree);
				if (!tree->root->right) break;
			}		
			linkToLeftTree(tree, leftTree);
		} else {
			break;
		}
	}
	assembleSplayTree(tree, leftTree, rightTree);
	return;
}

void insert(splayTree* tree, int key)
{
	if (!tree->root) {
		splayNode* node = createSplayNode();
		node->key = key;
		tree->root = node;
		printf("The key %3d was successfully inserted into the tree.\n", key);
		return;
	}
	splay(tree, key);
	if (key == getSplayNodeKey(tree->root)) {
		printf("The key %3d already exist in the tree.\n", key);
	} else if (key < getSplayNodeKey(tree->root)) {
		splayNode* node = createSplayNode();
		node->key = key;
		node->left = tree->root->left;
		tree->root->left = node;
		printf("The key %3d was successfully inserted into the tree.\n", key);
		return;		
	} else {
		splayNode* node = createSplayNode();
		node->key = key;
		node->right = tree->root->right;
		tree->root->right = node;
		printf("The key %3d was successfully inserted into the tree.\n", key);
		return;
	}
		
}

int getMaximumSplayNodeKey(splayNode* node)
{
	if (!node) {
		/*
		 * printf("Can't get maximum key because node is null.\n");
		 */
		return EMPTYNODEKEY;
	}
	if (node->right) {
		return getMaximumSplayNodeKey(node->right);
	} else {
		return node->key;
	}
}

void delete(splayTree* tree, int key)
{
	splay(tree, key);
	if (tree->root && tree->root->key == key) {
		splayTree* leftTree = createSplayTree();
		splayTree* rightTree = createSplayTree();
		leftTree->root = tree->root->left;
		rightTree->root = tree->root->right;
		if (getMaximumSplayNodeKey(leftTree->root) != EMPTYNODEKEY) {
			splay(leftTree, getMaximumSplayNodeKey(leftTree->root));	
		}			
		if (leftTree->root) {
			destroySplayNode(tree->root);
			leftTree->root->right = rightTree->root;
			tree->root = leftTree->root;
		} else {
			destroySplayNode(tree->root);
			tree->root = rightTree->root;	
		}
		printf("The key %d was successfully deleted.", key);
		if (leftTree) {
			free(leftTree);
			leftTree = NULL;
		}
		if (rightTree) {
			free(rightTree);
			rightTree = NULL;
		}		
		return;
	} else {
		printf("Could not find the key %d to delete.\n", key);
	}
}

void search(splayTree* tree, int key)
{
	splay(tree, key);
	if (getSplayNodeKey(tree->root) == key) {
		printf("The key %3d was found.\n", key);
		return;				
	} else {
		printf("The key %3d was not found.\n", key);		
		return;
	}
}

void printSplayTree(splayTree* tree)
{
	if (tree && tree->root) {
		printf("\n*************************");
		printf("\n* Printing keys inorder *");
		printf("\n*************************\n");
		printSplayNode(tree->root);
		printf("\n******************************");
		printf("\n* The tree printing is done! *");		
		printf("\n******************************\n\n");
	} else {
		printf("The tree to be printed does not exist.\n");
	}
}

void printSplayNode(splayNode* node)
{
	if (node) {
		if (node->left) printSplayNode(node->left);
		if (node->right) printSplayNode(node->right);
		printf("Key: %d\n", node->key);
	}
}

void destroySplayNode(splayNode* node)
{
	if (node) {
		if (node->data) free(node->data);
		free(node);
		node = NULL;
	}
}

void destroySplayNodeRecursive(splayNode* node)
{
	if (node) {
		if (node->left) destroySplayNodeRecursive(node->left);
		if (node->right) destroySplayNodeRecursive(node->right);
		destroySplayNode(node);
	}
}

void destroySplayTree(splayTree* tree)
{
	if (tree) {
		destroySplayNodeRecursive(tree->root);
	}	
}