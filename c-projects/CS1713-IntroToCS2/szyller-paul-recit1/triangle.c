// Joshua Thomas
// Thomas Means
// Paul Szyller
// Xavier Gilmore
// Bryce Dumler


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char * argv[]) 
{
	double a = 0;
	double b = 0;
	double c = 0;

	for (a = 1; a < 41; a++)
	{
		for (b = a + 1; b  < 41; b++) 
		//b starts at a+1 to avoid getting all the permutations of the tripples
		{
			c = sqrt(a * a + b * b);
			if(c - (int)c == 0 && c < 41)
			//if the difference between c and (int)c is 0, than it must mean that c is a whole number
			{
 				printf("%d %d %d\n", (int) a, (int) b, (int)c);
			}
		}
	}
return 0;
}
