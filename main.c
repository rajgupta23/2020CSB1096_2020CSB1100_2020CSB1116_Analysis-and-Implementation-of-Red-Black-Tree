#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "utils.h"

int main() {
	Tree *t = getRBTree(); // initially t-->nil tree
	int choice, i, d, key;
	while (1) {
		printf("Enter:\n1.Insertion\n2.Deletion\n3.search\n4.Black Height\n5.Inorder\n6.Postorder\n7.preorder\n8.Quit\n");
		scanf("%d", &choice);
		if (choice == 1) {
			printf("Enter value you want to insert : ");
			scanf("%d", &i);
			node* temp = getNode(i);
			insert(t, temp);
		}
		else if (choice == 2) {
			printf("Enter value you want to delete : ");
			scanf("%d", &d);
			delete(t, d);
		}
		else if (choice == 3) {
			printf("Enter value you want to search : ");
			scanf("%d", &key);
			if (search(t, key))printf("Element is present\n");
			else printf("Element is not present\n");
		}
		else if (choice == 4) {
			printf("Black Height of current Red Black tree is %d\n", blackHieght(t));
		}
		else if (choice == 5) {
			printf("Inorder traversal of tree is : ");
			inorder(t, t->root);
			printf("\n");
		}
		else if (choice == 6) {
			printf("Postorder traversal of tree is : ");
			postorder(t, t->root);
			printf("\n");
		}
		else if (choice == 7) {
			printf("Preorder traversal of tree is : ");
			preorder(t, t->root);
			printf("\n");
		}
		else if (choice == 8)break;
	}
	return 0;
}
