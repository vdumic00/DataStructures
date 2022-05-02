#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SIZE (11)
#define FILE_NAME_SIZE (1024)

struct _node;
typedef struct _node* NodePosition;
typedef struct _node {
	char data[DATA_SIZE];
	NodePosition left;
	NodePosition right;
} Node;

struct _list;
typedef struct _list* ListPosition;
typedef struct _list {
	NodePosition data;
	ListPosition next;
} List;

NodePosition readPostfixFromFile(char*);
NodePosition createNode(char*);
ListPosition createListNode(NodePosition);
int deleteTree(NodePosition);
int deleteList(ListPosition);
int isNumber(char*);
int push(ListPosition, NodePosition);
NodePosition pop(ListPosition);
int toInfix(ListPosition, NodePosition);
int pushBack(ListPosition, NodePosition);
int printInfixInFile(char*, ListPosition);

int main() {
	NodePosition root = NULL;
	List infixResult;
	char filename[FILE_NAME_SIZE] = { 0 };
	char outputFile[FILE_NAME_SIZE] = { 0 };

	infixResult.next = NULL;

	printf("Please insert postfix filename:\t");
	scanf(" %s", filename);

	printf("Please insert infix filename:\t");
	scanf(" %s", outputFile);

	root = readPostfixFromFile(filename);

	if (NULL == root) {
		return EXIT_FAILURE;
	}

	toInfix(&infixResult, root);

	printInfixInFile(outputFile, &infixResult);

	deleteList(&infixResult);
	deleteTree(root);

	return EXIT_SUCCESS;
}

NodePosition readPostfixFromFile(char* filename)
{
	FILE* fp = NULL;
	char readString[DATA_SIZE] = { 0 };
	List head;
	NodePosition result = NULL;

	head.next = NULL;

	fp = fopen(filename, "r");
	if (NULL == fp) {
		printf("File %s doesn't exist or you don't have permission to open it!\r\n", filename);
		return NULL;
	}

	while (!feof(fp)) {
		NodePosition node = NULL;

		fscanf(fp, " %s", readString);
		node = createNode(readString);

		if (NULL == node) {
			fclose(fp);
			return NULL;
		}

		if (isNumber(node->data)) {
			push(&head, node);

		}
		else {
			node->right = pop(&head);

			if (NULL == node->right) {
				printf("Postfix isn't right, please check it!\r\n");
				deleteList(&head);
				return NULL;
			}

			node->left = pop(&head);

			if (NULL == node->left) {
				printf("Postfix isn't right, please check it!\r\n");
				deleteList(&head);
				return NULL;
			}

			push(&head, node);
		}
	}

	result = pop(&head);

	if (NULL == result) {
		printf("File is empty!\r\n");
		return NULL;
	}

	if (pop(&head) != NULL) {
		printf("Postfix isn't right please check it!\r\n");
		return NULL;
	}

	fclose(fp);

	return result;
}

NodePosition createNode(char* data)
{
	NodePosition p = NULL;

	p = (NodePosition)malloc(sizeof(Node));

	if (NULL == p) {
		printf("Memory allocation failed!\r\n");
		return NULL;
	}

	strcpy(p->data, data);
	p->left = NULL;
	p->right = NULL;

	return p;
}

ListPosition createListNode(NodePosition data)
{
	ListPosition p = NULL;

	p = (ListPosition)malloc(sizeof(List));

	if (NULL == p) {
		printf("Memory allocation failed!\r\n");
		return NULL;
	}

	p->data = data;
	p->next = NULL;

	return p;
}

int deleteTree(NodePosition p)
{
	if (NULL == p) {
		return;
	}

	deleteTree(p->left);
	deleteTree(p->right);

	free(p);

	return 0;
}

int deleteList(ListPosition p)
{
	ListPosition current = p->next;
	ListPosition next = NULL;

	if (NULL == current) {
		printf("List is already empty!\r\n");
		return;
	}

	while (NULL != current) {
		next = current->next;
		free(current);
		current = next;
	}

	p = NULL;

	return 0;
}

int isNumber(char* str)
{
	int number = 0;

	if (sscanf(str, " %d", &number) == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int push(ListPosition head, NodePosition data)
{
	ListPosition node = NULL;

	node = createListNode(data);

	if (NULL == node)
		return -1;

	node->next = head->next;
	head->next = node;

	return 0;
}

NodePosition pop(ListPosition head)
{
	NodePosition result = NULL;
	ListPosition first = head->next;

	if (NULL == first) {
		return NULL;
	}

	head->next = first->next;
	result = first->data;
	free(first);

	return result;
}

int toInfix(ListPosition head, NodePosition current)
{
	if (NULL == current) {
		return;
	}

	toInfix(head, current->left);
	pushBack(head, current);
	toInfix(head, current->right);

	return 0;
}

int pushBack(ListPosition head, NodePosition data)
{
	ListPosition p = head;

	while (NULL != p->next)
		p = p->next;

	return push(p, data);
}

int printInfixInFile(char* filename, ListPosition head)
{
	FILE* fp = NULL;
	ListPosition p = head->next;

	fp = fopen(filename, "w");

	if (NULL == fp) {
		printf("File %s doesn't exist or you don't have permission to open it!\r\n", filename);
		return -1;
	}

	for (p; p != NULL; p = p->next)
		fprintf(fp, "%s ", p->data->data);

	fclose(fp);

	return 0;
}