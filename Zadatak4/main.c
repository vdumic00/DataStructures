#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _node;
typedef struct _node *Position;
typedef struct _node {
	int coeff;
	int exp;
	Position next;
} Node;

Position createElement(int, int);
int readFromFile(Position, char*);
int sortInsert(Position, Position, Position);
int printList(Position);
int insertAfter(Position, Position);
int copyList(Position, Position);
int addition(Position, Position, Position);
int multiplication(Position, Position, Position);
int deleteList(Position);

int main() {

	Node adit, multi, head1, head2;
	adit.next = NULL;
	multi.next = NULL;
	head1.next = NULL;
	head2.next = NULL;

	if (readFromFile(&head1, "List1.txt") != 0) {
		printf("Reading from file failed!\n");
		return -1;
	}

	if (readFromFile(&head2, "List2.txt") != 0) {
		printf("Reading from file failed!\n");
		return -1;
	}

	puts("First list:");
	printList(&head1);
	puts("");

	puts("Second list:");
	printList(&head2);
	puts("");

	puts("List after addition:");
	addition(&head1, &head2, &adit);
	printList(&adit);
	puts("");

	puts("List after multiplication:");
	multiplication(&head1, &head2, &multi);
	printList(&multi);


	return 0;
}

Position createElement(int coeff, int exp)
{
	Position p = NULL;

	p = (Position)malloc(sizeof(Node));

	if (NULL == p) {
		printf("Memory allocation failed!\n");
		return NULL;
	}

	p->coeff = coeff;
	p->exp = exp;
	p->next = NULL;

	return p;
}

int readFromFile(Position head, char *fileName)
{
	int coeff, exp;
	int x;
	Position el = NULL;
	FILE *fp = NULL;

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
		fscanf(fp, "%d %d", &coeff, &exp);
		if (coeff != 0) {
			if ((el = createElement(coeff, exp)) == NULL)
				return -1;
			sortInsert(head, head->next, el);
		}
	}

	fclose(fp);

	return 0;
}

int sortInsert(Position prev, Position next, Position el)
{
	while ((next != NULL) && (next->exp < el->exp)) {
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
		for (p = head->next; p != NULL; p = p->next) {
			printf("%dx^%d", p->coeff, p->exp);
			if (p->next != NULL) {
				printf(" + ");
			}
		}
	}
	else {
		printf("\n");
	}

	puts("");
	return 0;
}

int insertAfter(Position where, Position what)
{
	what->next = where->next;
	where->next = what;

	return 0;
}

int copyList(Position p, Position head)
{
	Position el = NULL;

	while (p != NULL) {
		if ((el = createElement(p->coeff, p->exp)) == NULL)
			return -1;
		if (insertAfter(head, el) != 0)
			return -1;
		head = head->next;
		p = p->next;
	}

	return 0;
}

int addition(Position p, Position q, Position r)
{
	Position el = NULL;

	if (NULL == p->next && NULL == q->next) {
		printf("Lists are empty\n");
		return 0;
	}

	if (NULL == p->next) {
		if (copyList(q->next, r) != 0)
			return -1;
		return 0;
	}

	if (NULL == q->next) {
		if (copyList(p->next, r) != 0)
			return -1;
		return 0;
	}

	p = p->next;
	q = q->next;

	while ((p != NULL) && (q != NULL)) {
		if (p->exp < q->exp) {
			el = createElement(p->coeff, p->exp);
			sortInsert(r, r->next, el);
			p = p->next;
			r = r->next;
		}
		else if (q->exp < p->exp) {
			el = createElement(q->coeff, q->exp);
			sortInsert(r, r->next, el);
			q = q->next;
			r = r->next;
		}
		else if (p->exp == q->exp) {
			if ((p->coeff + q->coeff) != 0) {
				el = createElement((p->coeff + q->coeff), p->exp);
				sortInsert(r, r->next, el);
				r = r->next;
			}
			p = p->next;
			q = q->next;
		}
	}

	if ((NULL == p) && (NULL != q)) {
		if (copyList(q, r) != 0)
			return -1;
	}

	if ((NULL == q) && (NULL != p)) {
		if (copyList(p, r) != 0)
			return -1;
	}

	return 0;
}

int multiplication(Position p, Position q, Position r)
{
	Position temp = NULL;
	Position el = NULL;

	Node head;
	head.next = NULL;
	Node rcopy;
	rcopy.next = NULL;

	Position pom = NULL;

	p = p->next;
	q = q->next;
	int coeff, exp;

	temp = q;

	if (p == NULL && q == NULL) {
		printf("Lists are empty\n");
		return 0;
	}

	if (p == NULL) {
		copyList(q, r);
		return 0;
	}

	if (q == NULL) {
		copyList(p, r);
		return 0;
	}

	while (p != NULL) {
		pom = &head;
		while (q != NULL) {
			coeff = p->coeff * q->coeff;
			exp = p->exp + q->exp;
			el = createElement(coeff, exp);
			sortInsert(pom, pom->next, el);
			q = q->next;
			pom = pom->next;
		}

		q = temp;
		p = p->next;
		deleteList(r);
		addition(&head, &rcopy, r);
		deleteList(&rcopy);
		copyList(r->next, &rcopy);
		deleteList(&head);
	}

	return 0;
}

int deleteList(Position p)
{
	Position temp = NULL;

	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}

	return 0;
}
