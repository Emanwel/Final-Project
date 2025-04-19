#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//player initialization

struct player
{
        char *name;
        int pronouns;
        int personality;                 //kamo bahala if iapil ni or dili
		
		// apilon pa ni?
        float hunger;
        float thirst;
        float health;

        int energy;
        int knowledge;
        int happiness;

        int inventory[5];         //iapil pa ni? Basig naa moy magamit ani
} player;

//interaction mechanics
void Dialogue();
void Calculate();
void Decision();
void RandEventCheck();
void Ending();

int main ()
{
        return 0;
}