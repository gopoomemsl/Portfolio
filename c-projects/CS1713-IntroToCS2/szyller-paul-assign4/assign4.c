#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

	void findCoins (int x, int *nP, int *nN, int *nD, int *nQ);

void main ()
{
	int n, nP, nN, nD, nQ, nTotal, max, x;
	printf ("Enter the number of coins\n");
	scanf ("%i", &n);
	
	max = n * 25;
	for (x = 1; x <= max; x++)
	{
		findCoins (x, &nP, &nN, &nD, &nQ);
		nTotal = nP + nN + nD + nQ;
		if (n == nTotal)
		{
			printf ("%5i cents: %5i quarters %5i dimes %5i nickels %5i pennies\n", x, nQ, nD, nN, nP);
		}
	}
	
	
	return;
}

void findCoins (int x, int *nP, int *nN, int *nD, int *nQ)
{
	*nQ = x / 25;
	x = x % 25;
	*nD = x / 10;
	x = x % 10;
	*nN = x / 5;
	*nP = x % 5;
}


/*I think there might be some errors in the sample execution.
What I mean is that the sample execution does not exactly answer the prompt of the assignment.
For the first example (execution with for an input n of 2), the sample output does not consider the possibility of 2 nickels for 10 cents.

If your sample program is written the same way as mine above, it is probably because the function findCoins is written to find the minimum number of coins for each x value.
So the final output ends up being a list of every value x that can be reached with a minimum of n coins, not the full list of all the values that can be found using n coins.

When n is 2, we only miss 1 possibility, but as n increases, more possibilities are missed.*/
