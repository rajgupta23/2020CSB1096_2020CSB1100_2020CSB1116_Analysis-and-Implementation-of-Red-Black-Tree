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
	struct node *parent; // pointer to parent child
} node;

typedef struct Tree {
	node *root;
	node *NIL;
} Tree;
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
void transplant(Tree *t, node *a, node *b)
{
	if (a->parent == t->NIL)
		t->root = b;
	else if (a == a->parent->left)
		a->parent->left = b;
	else
		a->parent->right = b;
	b->parent = a->parent;
}
node* treeMin(Tree* t, node *z) {  // to find minimum value in tree
	node * temp = z;
	while (temp->left != t->NIL)temp = temp->left;
	return temp;
}
void deleteFixup(Tree *t, node *x)
{
	while ((x != t->root) && (x->color == Black))
	{
		if (x == x->parent->left) {
			node * w = x->parent->right;
			if (w->color == Red) {
				w->color = Black;
				x->parent->color = Red;
				left_rotate(t, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == Black && w->right->color == Black) {
				w->color = Red;
				x = x->parent;
			}
			else {
				if (w->right->color == Black) {
					w->left->color = Black;
					w->color = Red;
					right_rotate(t, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = Black;
				w->right->color = Black;
				left_rotate(t, x->parent);
				x = t->root;
			}
		}

		else {
			node * w = x->parent->left;
			if (w->color == Red) {
				w->color = Black;
				x->parent->color = Red;
				right_rotate(t, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == Black && w->left->color == Black) {
				w->color = Red;
				x = x->parent;
			}
			else {
				if (w->left->color == Black) {
					w->right->color = Black;
					w->color = Red;
					left_rotate(t, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = Black;
				w->left->color = Black;
				right_rotate(t, x->parent);
				x = t->root;
			}
		}
	}
	x->color = Black;
}
void delete(Tree *t, int k)
{
	node* z = malloc(sizeof(node));
	z = t->root;
	while ((z->data != k) && (z != t->NIL)) {
		if (z->data < k)z = z->right;
		else z = z->left;
	}
	if (z == t->NIL) {
		printf("Element is not present\n");
		return;
	}
	node *x;
	node *y = z;
	bool y_orignal_color = y->color;

	if (z->left == t->NIL) {
		x = z->right;
		transplant(t, z, z->right);
	}
	else if (z->right == t->NIL) {
		x = z->left;
		transplant(t, z, z->left);
	}
	else {
		y = treeMin(t, z->right);
		y_orignal_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		}
		else {
			transplant(t, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(t, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_orignal_color == Black)
		deleteFixup(t, x);
}
