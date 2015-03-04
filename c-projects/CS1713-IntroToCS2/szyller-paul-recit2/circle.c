// Joshua Thomas
// Thomas Means
// Paul Szyller
// Xavier Gilmore
// Bryce Dumler

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
typedef int bool;
#define true 1
#define false 0

	int generateRandom (int lBound, int uBound);
	void generateArray (int points [][1], int radius, int iterations);
	bool isInCircle (int radius, int points [][1], int pointNumber);
	double calculateArea (int radius, int points [][1], int iterations);
	
int main ()
{
	int radius = 0;
	int seedInput = 0;
	printf ("Enter a radius and a seed: ");
	scanf ("%i %i", &radius, &seedInput);	
	srand(seedInput);
	
	printf ("\titerations\testimate\n");
	
	int i;
	for ( i = 100; i < 1001; i = i + 100)
	{
		int points [i][1];
		generateArray(points , radius, i);
		double area = calculateArea (radius, points, i);
		printf ("\t%i\t\t%.6lf\n", i, area);
	}
	printf ("\n");
	
	double exactArea = M_PI * pow(radius, 2);
	printf ("Exact area: %.6lf\n", exactArea);
	return(1);
}

int generateRandom (int lBound, int uBound)
{
	return rand()%(uBound - lBound) + lBound;
}

void generateArray ( int points [][1], int radius, int iterations)
{
	int i, j;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < iterations; j++)
		{
			points [i][j] = generateRandom (((-1)*radius), radius);
		}
	}
	return;
}

bool isInCircle (int radius, int points [][1], int pointNumber)
{
	int x = points[pointNumber][0];
	int y = points[pointNumber][1];
	double xSquare = pow((double)x, 2);
	double ySquare = pow((double)y, 2);
	double dCenterToPoint = sqrt(xSquare + ySquare);
	
	if ( dCenterToPoint <= radius )
	{
		return true;
	}
	else
	{
		return false;
	}
}

double calculateArea (int radius, int points [][1], int iterations)
{
	int i;
	double circle = 0;
	for (i = 0; i < iterations; i++)
	{
		if (isInCircle(radius, points, i))
		{
			circle++;
		}
	}
	double ratio = circle / iterations;
	double squareArea = pow(radius*2, 2);
	double area = ratio * squareArea;
	return area;
}


