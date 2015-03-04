#include "rogueGame.h"

#define GRIDSIZE 20
#define MAX_NAME_LENGTH 16
#define ENEMY_SPAWN_RATE 10


/************************************
/!\
This program was being worked on during the last lectures of 
the semester and was never truly finished.
/!\
*************************************/

char gameGrid [GRIDSIZE][GRIDSIZE];
Hero hero;
Enemy * enemyList;
int numEnemyTypes;

int main (int args, char *argsv[])
{
	char input;
	char tempstr[16];
	bool quit = false;
	
	srand (time(0));
	readEnemyList("enemylist.txt");
	initialization();
	printGameGrid();
	
	while (!quit)
	{		
		printGameGrid();	
		fgets(tempstr, 16, stdin);
		input = tempstr[0];
		if (input == 'q')
			quit = true;
			
		heroMove(input);	
		if (hero.HP <= 0)
		{
			printf("%s died. Press q to quit or r to restart the game.\n", hero.name);
			fgets(tempstr, 16, stdin);
			input = tempstr[0];
			if (input == 'q')
				quit = true;
			if (input == 'r')
				initialization();
		}
	}
	
	freeMemory();
}

void readEnemyList(char *enemyFileName)
{
	FILE *fp;
	numEnemyTypes = 0;
	fp = fopen(enemyFileName, "r");
	if (fp == NULL)
	{
		exit(1);
	}
	fscanf(fp, "num_enemy_types= %i\n", &numEnemyTypes);
	enemyList = (Enemy *) malloc(sizeof(Enemy) * numEnemyTypes);
	
	int i;
	for (i = 0; i < numEnemyTypes; i++)
	{
		enemyList[i].name = (char *) malloc(sizeof(char) * MAX_NAME_LENGTH);
		fscanf (fp, "name= %s\nATT= %i\nDEF= %i\nHP= %i\nsymbol= %c\n\n", enemyList[i].name, &(enemyList[i].ATT), &(enemyList[i].DEF), &(enemyList[i].HP), &(enemyList[i].symbol));
	}
	fclose(fp);	
	
	//printEnemyList();
}

void printEnemyList()
{
	int i;
	for (i = 0; i < numEnemyTypes; i++)
	{
		printf("name = %s\n", enemyList[i].name);
		printf("ATT = %i\n", enemyList[i].ATT);
		printf("DEF = %i\n", enemyList[i].DEF);
		printf("HP = %i\n", enemyList[i].HP);
		printf("symbol = %c\n", enemyList[i].symbol);
	}
}

void freeMemory()
{
	int i;
	for (i = 0; i < numEnemyTypes; i++)
	{
		free(enemyList[i].name);
	}
	free(enemyList);
}

void generateGameGrid()
{
	int i, j;
	for (i = 0; i < GRIDSIZE; i++)
	{
		for (j = 0; j < GRIDSIZE; j++)
		{
			if (i == 0 || j == 0 || j == GRIDSIZE-1 || i == GRIDSIZE-1)
			{
				gameGrid[i][j] = '+';
			}
			else
			{
				if ( rand() % 100 < ENEMY_SPAWN_RATE)
				{
					gameGrid[i][j] = enemyList[rand() % numEnemyTypes].symbol;
				}
				else
				{
					gameGrid[i][j] = '-';
				}
			}
		}
	}
}

void initialization()
{
	generateGameGrid();
	hero.x = GRIDSIZE /2;
	hero.y = GRIDSIZE /2;
	hero.name = "Paul";
	hero.symbol = '@';
	hero.HP = 100;
	hero.ATT = 10;
	hero.DEF = 10;
	hero.LVL = 1;
	hero.XP = 0;
	gameGrid[hero.x][hero.y] = hero.symbol;
}

void printGameGrid()
{
	int i, j;
	for (i = GRIDSIZE-1; i>=0; i--)
	{
		for (j = 0; j < GRIDSIZE; j++)
		{
			printf ("%c", gameGrid[j][i]);
		}
		printf ("\n");
	}
}

void heroMove (char dir)
{
	int nextx = hero.x;
	int nexty = hero.y;
	
	if (dir == 'w') //n
		nexty++;
	else if (dir == 's') //s
		nexty--;
	else if (dir == 'a') //w
		nextx--;
	else if (dir == 'd') //e
		nextx++;
	
	if (gameGrid[nextx][nexty] == '-')
	{
		gameGrid[hero.x][hero.y] = '-';
		hero.x = nextx;
		hero.y = nexty;
		gameGrid[hero.x][hero.y] = hero.symbol;
	}
	else if (gameGrid[nextx][nexty] >= 'A' && gameGrid[nextx][nexty] <= 'Z')
	{
		fight(gameGrid[nextx][nexty], nextx, nexty);
	}
}

Enemy * getEnemy(char enemyType)
{
	int i;
	for (i = 0; i < numEnemyTypes; i++)
	{
		if (enemyType == enemyList[i].symbol)
			return &enemyList[i];
	}
	return NULL;
}

int clamp (int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

void fight (char enemyType, int x, int y)
{
	Enemy * enemy = getEnemy(enemyType);
	int enemyCurrentHP = enemy->HP;
	char input ' ';
	char tempstr[16];
	
	printf("e => attack\t\tr => run\n");	
	while (enemyCurrentHP > 0 && hero.HP > 0 && input != 'r')
	{
		printf ("%s's HP = %i\t\t%s's HP = %i\n", hero.name, hero.HP, enemy->name, enemyCurrentHP);
		fgets(tempstr, 16, stdin);
		input = tempstr[0];
		
		if (input == 'e')
		{
			int atk = clamp(hero.ATT - enemy->DEF, 0, 320000);
			printf("%s attack %s for %i points.\n", hero.name, enemy->name, atk);
			enemyCurrentHP -= atk;
		}
		
		if (enemyCurrentHP > 0)
		{
			int eAtk = clamp(enemy->ATT - hero.DEF, 0, 320000);
			printf("%s attack %s for %i points.\n", enemy->name, hero.name, eAtk);
			hero.HP -= eAtk;
		}
		
		if (input == 'r')
		{
			printf("%s ran away.\n", hero.name);
		}
	}
	
	if (enemyCurrentHP <= 0)
	{
		int xp = enemy->HP*2;
		printf("You vanquished %s and got %i XP.\n", enemy->name, xp);
		hero.XP += xp;
		gridGrid[x][y] = '-';
	}
}
