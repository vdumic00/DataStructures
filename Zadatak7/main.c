#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _node;
typedef struct _node* position;
typedef struct _node {
	int el;
	position next;
} node;

char* readFromFile(char*, char*);
int calculate(char*, position);
position createElement(int);
int pushStack(position, position);
int popStack(position);
int operation(int, int, char);
int printStack(position p);

int main()
{
	node stack;
	char* file = "dat.txt";
	char* buffer = NULL;
	int rez = 0;

	stack.next = NULL;
	buffer = (char *)malloc(100 * sizeof(char));

	buffer = readFromFile(file, buffer);
	if (buffer != NULL)
		printf("%s\n\n", buffer);

	rez = calculate(buffer, &stack);

	if(rez != 0)
		printf("\nResult is %d\n", rez);

	free(buffer);
	return 0;
}

char* readFromFile(char* FileName, char* buff)
{
	FILE* fp = NULL;

	fp = fopen(FileName, "r");
	if (fp == NULL) {
		printf("Opening file failed!\n");
		return NULL;
	}

	fgets(buff, 100, fp);

	fclose(fp);
	return buff;
}

int calculate(char* buff, position p)
{
	int br, n, a, b;
	int rez = 0, i = 0, length;
	char c[5];
	position q;

	length = strlen(buff);
	while (length >= 1) {
		i = sscanf(buff, "%d%n", &n, &br);
		if (i >= 1) {
			q = createElement(n);
			if(q != NULL)
				pushStack(p, q);
		}
		else {
			sscanf(buff, " %s%n", c, &br);
			a = popStack(p);
			b = popStack(p);
			rez = operation(a, b, c[0]);
			q = createElement(rez);
			if(q != NULL)
				pushStack(p, q);
		}
		buff += br;
		length = strlen(buff);
		printStack(p);
	}

	return rez;
}

position createElement(int x)
{
	position q = NULL;

	q = (position)malloc(sizeof(node));
	if (q == NULL) {
		printf("Memory allocation failed!\n");
		return NULL;
	}
	q->el = x;

	return q;
}

int pushStack(position p, position q)
{
	q->next = p->next;
	p->next = q;

	return 0;
}

int popStack(position p)
{
	position tmp = NULL;
	int x;

	tmp = p->next;
	x = tmp->el;
	p->next = tmp->next;
	free(tmp);

	return x;
}

int operation(int a, int b, char c)
{
	switch (c) {
	case '+':
		return b + a;
		break;
	case '-':
		return b - a;
		break;
	case '*':
		return b * a;
		break;
	case '/':
		return b / a;
		break;
	}
}

int printStack(position p)
{
	for (p = p->next; p != NULL; p = p->next) {
		printf("%d\t", p->el);
	}
	puts("");
}

