#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void debug() {printf("debug ni diri WAWAWAW");}

//player initialization

/* NOTE:

        Walay gamit nga gi structure ni nako actually kay usa ra
        ka player ang available, maybe magbutang kog like gimmick
        nga your past runs/players make appearances in random events.
        
*/

typedef struct player
{
        //char name[100];

        int hunger;

        int energy;
        int knowledge;
        int happiness;

} player;

/*
    statVect is basically the three stats nga important sa game, and is
    used sa pag modify sa player stats and sa random events. Gamit kaayo
    siya nga akoa siya gi vector actually.
*/

typedef struct statVect
{
    int energy;
    int knowledge;
    int happiness;
} statVect;

typedef struct rand_event
{
    int energy;
    int knowledge;
    int happiness;

    //choices
    statVect choice[4];
} rand_event;

//system functions
void Calculate(player *player, int action);
void Start();
void Read(const char *filename, int start, int end);
void Update(player *player);
int EventCheck(int p);
rand_event RandEventBuild(int type);

// [IMPORTANT] i modify ang value ani later once naa na ang game over
int gameOver = 0;
int day = 1;
int hour[] = {6,0};
int location = 1;

//conditions
int loseCount = 0;
int hungerCount = 0;        //depende if apilon nato si hunger
int studyCount = 0;
int isDayOne = 1;
int isWeekend = 0;
int checkCount = 0;

//interaction mechanics
void Dialogue();
void Decision(player *player);
void Ending();
void Talk(player *player);

//actions
void CheckWatch(player *player);
void DisplayStats(player *player);
void GoOutside(player *player);

//MAIN LOOP
//gamay kaayo siya kay functions do the heavy lifting here
int main ()
{
    //initialization
    	printf("[START DIALOGUE]\n");
        Start();
    player player = {50, 100, 50, 50};
    gameOver = 0;

        /*printf("\nInput Name >> ");
    fflush(stdout);
    scanf("%s", player.name);*/

    //gameloop
        while (!gameOver){
            checkCount = 0;
            if (day == 6 || day == 7 || day == 13 || day == 14) isWeekend = 1;
            else isWeekend = 0;
            printf("\n\n--DAY %i--\n\n", day);
            if (day == 15) Ending();
            DisplayStats(&player);
        }
        
        Ending();

        return 0;
}

//START
void Start(){
        printf(">> ");
        char buff[100];
        scanf("%s", buff);
        if (strcmp("START", buff) != 0) Start();
}

void Ending(){

}

int EventCheck(int p){
    checkCount = 1;
    int prob = rand() * 100 + 1;
    if (prob > p){
        return 1;
    }
    else return 0;
}

