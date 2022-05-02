#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
#define MaxPoints 50

typedef struct {
	char firstName[MAX];
	char lastName[MAX];
	int points;
} student;

int CountStudents(char *);
int ReadFromFile(char *, int, student *);
int PrintStudents(int, student *);

int main(void) {

	student* students;
	char fileName[MAX];
	int n;

	printf("Insert name of a file: ");
	scanf(" %s", fileName);

	n = CountStudents(fileName);

	if (n == -1)
		return 1;

	students = (student *)malloc(n * sizeof(student));

	if (ReadFromFile(fileName, n, students) == -1)
		return -1;

	if (PrintStudents(n, students) != 1)
		return -1;

	free(students);

	return 0;
}

int CountStudents(char *FileName)
{
	FILE *fp = NULL;
	int n = 0;
	
	fp = fopen(FileName, "r");

	if (NULL == fp) {
		printf("File opening failed!!\n");
		return -1;
	}

	while (!feof(fp)) {
		if (fgetc(fp) == '\n') n++;
	}

	fclose(fp);

	return n;
}

int ReadFromFile(char *FileName, int n, student *s)
{
	FILE *fp = NULL;
	int i = 0;

	fp = fopen(FileName, "r");

	if (NULL == fp) {
		printf("File opening failed!!\n");
		return -1;
	}

	for (i = 0; i < n; i++) 
		fscanf_s(fp, "%s %s %d", (s + i)->firstName, MAX, (s + i)->lastName, MAX, &(s + i)->points);

	fclose(fp);

	return 1;
}

int PrintStudents(int n, student *s)
{
	int i = 0;
	float x;

	printf("\n%15s\t%15s\t%15s\t%15s\n", "First name", "Last name", "Abs. points", "Rel. points");

	for (i = 0; i < n; i++)
		printf("%15s\t%15s\t%15d\t%15.2f\n", (s + i)->firstName, (s + i)->lastName, (s + i)->points, ((s + i)->points / (float)MaxPoints) * 100);

	return 1;
}