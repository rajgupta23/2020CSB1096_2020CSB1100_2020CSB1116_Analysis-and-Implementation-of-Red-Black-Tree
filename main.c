#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "utils.h"

int main() {
	Tree *t = getRBTree(); // initially t-->nil tree

	for (int i = 0; i < 10; i++) {
		node * temp = getNode(i);
		insert(t, temp);
	}
	printf("%d\n", blackHieght(t));
	preorder(t, t->root);
	printf("\n");
	postorder(t, t->root);
	printf("\n");
	inorder(t, t->root);
	printf("\n");
	printf("max = %d \n", maximum(t));
	printf("max = %d \n", minimum(t));
	search(t, 5) ? printf("found\n") : printf("Not found\n");
	return 0;
}
