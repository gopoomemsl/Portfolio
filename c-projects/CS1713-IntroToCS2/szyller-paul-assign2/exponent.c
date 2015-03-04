// Paul Szyller
// CS 1713 assign 2
// exponent.c

// include appropriate libraries
# include <stdio.h>
# include <math.h>

	// prototypes
	double factorial (int n);
	double exponent (double x, int n);

// The main function prompts the user for input (n and x) and return a table showing 
// e^x with each row using a higher number for n until the input n is reached
int main ()
{
	double x = 0;
	int n = 0;
	printf ("Enter 2 values for n (needs to be an integer) and x respectively:");
	scanf ("%i %lf", &n, &x); //user input for x and n
	
	//print header (10 spaces for "i", 15 for "Approximation"
	printf ("%10s %15s\n", "i", "Approximation"); 
	printf ("-----------------------------------\n");
	
	//print table
	int i;
	for (i = 0; i <= n; i++) 
	//prints each approximation using all integers from 0 to input n as n in the equation
	{
		printf ("%10i %15.10lf\n", i, exponent(x, i));
	}
	printf ("Exact Value = %15.10lf\n", exp(x)); //prints exact value
	
	return 0;
}

//Takes in an integer and returns its factorial
double factorial (int n)
{
	double result = 1;
	int i;
	for (i = n; n > 0; n--)
	{
		result = result * n;
	}
	return result;
}


double exponent (double x, int n)
{
	double result = 0;
	int i;
	for (i = 0; i <= n; i++)
	{
		result = result + ( pow(x, i) / factorial(i) );
	}
	return result;
}
