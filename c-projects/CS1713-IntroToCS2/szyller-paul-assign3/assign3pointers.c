// Paul Szyller
// CS1713
// Assign3 - Majority

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

void findMajority (int array[], int *p1, bool *p2);

void main ()
{
	int array [7];
			
	printf ("Enter 7 numbers\n");
	scanf ("%i %i %i %i %i %i %i", &array[0], &array[1], &array[2], &array[3], &array[4], &array[5], &array[6]);
	
	int majority = 0;
	bool isMaj = false;
	
	findMajority (array, &majority, &isMaj);	
	
	if (!isMaj) 
	{
		printf ("No Majority\n");
	}
	else 
	{
		printf ("Majority = %i\n", majority);
	}
}

void findMajority (int array[], int *p1, bool *p2) 
{		
	int i, j;
	for (i = 0; i < 7; i++) 
	{
		int count = 0;
		for (j = i + 1; j < 7; j++) 
		{
			if (array[i] == array[j])
			{
				count++;
			}
		}
		if (count > 2) 
		{
			*p1 = array[i];
			*p2 = true;
			return;
		}
	}
	*p2 = false;
}
