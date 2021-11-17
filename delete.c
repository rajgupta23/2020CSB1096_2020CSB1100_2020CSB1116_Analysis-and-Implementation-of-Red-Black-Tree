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

void left_rotate(Tree *t, node *x){}
void right_rotate(Tree *t, node *x) {}

void transplant(Tree *t, node *a, node *b)
{
    if(a->parent == t->NIL)
        t->root = b;
    else if(a == a->parent->left)
        a->parent->left = b;
    else
        a->parent->right = b;
    b->parent = a->parent;
}
node* treeMin(Tree* t, node *z) {  // to find minimum value in tree
	node * temp = z;
	if (temp == t->NIL)return NULL; // tree is empty
	while (temp->left != t->NIL)temp = temp->left;
	return temp;
}
void deleteFixup(Tree *t, node *x)
{
    node *w;
    while((x != t->root)&&(x->color == Black))
    {
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->color == Red){
                w->color = Black;
                x->parent->color = Red;
                left_rotate(t, x->parent);
                w = x->parent->right;
            }
            if((w->left->color == Black)&&(w->right->color == Black)){
                w->color = Red;
                x = x->parent;  
            }
            else if(w->right->color == Black){
                w->left->color = Black;
                w->color = Red;
                right_rotate(t, w);
                w = x->parent->right;
            }
            else{
                w->color = w->parent->color;
                w->parent->color = Black;
                w->right->color = Black;
                left_rotate(t, x->parent);
                x = t->root;
            }
 
        }
        
        else{// x == x->parent->right
            w = x->parent->left;
            if(w->color == Red){
                w->color = Black;
                x->parent->color = Red;
                right_rotate(t, x->parent);
                w = x->parent->left;
            }
            if((w->left->color == Black)&&(w->right->color == Black)){
                w->color = Red;
                x = x->parent;  
            }
            else if(w->left->color == Black){
                w->right->color = Black;
                w->color = Red;
                left_rotate(t, w);
                w = x->parent->left;
            }
            else{
                w->color = w->parent->color;
                w->parent->color = Black;
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
    node* z = t->root;
	while ((z->data != k)&&(z != t->NIL)) {
		if (z->data < k)z = z->left;
		else z = z->right;
	}
    node *x;
    node *y = z;
    bool yOriginalColor = y->color;

    if((z->left == t->NIL)&&(z->right != t->NIL)){
        x = z->right;
        transplant(t, z,z->right);
    }
    else if((z->right == t->NIL)&&(z->left != t->NIL)){
        x = z->left;
        transplant(t, z,z->left);
    }
    else if((z->right == t->NIL)&&(z->left == t->NIL)){
        if(z == z->parent->left)
            z->parent->left = t->NIL;
        if(z == z->parent->right)
            z->parent->right = t->NIL;
        x = z;
    }
    else{
        y = treeMin(t, z->right);
        yOriginalColor = y->color;
        x = y->right;
        if(y->parent == z)
            x->parent = y;
        else{
            transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    } 
    if(yOriginalColor == Black)
        deleteFixup(t, x);
}


int main()
{ 
    return 0;
}

/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Red 0
#define Black 1

struct node{
	int val;
	bool color;
	struct node *parent;
	struct node *left;
	struct node *right;
};
struct node *ROOT;
struct node *NILL;

void leftRotate(struct node *x)
{

}
void rightRotate(struct node *x)
{

}
struct node *treeMin(struct node *z)
{

}
void transplant(struct node *a, struct node *b)
{
    if(a->parent == NILL)
        ROOT = b;
    else if(a == a->parent->left)
        a->parent->left = b;
    else
        a->parent->right = b;
    a->parent = a->parent;
}
void deleteFixup(struct node *x)
{
    struct node *w;
    while((x != ROOT)&&(x->color == Black))
    {
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->color == Red){
                w->color = Black;
                x->parent->color = Red;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if((w->left->color == Black)&&(w->right->color == Black)){
                w->color = Red;
                x = x->parent;  
            }
            else if(w->right->color == Black){
                w->left->color = Black;
                w->color = Red;
                rightRotate(w);
                w = x->parent->right;
            }
            else{
                w->color = w->parent->color;
                w->parent->color = Black;
                w->right->color = Black;
                leftRotate(x->parent);
                x = ROOT;
            }
 
        }
        
        else{// x == x->parent->right
            w = x->parent->left;
            if(w->color == Red){
                w->color = Black;
                x->parent->color = Red;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if((w->left->color == Black)&&(w->right->color == Black)){
                w->color = Red;
                x = x->parent;  
            }
            else if(w->left->color == Black){
                w->right->color = Black;
                w->color = Red;
                leftRotate(w);
                w = x->parent->left;
            }
            else{
                w->color = w->parent->color;
                w->parent->color = Black;
                w->left->color = Black;
                rightRotate(x->parent);
                x = ROOT;
            }
            
        }
    }
	x->color = Black;   
}
void delete(struct node *z)
{
    struct node *x;
    struct node *y = z;
    bool yOriginalColor = y->color;

    if(z->left == NILL){
        x = z->right;
        transplant(z,z->right);
    }
    else if(z->right == NILL){
        x = z->left;
        transplant(z,z->left);
    }
    else{
        y = treeMin(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if(y->parent == z)
            x->parent = y;
        else{
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    } 
    if(yOriginalColor == Black)
        deleteFixup(x);
}


int main()
{
    
    return 0;
}*/
