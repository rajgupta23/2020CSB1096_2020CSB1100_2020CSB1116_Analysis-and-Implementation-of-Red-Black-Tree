#include <stdio.h>             // For taking input from user and printing output 
#include <stdlib.h>            // For allocating memory dynamically

struct node{                   // Structure for node of red black tree
	int key;               // Data of node
	int color;             // Colour of node
	struct node *parent;   // Parent pointer of node
	struct node *left;     // Pointer to left child
	struct node *right;    // Pointer to right child
};

struct node *root;           // Global pointer for root
struct node *nill;           // Global pointer for nill node

void tree_print_inorder_helper(struct node *x){         // Helper function for Inorder traversal of tree
	if(x != nill){
		tree_print_inorder_helper(x->left);
		printf("%d\t", x->key);
		tree_print_inorder_helper(x->right);
	}
}
void tree_print_inorder()                  // Main function call for Inorder traversal of tree
{
    tree_print_inorder_helper(root);
    printf("\n");
}

void tree_print_preorder_helper(struct node *x){          // Helper function for Preorder traversal of tree
	if(x != nill){
	    printf("%d\t", x->key);
		tree_print_preorder_helper(x->left);
		tree_print_preorder_helper(x->right);
	}
}
void tree_print_preorder()              // Main function call for Preorder traversal of tree
{
    tree_print_preorder_helper(root);
    printf("\n");
}

void tree_print_postorder_helper(struct node *x){        // Helper function for Postorder traversal of tree
	if(x != nill){
	    tree_print_postorder_helper(x->left);
		tree_print_postorder_helper(x->right);
		printf("%d\t", x->key);
	}
}
void tree_print_postorder()                   // Main function call for Postorder traversal of tree
{
    tree_print_postorder_helper(root);
    printf("\n");
}

struct node *search(int val){                     //Searching a key in tree
	struct node *x = root;                    // Assigning root to x
	while(x != nill && x->key != val){        // Traversing until we find nill or finding the node which has val as its key
		if(val < x->key){
			x = x->left;              //Going to left child
		}
		else{
			x = x->right;           //Going to right child
		}
	}

	return x;              //Returning the pointer whose key is val
}

struct node *minimum_helper(struct node *x){             //Helper function for finding minimum
    if(x==nill)                
    {
        return x;                 // Edge case:When tree is empty
    }
	while(x->left != nill){       // Traversing only through left children until we find nill pointer
		x = x->left;
	}
	return x;                    // Returning the last left child
}

struct node *minimum()              //Main function for finding minimum
{
    return minimum_helper(root);
}

struct node *maximum_helper(struct node *x){            //Helper function for finding maximum
    if(x==nill)
    {
        return x;                // Edge case:When tree is empty                
    }
	while(x->right != nill){
		x = x->right;           // Traversing only through right children until we find nill pointer
	}
	return x;                        // Returning the last right child
}

struct node *maximum()              //Main function for finding maximum
{
    return maximum_helper(root);
}

void print_path(int val)           //Print_path function
{
    struct node *x = search(val);      //Extracting node address which has its key as val
    if(x==nill)
    {
        return;              //Edge case: When not found or empty tree
    }
    if(x==root)
    {
        printf("%d\t",x->key);           //Base case 
        return;
    }
    print_path(x->parent);          //Recursive call
    printf("%d\t",x->key);             //Small work
    
}
int main() {
	// code
	return 0;
}
