#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//npc initialization
typedef struct outfit		//pang chuychuy ra ni, no graphics kay kulang tag oras, pwede ra ni wala
{
	int head;
	int body;
	int legs;
	int shoes;
} outfit;

struct npc
{
	char *name;
	int pronouns;
	int personality; 		//kamo bahala if iapil ni or dili
	
	float hunger;
	float thirst;
	float health;
	
	int love;
	int anger;
	
	int inventory[5]; 	//iapil pa ni? Basig naa moy magamit ani
	outfit clothes;		// pwede ra ni wala
} npc;

//interaction mechanics
void dialogue();


int main ()
{
	return 0;
}