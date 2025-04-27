#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//player initialization

/* NOTE:

	Walay gamit nga gi structure ni nako actually kay usa ra
	ka player ang available, maybe magbutang kog like gimmick
	nga your past runs/players make appearances in random events.
	
*/

struct player
{
        char name[100];
        int pronouns;
		
		// apilon pa ni?
        float hunger;
        float health;

        int energy;
        int knowledge;
        int happiness;

} player;


//system functions
void Calculate();
void Start();
void InitFiles();
void Read();

//interaction mechanics
void Dialogue();
void Decision();
void RandEventCheck();
void Ending();

int main ()
{
	Start();
	
	//get name
	printf("Input Name >> ");
	fgets(player.name, 20, stdin);
	
	//pronouns
	printf("[PRONOUN DIALOGUE]\n");
	fgets(player.pronouns, 1, stdin);
	
	//initialize stats; I think naay better way sa pag initialize ani
	player.energy = 100;
	player.knowledge = 50;
	player.happiness = 50;
	
	
	return 0;
}

//START
void Start(){
	printf("[START DIALOGUE]\n");
	char buff[6];
	fgets(buff, 6, stdin);
	if (strcmp("START", buff) != 0) Start();
}