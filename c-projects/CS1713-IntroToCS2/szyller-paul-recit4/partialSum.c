// Thomas Means
// Paul Szyller
// Xavier Gilmore
// Bryce Dumler

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

	int partialSum (int data[], int start, int end);
	void partialPrint (int data[], int start, int end);
	int generateRandom (int lBound, int uBound);
	int initializeArray (int data[]);
	
int main ()
{
	int start;
	int end;
	int data [15];
	int sum;
	
	initializeArray (data);
	
	printf ("Enter starting and ending index\n");
	scanf ("%i %i", &start, &end);
	
	partialPrint (data, start, end);
	sum = partialSum (data, start, end);
	printf ("\nSum from data[%i] to data[%i] is %i\n", start, end, sum);
	
	return 0;
}

int generateRandom (int lBound, int uBound)
{
	return rand()%(uBound - lBound) + lBound;
}

int initializeArray (int data[])
{
	srand (time(0));
	int i;
	for (i = 0; i < 15; i++)
	{
		int num = generateRandom (10, 20);
		data[i] = num;
	}	
}

void partialPrint (int data[], int start, int end)
{
	printf ("Partial Array Output:");
	
	int i;
	for (i = start; i <= end; i++)
	{
		printf ("\n%i %i", i, data[i]);
	}
}

int partialSum (int data[], int start, int end)
{
	int sum = 0;
	int i;
	for (i = start; i <= end; i++)
	{
		sum += data[i];
	}
	return sum;
}
