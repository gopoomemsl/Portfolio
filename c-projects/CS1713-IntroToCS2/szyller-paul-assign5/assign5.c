# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>

	
	bool ispalindrome (char *s);
	void strrev (char *s);
	char *strmakepalindrome (char *s);	
	
int main (int args, char * argsv[])
{		
	char s [1024];
	FILE *fp;
	
	fp = fopen(argsv[1], "r");
	
	if (fp == NULL)
	{
		printf("Error opening %s\n",argsv[1]);
		exit(0);
	}
	
	while (fgets (s, 1024, (FILE*)fp) != NULL)
	{	
		char *s2 = strmakepalindrome(s);
		printf ("%s", s2);
	}
}

bool ispalindrome (char *s)
{
	char *temp = s;
	strrev (s);
	if (strcmp(s, temp) == 0)
	{
		return true;
	}
	return false;
}

void strrev (char *s)
{
	
	char temp;
	int i, j;

	if ( s[0] == '\0' )
	{
		return;
	}
	
	for (j = 0; s[j] != '\0'; j++ );
	j--;

	for (i = 0; i < j; i++) 
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		j--;
	}
}

char *strmakepalindrome (char *s)
{
	if (!ispalindrome(s))
	{
		char rev [1024];
		strcpy (rev, s);
		strrev (rev);
		strcat (s, rev);
	}
	return s;
}
