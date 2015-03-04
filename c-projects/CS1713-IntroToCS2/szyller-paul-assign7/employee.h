# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>

typedef struct
{
	int numElements;
	int maxSize;
	char * name;
} DynamicString;

typedef struct
{
	int id;
	DynamicString *name;
	int age;
	double salary;
} Employee;

typedef struct
{
	int numElements;
	int maxSize;
	Employee ** employees;
} DynamicArray;

	FILE *openInFile (char *filename);
	DynamicArray * construct(int initialCapacity);
	int insert (Employee *dataPoint, DynamicArray *data);
	DynamicString * constructStr(int initialCapacity);
	int insertStr (char dataPoint, DynamicString *str);
	void readData (DynamicArray *workforce, FILE *fp);
	void printReport (DynamicArray *workforce);
