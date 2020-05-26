#ifndef TREE_H
#define TREE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	char cognome[20];
	char nome[20];
	char materia[20];
	int livello;
}docente;

typedef  docente  elementTree;

typedef struct  treeelementTree {
	elementTree value;
	struct treeelementTree  *left, *right;
} node;

typedef  node *tree;

//PER ELEMENTTREE:
void showelementTree(elementTree a);    //INSERIRE A SECONDA DI ELEMENTTREE
bool isLess(elementTree a, elementTree b);//INSERIRE A SECONDA DI ELEMENTTREE
bool isEqual(elementTree a, elementTree b);//INSERIRE A SECONDA DI ELEMENTTREE

//PRIMITIVE
bool empty(tree);
tree emptyTree(void);
elementTree root(tree);
tree left(tree);
tree right(tree);
tree consTree(elementTree, tree, tree);
tree insert(elementTree, tree);

//ESPLORAZIONE
void preOrder(tree);
void inOrder(tree);
void postOrder(tree);



typedef struct  treeelementTree2 {
	int value;
	struct treeelementTree2  *left, *right;
} node2;

typedef node2 *tree2;

bool empty2(tree2);
tree2 emptyTree2(void);
int root2(tree2);
tree2 left2(tree2);
tree2 right2(tree2);
tree2 consTree2(int, tree2, tree2);

tree2 insert2(int, tree2);
void showelementTree2(int a);   //INSERIRE A SECONDA DI ELEMENTTREE
bool isLess2(int a, int b);//INSERIRE A SECONDA DI ELEMENTTREE
bool isEqual2(int a, int b);//INSERIRE A SECONDA DI ELEMENTTREE
void inOrder2(tree2);

#endif