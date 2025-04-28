#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define debug "DEBUG NI"

//player initialization

/* NOTE:

	Walay gamit nga gi structure ni nako actually kay usa ra
	ka player ang available, maybe magbutang kog like gimmick
	nga your past runs/players make appearances in random events.
	
*/

typedef struct player
{
        char name[100];
		
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
void Read();

// [IMPORTANT] i modify ang value ani later once naa na ang game over
int gameOver = 1;

//interaction mechanics
void Dialogue();
void Decision();
void RandEventCheck();
void Ending();

//actions
void CheckWatch();
void DisplayStats();
void GoOutside();

int main ()
{
    //initialization
	Start();
    player player = {.happiness = 70, .energy = 100, .knowledge = 70};
	
	printf("Input Name >> ");
	scanf("%s", player.name);

    //gameloop
    int day = 1;
    int hour = 700;

    do {
        printf("\n\n--DAY %i--\n\n", day);
        DisplayStats(1, &player, day, &hour);
    }
    while (!gameOver);
	
	return 0;
}

//START
void Start(){
	printf("[START DIALOGUE]\n");
	char buff[100];
	scanf("%s", buff);
	if (strcmp("START", buff) != 0) Start();
}

void Read(const char *filename, int start, int end){
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL){
        perror("ERROR RETURNING FILE");
        return;
    }

    char buff[1000];
    int current = 1;

    while(fgets(buff, 1000, fptr)){
        if (current >= start && current <= end) printf("%s", buff);
        if (current > end) break;
        current++;
    }
    fclose(fptr);
}

void DisplayStats(int location, player *player, int day, int *hour){
    printf("\nEnergy: %i\n", player->energy);

    //day 1 base case
    if (day == 1){
        Read("stats.txt", 1, 1);
        printf("\n");
        Decision(location, player, day, hour);
        return;
    }

    //conditionals

    /*
        Guys nalingaw gyud kog code HAHAHAHA so what this means kay
        depende sa threshold given sa ubos kay naay lain2 nga descriptions
        ihatag ang program. In this case, naa sila'y lain2 nga dialogue
        
        For example:
        Kung big imo knowledge pero di pa kaayo, moingon ang program ug
        "You feel relieved, knowing that you retain the studies from what you have studied for."
    */

    if (player->knowledge >= 70) Read("stats.txt", 3, 3);
    else if (player->knowledge >= 50) Read("stats.txt", 4, 4);
    else if (player->knowledge >= 30) Read("stats.txt", 5, 5);
    else if (player->knowledge < 30) Read("stats.txt", 6, 6);
    
    if (player->happiness >= 70) Read("stats.txt", 8, 8);
    else if (player->happiness >= 50) Read("stats.txt", 9, 9);
    else if (player->happiness >= 30) Read("stats.txt", 10, 10);
    else if (player->happiness < 30) Read("stats.txt", 11, 11);

    Decision(location, player, day, hour);
}

void Calculate(int location, player *player, int *hour, int action){
    //delta varables
    int d_energy, d_happiness, d_knowledge;

    //location modifiers

    /*
        Naay modifiers ang happiness ug ang knowledge depende kung asa ka
        kung mag study ka sa school, more effective ang +knowledge, less ang
        +happiness, kung naa kas party kay mas dali mahurot ang energy pero
        grabe ka dako ang +happiness, etc.
    */

    switch (location){
    case 1:
        //home modifiers
        break;
    case 2:
        //school modifiers
        break;
    case 3:
        //mall modifiers
        break;
    case 4:
        //event modifiers
        break;
    }

    switch (action){
        case 1:
            //study
            break;
        case 2:
            //play games
            break;
        case 3:
            //talk to friends
            break;
    }
}

void CheckWatch(){
    
}

void GoOutside(){
    
}

void Decision(int location, player *player, int day, int *hour){
    char input[1000];
    scanf("%s", input);

    //check the user's action
    if (strcmp("TIME", input) == 0) CheckWatch(location, player, day, hour);
    else if (strcmp("STATS", input) == 0) DisplayStats(location, player, day, hour);
    else if (strcmp("STUDY", input) == 0) Calculate(location, player, hour, 1);
    else if (strcmp("GAMES", input) == 0) Calculate(location, player, hour, 2);
    else if (strcmp("TALK TO FRIENDS", input) == 0) Calculate(location, player, hour, 3);
    else if (strcmp("GO OUTSIDE", input) == 0) GoOutside(location, player, hour);
    else
    {
        printf("Invalid Input!\n");
        Decision(location, player, day, hour);
    }
}
