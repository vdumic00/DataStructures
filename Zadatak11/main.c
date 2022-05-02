#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE (1024)

struct _node;
typedef struct _node* Position;
typedef struct _node {
	char firstName[NAME_SIZE];
	char lastName[NAME_SIZE];
	int idNumber;
	Position next;
} Node;

int insertInHash(char*, char*, int, Node*);
int findIndex(char*);
Position createNode(char*, char*, int);
Position findPositionLastName(Position, Position);
Position findPositionFirstName(Position, Position);
int insertNode(Position, Position);
int printList(Position);
int printHash(Node*);
int findPerson(char*, char*, Node*);
Position findByLastName(char*, char*, Position);
Position findByFirstName(char*, char*, Position);
int deleteList(Position);
int deleteHash(Node*);

int main() {
	Node hash[11];
	int i, stop;
	char fName[NAME_SIZE], lName[NAME_SIZE];
	int idNum;

	for (i = 0; i < 11; i++)
		hash[i].next = NULL;

	do {
		printf("Please press 1 if you want to insert person, press 0 to stop: ");
		scanf("%d", &stop);

		if (stop == 1) {
			printf("First name: ");
			scanf(" %s", fName);

			printf("Last name: ");
			scanf("%s", lName);

			printf("Identification number: ");
			scanf("%d", &idNum);

			insertInHash(fName, lName, idNum, hash);

			puts("");
		}
	} while (stop != 0);

	printf("Hash list:\n");
	printHash(hash);
	puts("");

	do {
		printf("Please press 1 if you want to find person, press 0 to stop: ");
		scanf("%d", &stop);

		if (stop == 1) {
			printf("First name: ");
			scanf(" %s", fName);

			printf("Last name: ");
			scanf("%s", lName);

			printf("Identification number is: %d\n", findPerson(fName, lName, hash));
		}
	} while (stop != 0);

	deleteHash(hash);

	return EXIT_SUCCESS;
}

int insertInHash(char* firstName, char* lastName, int idNum, Node* hash)
{
	Position p = NULL;
	int i;

	p = createNode(firstName, lastName, idNum);
	if (NULL == p)
		return -1;

	i = findIndex(lastName);

	insertNode(&hash[i], p);

	return 0;
}

int findIndex(char* lastName)
{
	int i, sum = 0;

	for (i = 0; i < 5; i++)
		sum += lastName[i];

	return sum % 11;
}

Position createNode(char* firstName, char* lastName, int idNum)
{
	Position p = NULL;

	p = (Position)malloc(sizeof(Node));

	if (NULL == p) {
		printf("Memory allocation failed!\r\n");
		return NULL;
	}

	strcpy(p->firstName, firstName);
	strcpy(p->lastName, lastName);
	p->idNumber = idNum;
	p->next = NULL;

	return p;
}

Position findPositionLastName(Position head, Position p)
{
	Position q = head;

	if (q->next != NULL && strcmp(p->lastName, q->next->lastName) == 0) {
		return findPositionFirstName(q, p);
	}

	while (q->next != NULL && strcmp(p->lastName, q->next->lastName) > 0) {
		if (strcmp(p->lastName, q->next->lastName) == 0)
			return findPositionFirstName(q, p);

		q = q->next;
	}

	return q;
}

Position findPositionFirstName(Position q, Position p)
{
	while (q->next != 0 && strcmp(p->lastName, q->next->lastName) == 0 && strcmp(p->firstName, q->next->firstName) > 0)
		q = q->next;

	return q;
}

int insertNode(Position head, Position p)
{
	Position q = NULL;

	q = findPositionLastName(head, p);

	p->next = q->next;
	q->next = p;

	return 0;
}

int printList(Position p)
{
	if (NULL == p) {
		printf("List is empty!\r\n");
		return 0;
	}

	p = p->next;

	while (p != NULL) {
		printf("%15s %15s %15d\n", p->firstName, p->lastName, p->idNumber);
		p = p->next;
	}

	return 0;
}

int printHash(Node* hash)
{
	int i;

	for (i = 0; i < 11; i++) {
		printf("Position %d:\n", i);
		printList(&hash[i]);
	}

	return 0;
}

int findPerson(char* firstName, char* lastName, Node* hash)
{
	int i;
	Position p = NULL;

	i = findIndex(lastName);

	p = findByLastName(lastName, firstName, &hash[i]);

	if (NULL == p)
		return 0;

	return p->idNumber;
}

Position findByLastName(char* lastName, char* firstName, Position p) 
{
	if (NULL == p->next) {
		printf("Person doesn't exist in list!\r\n");
		return NULL;
	}

	p = p->next;

	if (strcmp(p->lastName, lastName) == 0)
		return findByFirstName(lastName, firstName, p);

	while (p != NULL && strcmp(p->lastName, lastName) != 0){
		if (strcmp(p->next->lastName, lastName) == 0)
			return findByFirstName(lastName, firstName, p);

		p = p->next;
	}

	return p;
}

Position findByFirstName(char* lastName, char* firstName, Position p)
{
	while (p != NULL && strcmp(p->lastName, lastName) == 0 && strcmp(p->firstName, firstName) != 0)
		p = p->next;

	return p;
}

int deleteList(Position head)
{
	Position tmp = NULL, p = head->next;

	if (NULL == p)
		return 0;

	while (p != NULL) {
		tmp = p->next;
		free(p);
		p = tmp;
	}

	head->next = NULL;

	return 0;
}

int deleteHash(Node* hash)
{
	int i;

	for (i = 0; i < 11; i++)
		deleteList(&hash[i]);

	return 0;
}