#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

struct _dir;
typedef struct _dir* position;
typedef struct _dir {
	char name[MAX_NAME];
	position next;
	position child;
} dir;

struct _stack;
typedef struct _stack* pos;
typedef struct _stack {
	position el;
	pos next;
} stack;

position createDir(char*);
int makeDir(char*, position);
int sortInsert(position, position, position);
int printDir(position);
void deleteDir(position);
int pushStack(pos, position);
position popStack(pos);
position findDir(char*, position, pos);

int main() {

	dir *current = NULL, *first = NULL;
	stack head;
	int i = 0;
	char x[MAX_NAME];

	head.next = NULL;

	first = createDir("C:");
	if (first == NULL)
		return -1;

	current = first;

	do {
		printf("What you want to do:\n");
		printf("1\tmd\n2\tcd dir\n3\tcd..\n4\tdir\n5\texit\n");
		scanf("%d", &i);

		switch (i) {
		case 1:
			printf("Name of directory:\t");
			scanf(" %s", x);
			if (makeDir(x, current) == -1)
				return -1;
			break;
		case 2:
			printf("Name of directory:\t");
			scanf(" %s", x);
			pushStack(&head, current);
			current = findDir(x, first, &head);
			break;
		case 3:
			current = popStack(&head);
			if (current == NULL)
				return -1;
			break;
		case 4:
			printDir(current);
			break;
		case 5:
			deleteDir(first);
			break;
		}

	} while (i != 5);

	return 0;
}

position createDir(char* dir_name)
{
	position p = NULL;

	p = (position)malloc(sizeof(dir));
	if (NULL == p) {
		printf("Memory allocation failed!\n");
		return NULL;
	}

	strcpy(p->name, dir_name);
	p->child = NULL;
	p->next = NULL;

	return p;
}

int makeDir(char* dir_name, position p)
{
	position q = NULL;

	q = createDir(dir_name);
	if (q == NULL) {
		printf("Creating directory failed!\n");
		return -1;
	}

	if (p->child == NULL) {
		p->child = q;
		return 0;
	}

	sortInsert(p, p->child, q);

	return 0;
}

int sortInsert(position prev, position next, position el)
{
	if (strcmp(prev->child->name, el->name) > 0) {
		prev->child = el;
		el->next = next;
		return 0;
	}

	prev = prev->child;
	next = prev->next;

	while (next != NULL && strcmp(next->name, el->name) < 0) {
		prev = next;
		next = next->next;
	}

	prev->next = el;
	el->next = next;

	return 0;
}

int printDir(position p)
{
	if (p->child == NULL) {
		printf("Directory is empty!\n\n");
		return 0;
	}

	p = p->child;
	while (p != NULL) {
		printf("%s\n", p->name);
		p = p->next;
	}

	puts("");

	return 0;
}

void deleteDir(position p)
{
	if (p == NULL)
		return;
	deleteDir(p->next);
	deleteDir(p->child);
	free(p);

	return;
}

int pushStack(pos p, position dir)
{
	pos q = NULL;

	q = (pos)malloc(sizeof(stack));
	if (q == NULL) {
		printf("Memory allocation failed!\n");
		return -1;
	}

	q->el = dir;
	q->next = p->next;
	p->next = q;

	return 0;
}

position popStack(pos p)
{
	pos tmp = NULL;
	position q = NULL;

	tmp = p->next;
	p->next = tmp->next;
	q = tmp->el;
	free(tmp);

	return q;
}

position findDir(char* dir_name, position p, pos stack)
{
	position q = NULL, start = p;

	if (p->next != NULL) {
		p = p->next;
		while (p != NULL) {
			if (strcmp(p->name, dir_name) == 0)
				return p;
			p = p->next;
		}
	}

	p = start;

	if (p->child != NULL) {
		p = p->child;
		while (p != NULL) {
			if (strcmp(p->name, dir_name) == 0)
				return p;
			p = p->next;
		}
	}
}

int printStack(pos p)
{
	for (p = p->next; p != NULL; p = p->next) {
		printf("%s\t", p->el->name);
	}
	puts("");
}