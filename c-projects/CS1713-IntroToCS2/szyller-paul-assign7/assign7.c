# include "employee.h"

int main (int args, char * argsv[])
{	
	printf("\nAssignment 7 written by Paul Szyller\n\n");
	FILE *fp = openInFile (argsv[1]);	
	DynamicArray *workforce = construct(0);
	readData (workforce, fp);
	
	int i;
	for (i = 0; workforce->employees[i]; i++)
	{
		free (workforce->employees[i]->name);
	}
	free (workforce);
}

FILE *openInFile (char *filename)
{
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error opening %s\n", filename);
		exit(0);
	}
	return fp;
}

DynamicArray * construct(int initialCapacity)
{
	DynamicArray * p;
	p = (DynamicArray *) malloc(sizeof(DynamicArray));
	if (p == NULL)
	{
		return NULL;
	}

	p->employees = (Employee **)malloc (sizeof(Employee*) * initialCapacity);
	if (p->employees == NULL)
	{
		return NULL;
	}
	
	p->numElements = 0;
	p->maxSize = initialCapacity;
	return p;	
}

int insert (Employee *dataPoint, DynamicArray *data)
{
	Employee **q;
	if (data->numElements == data->maxSize)
	{
		q = (Employee**)realloc(data->employees, (data->maxSize + 5)* sizeof(Employee*));
		if (q == NULL)
		{
			return (-1);
		}
		data->maxSize += 5;
		data->employees = q;
		printf("*** Resizing employee array from %i to %i ***\n\n", data->maxSize - 5, data->maxSize);
	}
	data->employees[data->numElements++] = dataPoint;
	/*--------TEST
	int i;
	for (i = 0; i < data->numElements; i++)
	{
		printf("\n%i\t%i", i, data->employees[i]->age);
	}
	printf("\n");
	-----------*/
	return (0);
}

DynamicString * constructStr(int initialCapacity)
{
	DynamicString * p;
	p = (DynamicString *) malloc(sizeof(DynamicString));
	if (p == NULL)
	{
		return NULL;
	}

	p->name = (char *)malloc (sizeof(char) * initialCapacity);
	if (p->name == NULL)
	{
		return NULL;
	}
	
	p->numElements = 0;
	p->maxSize = initialCapacity;
	return p;	
}

int insertStr (char dataPoint, DynamicString *str)
{
	char *q;
	if (str->numElements == str->maxSize)
	{
		q = (char*)realloc(str->name, (str->maxSize + 5)* sizeof(char));
		if (q == NULL)
		{
			return (-1);
		}
		str->maxSize += 5;
		str->name = q;
	}
	str->name[str->numElements++] = dataPoint;
	return (0);
}

void readData (DynamicArray *workforce, FILE *fp)
{
	char transaction[6];
	
	while (!feof(fp))
	{
		fscanf(fp, "%6[^|]", transaction);
		
		if (strcmp(transaction, "INSERT") == 0)
		{
			Employee temp;
			char tempstr[64];
			temp.name = constructStr(8);			
			fscanf(fp,"|%i|%64[^|]|%i|%lf\n", &temp.id, tempstr, &temp.age, &temp.salary);
			int i;
			for (i = 0; tempstr[i]; i++)
			{
				insertStr (tempstr[i], temp.name);
			}
			insert (&temp, workforce);
		}
		
		if (strcmp(transaction, "REPORT") == 0)
		{
			printReport(workforce);
			fscanf(fp, "\n");
		}
	}
}

void printReport (DynamicArray *workforce)
{
	printf("Employee Report for Big Jim's Pizza Haus\n");
	printf("Id     Name                         Age          Salary\n");
	printf("------ --------------------------- ----- --------------\n");
	
	if (workforce->numElements == 0)
	{
		printf("no employees to report!\n\n");
	}
	
	else
	{
		double totSalary, avgSalary = 0;
	
		int i;
		for (i = 0; workforce->employees[i]; i++)
		{
			printf("%-6i %-27s %5i %14.2lf\n", workforce->employees[i]->id, workforce->employees[i]->name->name, workforce->employees[i]->age, workforce->employees[i]->salary); 
			totSalary += workforce->employees[i]->salary;
		}
		avgSalary = totSalary / workforce->numElements;
		
		printf("Total Employees: %12i\nTotal salary: %15lf\nAverage salary: %13lf\n\n", workforce->numElements, totSalary, avgSalary);
	}
}
