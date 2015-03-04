// Paul Szyller
// CS1713
// Assign3 - Majority

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

bool findMajority (int array[]);
int majority;

int main ()
{
	int array [7];
			
	printf ("Enter 7 numbers\n");
	scanf ("%i %i %i %i %i %i %i", &array[0], &array[1], &array[2], &array[3], &array[4], &array[5], &array[6]);
	
	if (!findMajority(array))
	{
		printf ("No Majority\n");
	}
	else
	{
		printf ("Majority = %i\n", majority);
	}
	
	return 0;
}

bool findMajority (int array[])
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
			majority = array[i];
			return true;
		}
	}
	return false;
}
