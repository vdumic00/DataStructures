#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

struct _node;
typedef struct _node *Position;
typedef struct _node {
	char firstName[MAX];
	char lastName[MAX];
	int birthYear;
	Position next;
} Node;


Position create(char* , char*, int);
int insertAfter(Position, Position);
int printList(Position);
int insertEnd(Position, Position);
Position findPerson(Position, char*);
int deletePerson(Position, char*);
Position insertPerson();

int main(void) {
	Node head;
	head.next = NULL;
	Position el = NULL;

	char lastName[MAX];

	printf("Please insert first person:\n");
	el = insertPerson();
	if (insertAfter(&head, el) != 0) {
		return -1;
	}

	puts("");

	printf("Please insert last person:\n");
	el = insertPerson();
	if (insertEnd(&head, el) != 0) {
		return -1;
	}

	puts("");
	if (printList(&head) != 0)
		return -1;

	printf("Insert last name of a person you want to find:\t");
	scanf(" %s", lastName);
	el = findPerson(&head, lastName);
	if (el != NULL)
		printf("Person found!\n");



	printf("Insert last name of a person you want to delete :\t");
	scanf(" %s", lastName);
	if (deletePerson(&head, lastName) == 0)
		printf("Person successfully deleted!\n");

	puts("");
	printList(&head);

	return 0;
}

Position create(char *firstName, char *lastName, int birthYear)
{
	Position el = NULL;

	el = (Position)malloc(sizeof(Node));

	if (NULL == el) {
		printf("Memory allocation failed!\n");
		return NULL;
	}

	strcpy(el->firstName, firstName);
	strcpy(el->lastName, lastName);
	el->birthYear = birthYear;

	return el;
}

int insertAfter(Position where, Position what) {
	what->next = where->next;
	where->next = what;

	return 0;
}

int printList(Position head)
{
	Position p = NULL;

	for (p = head->next; p != NULL; p = p->next) {
		printf("%s %s %d\n", p->firstName, p->lastName, p->birthYear);
	}

	return 0;
}


int insertEnd(Position where, Position what)
{
	Position p = NULL;
	p = where->next;

	while (p->next != NULL)
		p = p->next;

	what->next = p->next;
	p->next = what;

	return 0;
}

Position findPerson(Position p, char *lastName)
{
	while (p != NULL && strcmp(p->lastName, lastName))
		p = p->next;

	if (NULL == p) {
		printf("Person not found!\n");
		return NULL;
	}

	return p;
}

int deletePerson(Position p, char *lastName)
{
	Position tmp = p;

	while (p != NULL && strcmp(p->next->lastName, lastName))
		tmp = p->next;

	if (NULL != tmp) {
		p = tmp->next;
		tmp->next = p->next;
		free(p);
	}
	else {
		printf("Person not found!\n");
		return 1;
	}

	return 0;
}

Position insertPerson()
{
	Position p = NULL;
	char firstName[MAX];
	char lastName[MAX];
	int birthYear;

	printf("First name:\t");
	scanf(" %s", firstName);

	printf("Last name:\t");
	scanf(" %s", lastName);

	printf("Birth year:\t");
	scanf("%d", &birthYear);

	p = create(firstName, lastName, birthYear);

	return p;
}
