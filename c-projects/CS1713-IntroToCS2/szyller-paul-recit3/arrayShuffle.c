// Thomas Means
// Paul Szyller
// Xavier Gilmore
// Bryce Dumler

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

	void initializeArray (int array [], int num);
	void shuffleArray (int array []);
	int generateRandom (int lBound, int uBound);
	void checkArray (int array [], int num, int *r1, int *r2, bool *x);
	
int main ()
{
	int array [50];
	int num = 0;
	int result1 = 0;
	int result2 = 0;
	bool isInRange = false;
	
	printf ("Enter a number for last array location\n");
	scanf ("%i", &num);
	
	initializeArray (array, num);	
	shuffleArray (array);
	checkArray (array, num, &result1, &result2, &isInRange);
	
	if (isInRange)
	{
		printf ("data[%i] = %i\ndata[%i] = %i\n", result1, num, result2, num);
	}
	else
	{
		printf ("There are no duplicates\n");
	}
	
	return 0;
}

void initializeArray (int array [], int num)
{
	int i;
	for (i = 0; i < 49; i++)
	{
		array [i] = i;
	}
	array [49] = num;
}

void shuffleArray (int array [])
{
	srand(time(0));
	int temp = 0;
	int i;
	for (i = 0; i < 25; i++)
	{	
		int rand1 = generateRandom (0, 50);
		int rand2 = generateRandom (0, 50);
		temp = array [rand1];
		array [rand1] = array [rand2];
		array [rand2] = temp;
	}
}

int generateRandom (int lBound, int uBound)
{
	return rand()%(uBound - lBound) + lBound;
}

void checkArray (int array [], int num, int *r1, int *r2, bool *x)
{
	int count = 0;
	int temp;
	
	int i;
	for (i = 0; i < 49; i++)
	{
		if (array[i] == num)
		{
			count++;
			if (count == 2)
			{
				*r1 = temp;
				*r2 = i;
				*x = true;
				return;
			}
			temp = i;
		}
	}
	return;
}
