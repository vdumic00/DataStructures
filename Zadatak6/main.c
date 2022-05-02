#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _node* position;
typedef struct _node {
	int el;
	position next;
} node;

int pushStack(position p);
int print(position p);
int popStack(position p);
position pushQueue(position p);
int popQueue(position p);

int main() {

	srand((unsigned)time(NULL));

	node stack, queue;
	position tmp = NULL;

	stack.next = NULL;
	queue.next = NULL;

	puts("Adding elements, stack:");
	if (pushStack(&stack) != 0)
		return -1;
	if (print(&stack) != 0)
		puts("Stack is empty!");

	if (pushStack(&stack) != 0)
		return -1;
	if (print(&stack) != 0)
		puts("Stack is empty!");

	if (pushStack(&stack) != 0)
		return -1;
	if (print(&stack) != 0)
		puts("Stack is empty!");

	if (pushStack(&stack) != 0)
		return -1;
	if (print(&stack) != 0)
		puts("Stack is empty!");
	
	puts("Getting elements from stack:");

	printf("Element is %d\n", popStack(&stack));
	if (print(&stack) != 0)
		puts("Stack is empty!");

	printf("Element is %d\n", popStack(&stack));
	if (print(&stack) != 0)
		puts("Stack is empty!");

	printf("Element is %d\n", popStack(&stack));
	if(print(&stack)!= 0)
		puts("Stack is empty!");

	printf("Element is %d\n", popStack(&stack));
	if (print(&stack) != 0)
		puts("Stack is empty!");

	puts("\nAdding elements, queue:");

	tmp = pushQueue(&queue);
	if (tmp == NULL)
		return -1;
	if (print(&queue) != 0)
		puts("Queue is empty!");

	tmp = pushQueue(tmp);
	if (tmp == NULL)
		return -1;
	if (print(&queue) != 0)
		puts("Queue is empty!");

	tmp = pushQueue(tmp);
	if (tmp == NULL)
		return -1;
	if (print(&queue) != 0)
		puts("Queue is empty!");

	puts("Getting elements from queue:");
	printf("Element is %d\n", popQueue(&queue));
	if (print(&queue) != 0)
		puts("Queue is empty!");

	printf("Element is %d\n", popQueue(&queue));
	if (print(&queue) != 0)
		puts("Queue is empty!");

	printf("Element is %d\n", popQueue(&queue));
	if (print(&queue) != 0)
		puts("Queue is empty!");

	return 0;
}

int pushStack(position p)
{
	position q = NULL;

	q = (position)malloc(sizeof(node));
	if (NULL == q) {
		printf("Memory allocation failed!\n");
		return -1;
	}

	q->next = p->next;
	p->next = q;

	q->el = rand() % (100 - 10 + 1) + 10;

	return 0;
}

int print(position p)
{
	if (p->next == NULL) 
		return -1;

	for (p = p->next; p != NULL; p = p->next)
		printf("%d\t", p->el);
	puts("");

	return 0;
}

int popStack(position p)
{
	position tmp = NULL;
	int x;

	if (p->next == NULL) {
		printf("Stack is empty!\n");
		return -1;
	}

	tmp = p->next;
	x = tmp->el;

	p->next = tmp->next;
	free(tmp);

	return x;
}

position pushQueue(position p)
{
	position q = NULL;

	q = (position)malloc(sizeof(node));
	if (NULL == q) {
		printf("Memory allocation failed!\n");
		return NULL;
	}

	q->next = p->next;
	p->next = q;

	q->el = rand() % 91 + 10;

	return q;
}

int popQueue(position p)
{
	position tmp = NULL;
	int x;

	if (p->next == NULL) {
		printf("Queue is empty!\n");
		return -1;
	}

	tmp = p->next;
	x = tmp->el;

	p->next = tmp->next;
	free(tmp);

	return x;
}