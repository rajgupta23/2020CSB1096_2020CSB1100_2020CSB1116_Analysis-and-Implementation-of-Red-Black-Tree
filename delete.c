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

void left_rotate(Tree *t, node *x) {}
void right_rotate(Tree *t, node *x) {}

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
	// node *w;
	// node *temp = x;
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

		else { // x == x->parent->right
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
	node *x;
	node *y = z;
	// bool n = 0;
	bool yOriginalColor = y->color;

	if (z->left == t->NIL) {
		x = z->right;
		transplant(t, z, z->right);
	}
	else if (z->right == t->NIL) {
		x = z->left;
		transplant(t, z, z->left);
	}
	// else if ((z->right == t->NIL) && (z->left == t->NIL)) {  /// we dont need it
	// 	if (z == z->parent->left)
	// 		z->parent->left = t->NIL;
	// 	if (z == z->parent->right)
	// 		z->parent->right = t->NIL;
	// 	x = z;
	// 	k = 1;
	// }
	else {
		y = treeMin(t, z->right);
		bool y_orignal_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = z;
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
	if (yOriginalColor == Black)
		deleteFixup(t, x);
}
