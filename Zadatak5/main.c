#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _node;
typedef struct _node* Position;
typedef struct _node {
	int n;
	Position next;
} Node;

int readFromFile(Position, char*);
Position createElement(int);
int sortInsert(Position, Position, Position);
int printList(Position);
int copyList(Position, Position);
int insertAfter(Position, Position);
int findElement(Position, int);
int unija(Position, Position, Position);
int presjek(Position, Position, Position);

int main() {
	Node head1, head2, list1, list2;
	head1.next = NULL;
	head2.next = NULL;
	list1.next = NULL;
	list2.next = NULL;

	if (readFromFile(&list1, "List1.txt") != 0) {
		printf("Reading from file failed!\n");
		return -1;
	}

	if (readFromFile(&list2, "List2.txt") != 0) {
		printf("Reading from file failed!\n");
		return -1;
	}

	puts("First list:");
	printList(&list1);
	puts("");

	puts("Second list:");
	printList(&list2);
	puts("");

	if((unija(&list1, &list2, &head1) != 0))
		return -1;
	puts("Union:");
	printList(&head1);

	puts("");
	puts("Intersection:");
	if((presjek(&list1, &list2, &head2)) != 0)
		return -1;
	printList(&head2);

	return 0;
}

int readFromFile(Position head, char *fileName)
{
	FILE *fp = NULL;
	int x, n;
	Position el = NULL;

	fp = fopen(fileName, "r");
	if (NULL == fp) {
		printf("Opening file failed!\n");
		return -1;
	}

	x = fgetc(fp);
	rewind(fp);

	while (!feof(fp)) {
		if (x == EOF) {
			printf("File is empty\n");
			break;
		}

		fscanf(fp, "%d", &n);
		if ((el = createElement(n)) == NULL) {
			return -1;
		}
		sortInsert(head, head->next, el);
	}

	fclose(fp);

	return 0;
}

Position createElement(int n)
{
	Position p = NULL;
	p = (Position)malloc(sizeof(Node));

	if (NULL == p) {
		printf("Memory allocation failed!\n");
		return NULL;
	}

	p->n = n;
	p->next = NULL;

	return p;
}

int sortInsert(Position prev, Position next, Position el)
{
	while ((next != NULL) && (next->n < el->n)) {
		prev = next;
		next = next->next;
	}

	prev->next = el;
	el->next = next;

	return 0;
}

int printList(Position head)
{
	Position p = NULL;

	if (head->next != NULL) {
		for (p = head->next; p != NULL; p = p->next)
			printf("%d\t", p->n);
	}
	else
		puts("");

	return 0;
}

int copyList(Position p, Position head)
{
	Position el = NULL;

	while (p != NULL) {
		if ((el = createElement(p->n)) == NULL)
			return -1;
		if (insertAfter(head, el) != 0)
			return -1;
		head = head->next;
		p = p->next;
	}

	return 0;
}

int insertAfter(Position where, Position what)
{
	what->next = where->next;
	where->next = what;

	return 0;
}

int findElement(Position p, int x)
{
	for (p = p->next; p != NULL; p = p->next) {
		if (p->n == x) {
			return 1;
		}
	}

	return 0;
}

int unija(Position p, Position q, Position r)
{
	Position el = NULL;
	Position tmp = r;
	p = p->next;
	q = q->next;
	Position tempp = p, tempq = q;

	if (NULL == p && NULL == q) {
		printf("Lists are empty\n");
		return 0;
	}

	if (NULL == p) {
		if (copyList(q, r) != 0)
			return -1;
		return 0;
	}

	if (NULL == q) {
		if (copyList(p, r) != 0)
			return -1;
		return 0;
	}

	while (p != NULL) {
			if ((el = createElement(p->n)) == NULL)	
				return -1;
			if (insertAfter(r, el) != 0)
				return -1;
			r = r->next;
			p = p->next;
	}

	r = tmp;

	while (q != NULL) {
			if (!(findElement(r, q->n))){
				el = createElement(q->n);
				sortInsert(r, r->next, el);
		}
		q = q->next;
	}

	return 0;
}

int presjek(Position p, Position q, Position r)
{
	Position el = NULL;
	p = p->next;
	q = q->next;
	Position temp = q, tempr = r;

	if (NULL == p || NULL == q) {
		printf("Intersection is empty\n");
		return 0;
	}

	while (p != NULL) {
		while (q != NULL) {
			if (p->n == q->n) {
				if ((el = createElement(p->n)) == NULL)
					return -1;
				if (insertAfter(r, el) != 0)
					return -1;
				r = r->next;
			}
			q = q->next;
		}
		p = p->next;
		q = temp;
	}

	r = tempr;
	if (r->next == NULL)
		printf("Lists don't have same elements\n");

	return 0;
}