rand_event RandEventBuild(int type){
    int choose = rand() * 10 + 1;
    rand_event rand;
    int line = 1 + (choose - 1) * 12;
    Read("event.txt", line, line + 5);
    
    //get choicss of event
    FILE *file = fopen("numbers.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    //get choices
    
    return rand;
}

void Update(player *player){
    //clock update
    if (hour[1] >= 60){
        hour[0]++;
        hour[1] -= 60;
    }
    if (hour[0] >= 24){
        day++;
        hour[0] -= 24;
    }
    //energy update
    if (player->energy <= 0){
        //player passes out
        printf("\nYou passed out.");
        hour[0] = 6;
        hour[1] = 0;
        day++;
        location = 1;
        player->energy = 75;
        return;
    }
    
    if (player->happiness <= 0){
    	Ending();
    	exit(0);
    }
    
    if (player->knowledge <= 0){
    	Ending();
    	exit(0);
    }
    
    if (day >= 14) gameOver = 1;

    /*
        again optional na na ang hunger here, I was planning nga
        you can buy food sa mall with money pero basig too much na
        na siya. I might also change the mall to like an arcade or smthn.
    */
    if (hungerCount > 3){
        Ending();
    }

    //check if late ka sa school; schooltime is 9:00 to 18:00
    if (location != 2 && hour[0] >= 9 && hour[1] <= 18 && !isWeekend){
        printf("You're late for class. Go to school now.\n");
        player->knowledge--;
        player->happiness--;
    }

    Decision(player);
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

void DisplayStats(player *player){
    printf("\nEnergy: %i\n", player->energy);

    //day 1 base case
    if (isDayOne){
        Read("stats.txt", 1, 1);
        printf("\n");
        isDayOne = 0;
        Decision(player);
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

    if (location == 1) printf("You're at your home, sitting in front of your cluttered desk.\n");
    if (location == 2) printf("You're at the school, watching your teacher's canva slides show default template texts.\n");
    if (location == 3) printf("You're at the mall. The hustle and bustle of the different stalls around you deafen your own voice.\n");
    if (location == 4) printf("You're in a school event. One of your classes required your attendance here.\n");

    Decision(player);
}

void Calculate(player *player, int action){
    //delta varables
    statVect base = {0, 0, 0};
    statVect mod = {0, 0, 0};

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

    //actions possible
    base.energy = 5 + mod.energy;
    base.knowledge = 2 + mod.knowledge;
    base.happiness = 1 + mod.happiness;
    int studyTime = 0;

    switch (action){

        case 1:
            //study
            //ask for number of hours
            studySet:
                printf("\nEnter hours of studying (1-5)\n>> ");
                fflush(stdout);
                scanf("%i", &studyTime);
                if (studyTime > 5){
                    printf("Invalid Study Time, enter number from 1-5.");
                    goto studySet;
                }
            studyCount++;
            player->energy -= base.energy * studyTime;
            player->knowledge += base.knowledge * studyTime;
            player->happiness -= (base.happiness + studyCount) + studyTime;
            hour[0] += studyTime;
            if (studyCount >= 3) printf("You feel burnt out by the consecutive studying sessions.\n");
            Update(player);
            break;

        case 2:
            //play games
            if (location == 2) base.knowledge -= 5;
            if ((rand() % 20 + 1) >= 10){
                //win game
                int dialogue = rand() % 5 + 21;
                Read("stats.txt", dialogue, dialogue);
                loseCount = 0;
                base.happiness += mod.happiness;
            }
            else{
                //lose game
                int dialogue = rand() % 5 + 14;
                Read("stats.txt", dialogue, dialogue);
                printf("Losing Streak: %i\n", loseCount + 1);
                loseCount++;
                base.happiness -= loseCount;
            }
            player->energy -= base.energy;
            player->knowledge += base.knowledge;
            player->happiness -= base.happiness;
            hour[1] += 15;
            studyCount = 0;
            Update(player);
            break;

        case 3:
            //sleep
            if (location == 3) printf("You can't sleep in the mall.");
            else if (location == 1 && hour[0] >= 21){
                player->energy += base.energy + abs(hour[0] - 18);
                printf("\nSleeping through the night.\n");
                hour[0] = 6;
                hour[1] = 0;
                return;
            }
            else{
                player->energy += base.energy;
                hour[0] += 1;
                printf("\nYou took a nap for an hour to refresh your senses.\n");
                Update(player);
            }
            break;
    }
}

void CheckWatch(player *player){
    printf("You check the watch. It is %i:%02d.\n", hour[0], hour[1]);

    if (hour[0] >= 21) printf("It is past your bedtime.\n");
    else if (hour[0] >= 18) printf("The sun starts to set. You should be at home.\n");
    else if (hour[0] >= 12) printf("The heat of the sun shines through the windows.\n");
    else if (hour[0] >= 9) printf("It's time to attend school.\n");
    else if (hour[0] >= 6) printf("The morning breeze flows as you look around you.\n");
    else printf("You wonder what led you to be awake this late.\n");
    Decision(player);
}

void GoOutside(player *player){
    printf("\nWhere are you going today?\n\n");
    Read("stats.txt", 28, 30);
    printf("\n>> ");

    fflush(stdout);
    char input[1000];
    scanf("%s", input);
    int destination;

    if (strcmp("HOME", input) == 0) destination = 1;
    else if (strcmp("SCHOOL", input) == 0) destination = 2;
    else if (strcmp("MALL", input) == 0) destination = 3;
    else{
        printf("Invalid Input!\n");
        GoOutside(player);
    }
    if (destination == location){
        printf("You're already there.\n");
        GoOutside(player);
    }
    else location = destination;
    player->energy -= 20;
    hour[1] += 30;
    Update(player);
}

void Talk (player *player){
    if (EventCheck(80)){
        rand_event current_event = RandEventBuild(2);
    }
    else{
        printf("\nAll of your friends seem to be busy with their own tasks as of the moment.\n");
    }
    Update(player);
}

void Decision(player *player){

    printf("\nYou decide on what to do with your time.\n");
    Read("Input.txt", 1, 11);

    fflush(stdout);
    char input[1000];
    scanf("%s", input);

    //check the user's action
    if (strcmp("TIME", input) == 0) CheckWatch(player);
    else if (strcmp("STATS", input) == 0) DisplayStats(player);
    else if (strcmp("STUDY", input) == 0) Calculate(player,1);
    else if (strcmp("GAMES", input) == 0) Calculate(player,2);
    else if (strcmp("FRIENDS", input) == 0) Talk(player);
    else if (strcmp("OUTSIDE", input) == 0) GoOutside(player);
    else if (strcmp("SLEEP", input) == 0) Calculate(player,3);
    else if (strcmp("END", input) == 0) exit(0);
    else
    {
        printf("Invalid Input!\n");
        Decision(player);
    }
}