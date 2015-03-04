#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// this method takes in 2 int values as parameters and returns a random int between
//  those 2 values
int generateRandom (int lBound, int uBound) 
{
	return rand() % (uBound - lBound) + lBound;
}

// this method takes in an int as the chance for team 1
// to win a game and returns a different value based on
// the result of the game
int playGame (int chance)
{
	int num = generateRandom(1, 100); //generates random number between 1-100
	int result = 0; //declaring the result variable
	if ( num <= chance )//compares the user input to the random number to simulate probability
	{
		result = 1; //return 1 if team 1 won
	}	
	else if ( chance > num )
	{
		result = 0; //return 0 if team 1 lost
	}
	return result;
}

// this method takes in an int as the chance for team 1 to win any given game, calls
// the playGame method until one team has won 4 times to simulate a playoff, and 
// return a different value based on the result of that playoff
int playPlayoff (int chance)
{
	int score1 = 0;
	int score2 = 0;
	
	while ( score1 < 4 && score2 < 4 ) //keeps on playing games until a team reaches 4 wins
	{
		int gameResult = playGame(chance);
		if ( gameResult == 1 ) //if team 1 wins a game
		{
			score1++; //increase team 1's score
		}
		else if ( gameResult == 0 ) //if team 2 wins
		{
			score2++; //increase team 2's score
		}
	}
	if ( score1 == 4 ) //if team 1 reaches 4 pts and wins the playoff, return 1
	{
		return 1;
	}
	else if ( score2 == 4 ) //if team 2 reaches 4 pts and wins the playoff, return 0
	{
		return 0;
	}
}

// this method takes in an int as the chance for team 1 to win any given game, calls
// the playPlayoff method until one team has won 10 more playoffs than the other team
// to simulate a championship. The method prints out the number of the team winning each
// playoff, and then prints out the championship winner.
void playChampionship (int chance)
{
	int score1 = 0;
	int score2 = 0;
	
	while ( !(score1 - score2 == 10) && !(score2 - score1 == 10) ) 
	//keeps playing playoffs until one team wins 10 more than the other
	{
		int playoffResult = playPlayoff(chance);
		if ( playoffResult == 1 ) //if team 1 wins a playoff
		{
			printf ("1"); //print 1
			score1++; //and increase team 1's score
		}
		else if ( playoffResult == 0 ) //if team 2 wins a playoff
		{
			printf ("2"); //print 2
			score2++; //and increase team 2's score
		}
	}
	if ( score1 - score2 == 10 ) //if team 1 wins 10 more playoffs than team 2 
	{
		printf ("\nTeam 1 won the championship!"); //announce team 1 as championship winner
	}
	else if ( score2 - score1 == 10 ) //if team 2 wins 10 more playoffs than team 1
	{
		printf ("\nTeam 2 won the championship!"); //announce team 2 as championship winner
	}
}

// This is the main method, it prints out a header for the assignment, prompts the user
// for the chance of team 1 winning any given game, than calls on the playChampionship 
// method to launch the whole program. The method also uses a loop to make sure the input
// values is within bounds and keeps prompting the user if it isn't.
int main (int argc, char *argv[])
{
	printf ("Assignment 1 written by Paul Szyller.\n"); //header
	int chance = 0;
	printf ("Enter the percent chance that team 1 wins a game (0-100):"); //prompt
	scanf ("%d", &chance); //scan for user input
	
	while ( chance < 0 || chance > 100 ) //keep sending an error message and re prompting when value is out of bounds
	{
		printf ("Value out of bounds! Insert a value between 0 and 100:");
		scanf ("%d", &chance);
	}
	
	srand(time(NULL)); 
	playChampionship(chance);
		
	return (0);
}