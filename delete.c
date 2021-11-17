#include <stdio.h>
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
}
