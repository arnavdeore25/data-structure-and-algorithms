#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Department
{
	char code[6];
	int *rolls;
	int size;
	int capacity;
	struct Department *next;
};

int hashFunction(char dept[], int M)
{
	int h = 0;
	for (int i = 0; dept[i] != '\0'; i++)
	{
		h = (h * 31 + dept[i]) % M;
	}
	return h;
}

// Find department in bucket
struct Department *findDepartment(
	struct Department *head,
	char dept[])
{
	while (head != NULL)
	{
		if (strcmp(head->code, dept) == 0)
			return head;
		head = head->next;
	}
	return NULL;
}

// Binary search to find the position of a roll number in the sorted array
int binarySearch(int arr[], int size, int value)
{
	int low = 0;
	int high = size - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (arr[mid] == value)
			return mid;
		if (arr[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return low;
}

// Insert a roll number into the appropriate department
void insert(
	struct Department *table[],
	int M,
	char dept[],
	int roll)
{
	int index = hashFunction(dept, M);
	struct Department *d =
		findDepartment(table[index], dept);
	// if department not exists
	if (d == NULL)
	{
		d = malloc(sizeof(struct Department));
		if (d == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}
		strcpy(d->code, dept);
		d->size = 0;
		d->capacity = 4;
		d->rolls = malloc(d->capacity * sizeof(int));
		if (d->rolls == NULL)
		{
			free(d);
			printf("Memory allocation failed\n");
			exit(1);
		}
		d->next = table[index];
		table[index] = d;
	}
	int pos = binarySearch(d->rolls, d->size, roll);
	if (pos < d->size && d->rolls[pos] == roll)
		return;
	if (d->size == d->capacity)
	{
		d->capacity = d->capacity * 2;
		d->rolls = realloc(
			d->rolls,
			d->capacity * sizeof(int));
		if (d->rolls == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}
	}
	// shift element to right
	for (int i = d->size; i > pos; i--)
	{
		d->rolls[i] = d->rolls[i - 1];
	}
	d->rolls[pos] = roll;
	d->size++;
}

// search roll number
void search(
	struct Department *table[],
	int M,
	char dept[],
	int roll)
{
	int index = hashFunction(dept, M);
	struct Department *d =
		findDepartment(table[index], dept);
	if (d == NULL)
	{
		printf("NOT FOUND\n");
		return;
	}
	int pos = binarySearch(d->rolls, d->size, roll);
	if (pos < d->size && d->rolls[pos] == roll)
		printf("FOUND\n");
	else
		printf("NOT FOUND\n");
}

// rank of roll number
void rank(
	struct Department *table[],
	int M,
	char dept[],
	int roll)
{
	int index = hashFunction(dept, M);
	struct Department *d =
		findDepartment(table[index], dept);
	if (d == NULL)
	{
		printf("Rank not available\n");
		return;
	}
	int pos = binarySearch(d->rolls, d->size, roll);
	printf("%d\n", pos);
}

// delete roll number
void delete(struct Department *table[], int M, char dept[], int roll)
{
	int index = hashFunction(dept, M);
	struct Department *d = table[index];
	struct Department *prev = NULL;
	while (d != NULL && strcmp(d->code, dept) != 0)
	{
		prev = d;
		d = d->next;
	}
	if (d == NULL)
	{
		printf("Department not found\n");
		return;
	}
	// Find roll number
	int pos = binarySearch(d->rolls, d->size, roll);
	// Roll number not found
	if (pos >= d->size || d->rolls[pos] != roll)
	{
		printf("Roll number not found\n");
		return;
	}
	for (int i = pos; i < d->size - 1; i++)
		d->rolls[i] = d->rolls[i + 1];
	d->size--;
	// If department has no students left
	if (d->size == 0)
	{
		if (prev == NULL)
			table[index] = d->next;
		else
			prev->next = d->next;
		free(d->rolls);
		free(d);
	}
}

int main()
{
	int M, Q;
	printf("Enter the size of hash table: ");
	scanf("%d", &M);
	printf("Enter the number of queries: ");
	scanf("%d", &Q);
	// Allocate user entered size of hash table
	struct Department **table =
		calloc(M, sizeof(struct Department *));
	if (table == NULL)
	{
		printf("Memory allocation failed\n");
		return 1;
	}
	printf("Enter the queries in the format (INSERT/SEARCH/RANK/DELETE) department roll number:\n\n");
	for (int i = 0; i < Q; i++)
	{
		char operation[10];
		char dept[6];
		int roll;
		scanf("%s", operation);
		if (strcmp(operation, "INSERT") == 0)
		{
			scanf("%s %d", dept, &roll);
			insert(table, M, dept, roll);
		}
		else if (strcmp(operation, "SEARCH") == 0)
		{
			scanf("%s %d", dept, &roll);
			search(table, M, dept, roll);
		}
		else if (strcmp(operation, "RANK") == 0)
		{
			scanf("%s %d", dept, &roll);
			rank(table, M, dept, roll);
		}
		else if (strcmp(operation, "DELETE") == 0)
		{
			scanf("%s %d", dept, &roll);
			delete(table, M, dept, roll);
		}
	}

	// freeing the memory for both linked list and hash table
	for (int i = 0; i < M; i++)
	{
		struct Department *d = table[i];
		while (d != NULL)
		{
			struct Department *temp = d;
			d = d->next;
			free(temp->rolls);
			free(temp);
		}
	}
	free(table);

	return 0;
}