#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



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
    int line;

    //choices
    int choice[4][6];
} rand_event;

//system functions
void Calculate(player *player, int action);
void Start();
void Read(const char *filename, int start, int end);
void Update(player *player);
void gameloop (player *player);
int EventCheck(int p);
rand_event RandEventBuild();

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
void Dialogue(rand_event source, player *player);
void Decision(player *player);
void Ending(int p, player *player);
void Talk(player *player);

//actions
void CheckWatch(player *player);
void DisplayStats(player *player);
void GoOutside(player *player);

//repurposed nako ang debug btw, originally printf("debug ni") siya pero I used it pang display sa actual numerical stats
void debug(player *player) {printf("\nHappiness: %i\nKnowledge: %i\nHunger: %i\nDays Played: %i\n", player->happiness, player->knowledge, player->hunger, day);}

//MAIN LOOP
//gamay kaayo siya kay functions do the heavy lifting here

int main ()
{
    srand(time(NULL));		//para true random
    //initialization
    	Read("stats.txt", 69, 91);
        Start();
    player player = {20, 100, 50, 50};
    gameOver = 0;

    //gameloop
        while (!gameOver){
            gameloop(&player);
        }

        return 0;
}

//START
void Start(){
        printf(">> ");
        fflush(stdout);
        char buff[100];
        scanf("%s", buff);
        if (strcmp("START", buff) != 0) Start();
}

void gameloop(player *player){	//practically redundant nako pag implement btw ToT
    checkCount = 0;
    if (day == 6 || day == 7 || day == 13 || day == 14) isWeekend = 1;
    else isWeekend = 0;
    printf("\n\n--DAY %i--\n\n", day);
    if (day <= 7){
        Read ("art.txt", 21, 29);
        printf("\n\n");
        Read ("stats.txt", 33 + (day - 1) * 5, 36 + (day - 1) * 5);
    }
    DisplayStats(player);
}

//small scale dialogues akoa nalang gipaprint diretso opara di kaayo cluttered ang files
//the stats.txt file already has a cluttered layout, one wrong newline guba ang tibuok document
void Ending(int p, player *player){
    char *ends = " ";
    switch (p) {
        case 0:
            printf("\nYou lost all positivity and motivation for school. You stopped going to school and locked yourself in your room. [ENDING 1]");
            break;
        case 1:
            printf("\nYour teachers are getting concerned for your grades. You got sent into a special tutoring program. [ENDING 2]");
            break;
        case 2:
            printf("\nYou got sent to the hospital by the clinic for your concerning malnutrition. [ENDING 3]");
            break;
        case 3:
            if (player->knowledge >= 70) Read("stats.txt", 93, 93);
            else if (player->knowledge >= 50) Read("stats.txt", 94, 94);
            else if (player->knowledge >= 30) Read("stats.txt", 95, 95);
            else if (player->knowledge < 30) Read("stats.txt", 96, 96);

            if (player->happiness >= 70) Read("stats.txt", 98, 98);
            else if (player->happiness >= 50) Read("stats.txt", 99, 99);
            else if (player->happiness >= 30) Read("stats.txt", 100, 100);
            else if (player->happiness < 30) Read("stats.txt", 101, 101);

            break;
    }

    debug(player);
    printf("\nEnter any key to exit.\n>> ");
    scanf("%s", ends);
    exit(0);
}

//checks if the event occurs
//originally I wanted random events to occur, pero nahh samot ka gubot
int EventCheck(int p){
    checkCount = 1;
    int prob = rand() % 100 + 1;
    if (prob < p){
        return 1;
    }
    else return 0;
}

 
// one of the beefiest functions. Diri ang checks and stops sa game
void Update(player *player){
    //clock update

    if (player->energy <= 0){
        //player passes out
        printf("\nYou passed out.");
        hour[0] = 6;
        hour[1] = 0;
        day++;
        location = 1;
        player->energy = 75;
        gameloop(player);
        return;
    }

//time update
    if (hour[1] >= 60){
        hour[0]++;
        hour[1] -= 60;
    }
    if (hour[0] >= 24){
        day++;
        hour[0] -= 24;
        gameloop(player);
        return;
    }

//different endings
    player->hunger += 3;
    
    if (player->happiness <= 0){
    	Ending(0, player);
    }
    
    if (player->knowledge <= 0){
    	Ending(1, player);
    }
    
    if (day >= 7) Ending(3, player);

    if (player->hunger > 100){
        Ending(2, player);
    }

    //check if late ka sa school; schooltime is 9:00 to 18:00 IF weekday
    if (location != 2 && hour[0] >= 9 && hour[0] < 18 && !isWeekend){
        printf("You're late for class. Go to school now.\n");
        player->knowledge--;
        player->happiness--;
    }

    Decision(player);	// this is what I mean about way hunong nga rabbit hole on calling functions
			// last minute nako nakarealize nga ma optimize ni pero I GUESS nga negligible
			// ang impact niya sa performance
}

// the meat sa file manipulation. I print niya ang given range of lines sa given filename
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

