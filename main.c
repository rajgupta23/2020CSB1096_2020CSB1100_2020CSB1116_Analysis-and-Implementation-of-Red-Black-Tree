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
	inorder(t, t->root);

	return 0;
}