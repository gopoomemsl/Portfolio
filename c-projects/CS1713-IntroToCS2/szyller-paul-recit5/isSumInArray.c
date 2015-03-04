// Thomas Means
// Paul Szyller
// Xavier Gilmore
// Bryce Dumler

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

	void initializeArray (int array []);
	void organizeArray (int array []);
	bool isSumOfArray (int array [], int n, int *index1, int *index2);
	
int main (int args, char *argsv [])
{
	int array[20];
	initializeArray (array);
	organizeArray (array);
		
	int n;
	printf ("Enter a number\n");
	scanf ("%i", &n);
	
	int index1, index2;
	if (!isSumOfArray (array, n, &index1, &index2))
	{
		printf ("There are no shuch pair of numbers\n");
	}
	else
	{
		printf ("data[%i] + data[%i] = %i + %i = %i\n", index1, index2, array[index1], array[index2], n);
	}
	
	return(0);
}

void initializeArray (int array [])
{
	int i;
	for (i = 0; i < 10; i++)
	{
		array[i] = pow(2, i+1);
		array[i+10] = pow(3, i+1);
	}
}

void organizeArray (int array [])
{
	int i, j, temp;
	for (i = 0; i < 19; i++)
	{
		for (j = i + 1; j < 20; j++)
		{
			if (array[i] >= array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

bool isSumOfArray (int array [], int n, int *index1, int *index2)
{
	int i, j;
	for (i = 0; i < 19; i++)
	{
		for (j = i + 1; j < 20; j++)
		{
			if (array[i] + array[j] == n)
			{
				*index1 = i;
				*index2 = j;
				return true;
			}
		}
	}
	return false;
}
