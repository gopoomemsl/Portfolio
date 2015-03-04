#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

	void findCommonWords (char *s1, char *s2, char *result);

int main (int args, char *argsv[])
{
	char s1[1024];
	char s2[1024];	
	char result[1024];
	
	printf ("Enter first sentence: ");
	fgets (s1, 1024, stdin);
	printf ("Enter second sentence: ");
	fgets (s2, 1024, stdin);
	

	findCommonWords (s1, s2, result);
	printf("Common Words: %s\n", result);
	
	return 1;
}

/*void findCommonWords (char *s1, char *s2, char *result)
{
	int i, j, k = 0;
  char tempstr[1024];
	
	for (i = 0; s1[i]; i++)
	{
		for (j = 0; s2[j]; j++)
		{
			while (s1[i] == s2[j])
			{
				tempstr[k++] = s1[i];
				if (s1[i] == ' ' || s1[i] == '\t')
				{
					strcat (result, tempstr);
					strcat (result, " ");
					strcpy (tempstr, "");
					i++;
					j++;
				}
				i++;
				j++;
			}
		}
	}
}*/

void findCommonWords (char *s1, char *s2, char *result)
{
	int i, j, k = 0;
  char tempstr[1024];
	
	for (i = 0; s1[i]; i++)
	{
		for (j = 0; s2[j]; j++)
		{
			while (s1[i] == s2[j])
			{
				tempstr[k++] = s1[i];
				if ((s1[i] == ' ' || s1[i] == '\t') && (s2[j] == ' ' || s2[j] == '\t'))
				{
					strcat (result, tempstr);					
					//memset (tempstr, 0, 1024);
					k = 0;
				}
				i++;
				j++;
			}
			while (s1[i] != s2[j] && s2[j])
			{
				j++;
			}
		}
	}
}