// pili siya ug event from events.txt and gets the comma separated values para sa ila properties per choice
rand_event RandEventBuild(){
    int choose = rand() % 10;
    rand_event rand;
    int line = 1 + choose * 17;
    rand.line = line;
    
    //get choices
    FILE *fptr = fopen("events.txt", "r");
    if (fptr == NULL){
        perror("ERROR RETURNING FILE");
    }
    char buff[1000];
    char *pars;
    int current = 1;
    //debug();
    int i = 0;

    while(fgets(buff, 1000, fptr)){
    //debug();

        if (current >= line + 7 && current <= line + 10){
            //debug();
            //printf("%s\n", buff);
            pars = strtok(buff, ",");
            int j = 0;
            while (pars != NULL) {
                //printf("%s ", pars);
                int a = atoi(pars);
                //printf("%i ", a);
                rand.choice[i][j] = a;
                pars = strtok (NULL, ",");
                j++;
            }
            //printf("\n");
            i++;
        }
        if (current > line + 10) break;
        current++;
    }

    fclose(fptr);

    return rand;
}

/*
I don't like the player to have a numerical value sa ila
display kay mura silag ma influence sa pagkita ug high or
low value to balance it out. Para naa puy vision ang player,
naghatag ko ug stats nga mu update depende sa usa ka range
*/
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

// chonky boi, I decided nga i usa ang pag choose sa actions
// sleep, play, and game para ma usa ang ilahang calculations
void Calculate(player *player, int action){
    //delta varables
    statVect base = {0, 0, 0};
    statVect mod = {0, 2, 1};
	
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
                rewind(stdin);
                fflush(stdin);
                printf("\nEnter hours of studying (1-5)\n>> ");
                fflush(stdout);
                scanf("%i", &studyTime);
                if (studyTime > 5 || studyTime <= 0){
                    printf("Invalid Study Time, enter number from 1-5.");
                    goto studySet;
                }
            studyCount++;
            player->energy -= base.energy * studyTime;
            player->knowledge += base.knowledge * studyTime;
            player->happiness -= (base.happiness + studyCount) + studyTime;
            player->hunger += (studyTime - 1) * 3;
            hour[0] += studyTime;
            if (studyCount >= 3) printf("You feel burnt out by the consecutive studying sessions.\n");
            Update(player);
            break;

        case 2:
            //play games
            if (location == 2) base.knowledge -= 2;
            if ((rand() % 20 + 1) >= 5){
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
		//immune ka sa losing happiness IF naa ka sa mall
                if (location != 3) base.happiness = -1 * (abs(base.happiness + 1 - loseCount) / 2);
            }
            player->energy -= base.energy;
            player->happiness += base.happiness;
            player->knowledge -= base.knowledge;
            hour[1] += 15;
            studyCount = 0;
            Update(player);
            break;

        case 3:
            //sleep
            if (location == 3) printf("You can't sleep in the mall.");
            else if (location == 1 && hour[0] >= 21){
                player->energy += base.energy + abs(hour[0] - 18) * 10;
                printf("\nSleeping through the night.\n");
                hour[0] += 24 - hour[0] + 6;
                hour[1] = 0;
		Update(player);
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
    Read ("art.txt", 1, 9);
    printf ("\n           %i:%02d\n\n", hour[0], hour[1]);
    Read ("art.txt", 11, 19);
    printf("\nYou check the watch. It is %i:%02d.\n", hour[0], hour[1]);

    if (hour[0] >= 21) printf("It is past your bedtime.\n");
    else if (hour[0] >= 18) printf("The sun starts to set. You should be at home.\n");
    else if (hour[0] >= 12) printf("The heat of the sun shines through the windows.\n");
    else if (hour[0] >= 9) printf("It's time to attend school.\n");
    else if (hour[0] >= 6) printf("The morning breeze flows as you look around you.\n");
    else printf("You wonder what led you to be awake this late.\n");
    Decision(player);
}

// change locations
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

// I wanted the player to only have an event once per day pero naa may hunger
// I also wanted nga naay specific conditions, ma implement ra siya pero that
// will make the program a bit more complex than it should be (and right now
// it's already very complex)
void Talk (player *player){
    if (EventCheck(50)){
        rand_event current_event = RandEventBuild();
        Read("events.txt", current_event.line, current_event.line + 5);
        //printf("%i", current_event.line);
        Dialogue(current_event, player);
    }
    else{
        printf("\nAll of your friends seem to be busy with their own tasks as of the moment.\n");
    }
    Update(player);
}

// this is after the talk nga successful ang probability
void Dialogue (rand_event source, player *player){
    dial: 
        fflush(stdin);
        rewind(stdin);
        printf(">> ");
        fflush(stdout);
        char input[2];
        fgets(input, 2, stdin);
        int i = atoi(input) - 1;
        if (i < 0 || i > 4) goto dial;

    player->hunger -= source.choice[i][0];
    player->energy += source.choice[i][1];
    player->happiness += source.choice[i][2];
    player->knowledge += source.choice[i][3];
    hour[0] += source.choice[i][4];
    hour[1] += source.choice[i][5];

    Read("events.txt", source.line + i + 12, source.line + i + 12);

    Update (player);
}

// the function nga isigeg tawag and eats up the stack
void Decision(player *player){
	
    fflush(stdin);
    printf("\nYou decide on what to do with your time.\n");
    Read("Input.txt", 1, 11);
    printf(" ");

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
    else if (strcmp("DEBUG", input) == 0) debug(player);
    else
    {
        printf("Invalid Input!\n");
        Decision(player);
    }
}
