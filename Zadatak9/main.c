#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _node;
typedef struct _node* position;
typedef struct _node {
	int el;
	position left;
	position right;
} node;

int printTree(position);
position findElement(int, position);
position insertElement(int, position);
position deleteElement(int, position);
position findMin(position);

int main() {

	node* root = NULL;
	position tmp = NULL;

	root = insertElement(4, root);
	root = insertElement(2, root);
	root = insertElement(6, root);
	root = insertElement(1, root);
	root = insertElement(3, root);
	root = insertElement(5, root);
	root = insertElement(7, root);

	tmp = findElement(7, root);
	if (tmp != NULL) {
		printf("Element: %d\n", tmp->el);
	}

	tmp = findElement(9, root);
	if (tmp != NULL) {
		printf("Element %d\n", tmp->el);
	}

	printTree(root);

	root = deleteElement(2, root);
	root = deleteElement(6, root);

	root = insertElement(10, root);
	root = insertElement(-1, root);

	puts("");
	printTree(root);

	return 0;
}

int printTree(position p)
{
	if (p != NULL) {
		printTree(p->left);
		printf("%d\t", p->el);
		printTree(p->right);
	}

	return 0;
}

position findElement(int x, position p)
{
	if (p == NULL) {
		printf("\nElement %d doesn't exist!\n", x);
		return NULL;
	}

	else if (x < p->el)
		p = findElement(x, p->left);

	else if (x > p->el)
		p = findElement(x, p->right);

	return p;
}

position insertElement(int x, position p)
{
	if (p == NULL) {
		p = (position)malloc(sizeof(node));
		
		if (p == NULL) {
			printf("Memory allocation failed!\n");
			return NULL;
		}
		p->el = x;
		p->left = NULL;
		p->right = NULL;
	}

	else if (x < p->el)
		p->left = insertElement(x, p->left);

	else if (x > p->el)
		p->right = insertElement(x, p->right);

	return p;
}

position deleteElement(int x, position p)
{
	position tmp = NULL;

	if (p == NULL)
		return NULL;

	else if (x < p->el)
		p->left = deleteElement(x, p->left);

	else if (x > p->el)
		p->right = deleteElement(x, p->right);

	else if ((p->left != NULL) && (p->right != NULL)) {
		tmp = findMin(p->right);
		p->el = tmp->el;
		p->right = deleteElement(p->el, p->right);
	}

	else {
		tmp = p;
		if (p->left == NULL)
			p = p->right;
		else
			p = p->left;
		free(tmp);
	}

	return p;
}

position findMin(position p)
{
	if (p == NULL)
		return NULL;

	if (p->left == NULL)
		return p;

	return findMin(p->left);
}