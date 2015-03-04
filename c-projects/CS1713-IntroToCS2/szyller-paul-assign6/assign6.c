# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>

	DynamicArray * construct(int initialCapacity);
	int insert (Game *dataPoint, DynamicArray *data);
	void printInventory (DynamicArray *inventory);
	
typedef struct
{
	char name [64];
	double price;
	int stock;
} Game;

typedef struct
{
	int numElements;
	int maxSize;
	Game * items;
} DynamicArray;
	
int main (int args, char * argsv[])
{		
	FILE *fpIn;
	fpIn = fopen(argsv[1], "r");
	if (fpIn == NULL)
	{
		printf("Error opening %s\n",argsv[1]);
		exit(0);
	}
	
	DynamicArray *inventory = construct(5);
	Game temp;
	while (!feof(fpIn))
	{
		fscanf(fpIn, "%32[^,],%lf,%i\n", temp.name, &temp.price, &temp.stock);
		insert (&temp, inventory);
	}
	
	for (;;)
	{
		printInventory(inventory);
		printf("COMMAND: ");
		
		int choice;
		scanf ("%i", &choice);
		if (choice = getchar() == 'q')
		{
			break();
		}
		
		else if (inventory->items[choice-1]->stock > 0)
		{
			inventory->items[choice-1]->stock--;
		}
		
		else
		{
			printf ("***ERROR: %i. %s is OUT OF STOCK\n", choice, inventory->items[choice-1]->name);
		}
		
	}
	
	FILE *fpOut;
	fpOut = fopen (argsv[2], "w");
	if (fpOut == NULL)
	{
		printf("Error opening %s\n", argsv[2]);
		exit(0);
	}
	
	int i;
	for (i = 0; i < inventory->numElements; i++)
	{
		fprintf ("%s, %lf, %i\n", inventory->items->name, inventory->items->price, inventory->items->stock);
	}
}

DynamicArray * construct(int initialCapacity)
{
	DynamicArray * p;
	p = (DynamicArray *) malloc(sizeof(DynamicArray));
	if (p == NULL)
	{
		return NULL;
	}
	
	p->items = (Game *)malloc (sizeof(Game) * initialCapacity);
	if (p->items == NULL)
	{
		return NULL;
	}
		
	p->numElements = 0;
	p->maxSize = initialCapacity;
	return p;	
}

int insert (Game *dataPoint, DynamicArray *data)
{
	Game *q;
	if (data->numElements == data->maxSize)
	{
		q = (Game*)realloc(data->items, (data->maxSize + 5)* sizeof(Game));
		if (q == NULL)
		{
			return (-1);
		}
		data->maxSize += 5;
		data->items = q;
	}
	data->items[data->numElements++] = dataPoint;
	return (0);
}

void printInventory (DynamicArray *inventory)
{
	int i;
	for (i = 0; i < inventory->numElements; i++)
	{
		printf ("%i. %s, %lf, %i\n", i+1, inventory->items->name, inventory->items->price, inventory->items->stock);
	}
}