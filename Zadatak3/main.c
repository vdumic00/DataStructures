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

//Zadatak 3
int insertAfterPerson(Position, char*);
int insertBeforePerson(Position, char*);
Position findPreviousPerson(Position, char*);
int sortListByLastName(Position);
int printInFile(Position, char*);
int readFromFile(Position, char*);

//Zadatak 2
Position create(char*, char*, int);
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
	char fileName[MAX];

	printf("Insert name of a file you want to read from: ");
	scanf(" %s", fileName);
	if (readFromFile(&head, fileName) != 0)
		return -1;

	if (printList(&head) != 0)
		return -1;

	puts("");

	printf("Insert last name after which you want to add new person: ");
	scanf(" %s", lastName);
	if(insertAfterPerson(&head, lastName) != 0)
		return -1;

	puts("");

	printf("Insert last name before which you want to add new person: ");
	scanf(" %s", lastName);
	if(insertBeforePerson(&head, lastName) != 0)
		return -1;

	puts("");

	if (printList(&head) != 0)
		return -1;

	if (sortListByLastName(&head) != 0)
		return -1;

	printf("\nSorted list:\n");
	if (printList(&head) != 0)
		return -1;

	puts("");

	printf("Insert name of a file you want to write in: ");
	scanf(" %s", fileName);
	if (printInFile(&head, fileName) != 0)
		return -1;

	return 0;
}

int insertAfterPerson(Position head, char *lastName)
{
	Position el = NULL;
	Position tmp = NULL;

	printf("Insert person:\n");
	el = insertPerson();

	tmp = findPerson(head, lastName);
	if (insertAfter(tmp, el) != 0) {
		printf("Inserting failed!\n");
		return -1;
	}
	
	return 0;
}

int insertBeforePerson(Position head, char *lastName)
{
	Position el = NULL;
	Position tmp = NULL;

	printf("Insert person:\n");
	el = insertPerson();

	tmp = findPreviousPerson(head, lastName);
	if (insertAfter(tmp, el) != 0) {
		printf("Inserting failed!\n");
		return -1;
	}

	return 0;
}

Position findPreviousPerson(Position p, char *lastName)
{
	while (p != NULL && strcmp(p->next->lastName, lastName))
		p = p->next;

	if (NULL == p) {
		printf("Person not found!\n");
		return NULL;
	}

	return p;
}

int sortListByLastName(Position head)
{
	Position p = NULL, prev = NULL;
	Position tmp = NULL, stop = NULL;

	while (head->next != stop) {
		prev = head;
		p = head->next;
		while (p->next != stop) {
			if (strcmp(p->lastName, p->next->lastName) > 0) {
				tmp = p->next;
				p->next = tmp->next;
				prev->next = tmp;
				tmp->next = p;
				p = tmp;
			}
			prev = p;
			p = p->next;
		}
		stop = p;
	}
	
	return 0;
}

int printInFile(Position head, char *fileName)
{
	FILE *fp = NULL;
	Position p = NULL;
	fp = fopen(fileName, "w");

	if (NULL == fp) {
		printf("File opening failed!\n");
		return -1;
	}
	fprintf(fp, "%30s%30s%30s\n", "First name", "Last name", "Birth year");

	for (p = head->next; p != NULL; p = p->next) {
		fprintf(fp, "%30s%30s%30d\n", p->firstName, p->lastName, p->birthYear);
	}

	fclose(fp);

	return 0;
}

int readFromFile(Position head, char *fileName)
{
	FILE *fp = NULL;
	Position el = NULL;
	char firstName[MAX], lastName[MAX];
	int birthYear;

	fp = fopen(fileName, "r");

	if (NULL == fp) {
		printf("File opening failed!\n");
		return -1;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %s %d\n", firstName, lastName, &birthYear);
		el = create(firstName, lastName, birthYear);
		if (insertAfter(head, el) != 0) {
			printf("Inserting failed!\n");
			return -1;
		}
	}

	fclose(fp);

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