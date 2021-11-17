#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

#define Red 0
#define Black 1

typedef struct node { // treeNode structure
	int data; // data stored at node
	bool color; // using bool we can save 31 bits of int.
	struct node *right; // pointer to right child
	struct node *left; // pointer to left child
	struct node *parent; // pointer to parent 
} node;

typedef struct Tree {
	node *root;
	node *NIL;
} Tree;

node* getNode(int data) {
	node* n = (node*)malloc(sizeof(node));
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;
	n->data = data;
	n->color = Red;
	return n;
}

Tree* getRBTree() {
	Tree *t = (Tree*)malloc(sizeof(Tree));
	node *T_nil = (node*) malloc(sizeof(node));
	T_nil->color = Black;
	T_nil->data = 0;
	T_nil->left = NULL;
	T_nil->right = NULL;
	T_nil->parent = NULL;
	t->NIL = T_nil;
	t->root = t->NIL; // initially root is also a nill Node

	return t;
}

void left_rotate(Tree *t, node *x) {  // LEFT-ROTATE(T,x)
	node *y = x->right;
	x->right = y->left;
	if (y->left != t->NIL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == t->NIL) { //x --> root
		t->root = y;
	}
	else if (x == x->parent->left) { //x --> left child
		x->parent->left = y;
	}
	else { //x --> right child
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void right_rotate(Tree *t, node *x) { // CLRS RIGHT-ROTATE(T,x)
	node *y = x->left;
	x->left = y->right;
	if (y->right != t->NIL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == t->NIL) { //x --> root
		t->root = y;
	}
	else if (x == x->parent->right) { //x --> left child
		x->parent->right = y;
	}
	else { //x --> right child
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

void fixup(Tree *t, node *z) { // CLRS RB-INSERT-FIXUP(T,z)
	while (z->parent->color == Red) {
		if (z->parent == z->parent->parent->left) { //z.parent --> left child

			node *y = z->parent->parent->right; //uncle of z

			if (y->color == Red) { //when uncle of z is red
				z->parent->color = Black;
				y->color = Black;
				z->parent->parent->color = Red;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					left_rotate(t, z);
				}
				z->parent->color = Black; //made parent black
				z->parent->parent->color = Red; //made parent of parent red
				right_rotate(t, z->parent->parent);
			}
		}
		else { //z.parent --> right child
			node *y = z->parent->parent->left; //uncle of z

			if (y->color == Red) {
				z->parent->color = Black;
				y->color = Black;
				z->parent->parent->color = Red;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					right_rotate(t, z);
				}
				z->parent->color = Black; //made parent black
				z->parent->parent->color = Red; //made parent red
				left_rotate(t, z->parent->parent);
			}
		}
	}
	t->root->color = Black;
}

void insert(Tree *t, node *z) { // CLRS RB-INSERT(T,z)
	node* y = t->NIL;
	node* x = t->root;

	while (x != t->NIL) {
		y = x;
		if (z->data < x->data)
			x = x->left;
		else x = x->right;
	}
	z->parent = y;

	if (y == t->NIL) { //if tree is still empty
		t->root = z;
	}
	else if (z->data < y->data) //data of child is less than its parent, left child
		y->left = z;
	else
		y->right = z;

	z->right = t->NIL;
	z->left = t->NIL;

	fixup(t, z);
}

void inorder(Tree *t, node *root) {
	if (root != t->NIL) { // tree has atleast one node
		inorder(t, root->left);
		printf("%d\n", root->data);
		inorder(t, root->right);
	}
}
