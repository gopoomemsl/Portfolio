# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>

typedef struct {
	int x;
	int y;
	int HP;
	int LVL;
	int XP;
	int ATT;
	int DEF;
	char *name;
	char symbol;
	//Inventory inventory;
}Hero;

/*
typedef struct Iventory{
	Armor helm;
	Armor chest;
	Armor pants;
	....
	Weapon hand1;
	Weapon hand2;
};

typedef struct Armor{
	int armor;
	int hp;
	....
};

typedef struct Weapon{
	int att;
	int str;
	....
};
*/

//enemy
typedef struct {
	int x;
	int y;
	int HP;
	int ATT;
	int DEF;
	char *name;
	char symbol;
}Enemy;

	void readEnemyList(char *enemyFileName);
	void printEnemyList();
	void freeMemory();
	void generateGameGrid();
	void initialization();
	void printGameGrid();
	void heroMove (char dir);
	Enemy * getEnemy(char enemyType);
	int clamp (int value, int min, int max);
	void fight (char enemyType, int x, int y);
