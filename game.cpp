//============================================================================
// Name        : game.cpp
// Author      : Chiibu Abdul-Kudus
//============================================================================


// PLEASE COMPILE AND RUN THIS FROM A WINDOWS COMMAND PROMPT OR CODEBLOCKS. I USED FUNCTIONS RESERVED FOR WINDOWS AND THE CLEAR FUNCTION DOES NOT
// WORK ON ECLIPSE IDE. THANKS

#include <iostream>	// for i/o
#include <windows.h>// for Sleep() and clear functions
#include <cstdlib> 	//
#include <string>	// for strings
#include <fstream>	// for file handling

using namespace std;

typedef struct {	// struct declaration
	int level[6];	// levels go from 0 to 5
}Tower;	// Tower now like a new data type

Tower towers[3];	// an array of 3 instances of tower. one for each tower

string username;	// STORE USERNAME
int move_counter;	// COUNT MOVES
string top_names[4][5];// STORE NAMES OF PEOPLE IN LEADERBOARD
int top_scores[4][5]={0};// STORE MOVES MADE BY PEOPLE IN LEADERBOARD

// CONST CHAR ARRAY  to hold names of leaderboard files for the different game levels
const char * ld[8]={"leaderboard.dat","leaderboard2.dat","leaderboard3.dat","leaderboard4.dat","leaderboard5.dat","leaderboard6.dat","leaderboard7.dat","leaderboard8.dat"};

//START OF FUNCTION PROTOTYPES...

void gameMenu();
void newGame(Tower towers[]);
void gameRules();
void leaderboard();
void printTowers(Tower towers[]);
void getLeaderBoard();
void writeToLeaderBoard();
void sort_lb();
void replace(int i);
void flip(int i);

// END of function prototypes

int main() {							// MAIN FUNCTION
	getLeaderBoard();	// RETRIEVE ALL DATA IN FILES AND STORE THEM IN LOCAL ARRAYS
	system("cls");	// CLEAR CONSOLE
	gameMenu();	// CALL MAIN MENU OF GAME

	return 0;	// TERMINATE PROGRAM
}
							//END OF MAIN FUNCTION

void gameMenu(){
	system("cls");	// CLEAR
	cout <<"\n\n\n\n\n\t\t\t\t\t\t**********************************" << endl;	// NAME TAG
	cout <<"\n\t\t\t\t\t\tWelcome to the Tower of Hanoi Game" << endl;
	cout <<"\n\t\t\t\t\t\t\tBy Chiibu Abdul-Kudus" << endl;
	cout <<"\n\t\t\t\t\t\t**********************************" << endl;
	int menu_choice;	// user choice of menu item
	cout<<"\t\t\t\t\t\t\t1. New Game\n\t\t\t\t\t\t\t2. Read Game Rules\n\t\t\t\t\t\t\t3. Leaderboard\n\t\t\t\t\t\t\t4. Exit\n\t\t\t\t\t\t\tEnter your choice: ";	// print menu items
	while(!(cin>>menu_choice) || menu_choice<1 || menu_choice>4){	// input and validation
		cout<<"\t\t\t\t\t\tWrong input. Try again: ";	// prompt
		cin.clear();	// clear fail bit
		while(cin.get()!='\n'){}	// clear input buffer
	}

	switch(menu_choice){	// switch user choice
			case 1:
				newGame(towers);	// call new game and pass the towers to it
				break;
			case 2:
				gameRules();	// display game rules by it's function
				break;
			case 3:
				leaderboard();	// leaderboard function to display leaderboard
				break;
			case 4:
				system("cls");
				exit(EXIT_SUCCESS);
				break;	// break out and exit if user chooses to
			default:
				cout<<"\t\t\t\t\t\tI don't understand you!"<<endl;	// won't come to this because of validation but eehhh!
				break;
			}
	system("cls");	// clear console
}
void newGame(Tower towers[]){	// new game fucntion
	system("cls");
	cout<<"Enter number of disks per tower(3-6): ";	// ask number of disks per tower...the higher the tougher it is
	int disk_per_tower;
	bool fail;
	move_counter=0;
	while(!(cin>> disk_per_tower) || disk_per_tower <3 || disk_per_tower > 6){	// input and validation
		cin.clear();
		while(getchar()!='\n'){}
		cout<<"Enter a number between 3 and 6: ";
	}
	cout<<"New Game with "<<disk_per_tower<<" disks..."<<endl;	// prompt
	Sleep(1000);
	system("cls");
	int i,j;
	int premature=0;	// used to check if user quits prematurely
	for(i=0;i<3;i++){	// for loop to fill all levels of towers with 0s. This means no disks ...initialization
		for(j=0;j<6;j++){
			towers[i].level[j]=0;
		}
	}
	for(i=0;i<disk_per_tower;i++){	// fill first tower with as many disks as the user chooses. disk radii range from 1 to 6.
		towers[0].level[i]=(6-i);
	}
	int check[6];	// array to hold initial content of first tower to be compared with for winning
	for(i=0;i<6;i++){	// for loop to assign tower[0] to check[]
		check[i]=towers[0].level[i];
	}
	int from,to;	// int variables to hold moves
	bool game_on=true;	// check if game play should keep running
	while(game_on==true){
		fail=false;	// check if move is invalid
		system("cls");
		cout<<"\n\n"<<endl;
		printTowers(towers);	// print towers
		cout<<"\t\t\tTotal moves made: "<<move_counter<<endl;	// print number of moves made
		cout<<endl;
		cout<<"Move disk from ( enter 0 to quit ): ";	// print output
		while(!(cin>>from) || from > 3 || from < 0){	// input to from and validate it
			cin.clear();
			while(cin.get()!='\n'){}
			cout<<"Wrong input. Enter either 0, 1, 2 or 3: ";
		}
		if(from==0){	// if user enters 0, quit
			premature=1;	// let program know it quit prematurely
			break;
		}

		cout<<"To ( enter 0 to quit ): ";
		while(!(cin>>to)||to>3||to<0||to==from){	// input to "to" variable and validate it
			cin.clear();
			while(cin.get()!='\n'){}
			if(to==from){
				cout<<"You may not move from a tower to same tower. Enter another tower: "<<endl;
			}
			else{
				cout<<"Wrong input. Enter either 0, 1, 2 or 3: ";
			}
		}
		if(to==0){	// quit if input is 0
			premature=1;	// premature quitting
			break;
		}

		int i=5;
		int j;
		int disk_temp=0;
		while(i>=0 && disk_temp==0){	// loop through to see where the first disk is from the tower you want to pick from
			if(towers[from-1].level[i]>0){
				disk_temp=towers[from-1].level[i];
				j=i;
			}
			i--;
		}
		if(disk_temp==0){ // if no disk was found there
			cout<<"There is no disk from your initial tower. Pick a tower with a disk already in it."<<endl;
			Sleep(700);
			fail=true;	// set fail to false so it can go back without doing the rest of the game
		}
		if(fail==false){	// if the preceeding part was successful...
			for(i=0;i<6;i++){	// loop through to place the disk on the first free space on the "to" tower
				if(towers[to-1].level[i]==0){
					if(i==0){	// successfully placed
						towers[to-1].level[i]=disk_temp;
						towers[from-1].level[j]=0;
						move_counter++;
						break;
					}
					else{
						if(towers[to-1].level[i-1]<disk_temp){	// if you try to place on a disk smaller than the disk being moved
							cout<<"You cannot place a bigger disk on a smaller one. Try again..."<<endl;
							Sleep(2000);
						}
						else{	// successfully placed
							towers[to-1].level[i]=disk_temp;
							towers[from-1].level[j]=0;	// always reset the point from which the disk was moved to 0 so it signifies no disk exists there anymore
							move_counter++;	// increment move counter
						}
						break;
					}
				}
			}
		}

		game_on=false;	// temporally set game_on to false. You will check to see if it really is in the next loop below

		for(i=0;i<6;i++){	// check through to see if your last tower has disks matching how you started on the first tower
			if(towers[2].level[i]!=check[i]){
				game_on=true;	// if any of them fails to match, the game is still on
				break;	// break and stop checking
			}
		}
	}
if(premature==0){	// if you do not quit prematurely. You must win to get to this part of the program unless you quit prematurely then it will skip it.
	system("cls");
	cout<<"\n\n"<<endl;
	printTowers(towers);	// print the tower
	cout<<"\t\t\tTotal moves made: "<<move_counter<<endl;	// display moves made
	Sleep(1000);
	system("cls");
	for(i=0;i<2;i++){	// nice way of saying "You win!" ;)
		cout<<"\n\n\n\n\n\t\t\t\t\t\tYOU WIN !!!"<<endl;
		Sleep(700);
		system("cls");
		Sleep(500);
	}
	switch(disk_per_tower){
	case 3:						// CHECK IF PLAYER WON WITH THE LEAST POSSIBLE MOVES
		if(move_counter==7){
			cout<<"You made a perfect score!"<<endl;
			Sleep(600);
		}
		break;
	case 4:
		if(move_counter==15){
			cout<<"You made a perfect score!"<<endl;
			Sleep(600);
		}
		break;
	case 5:
		if(move_counter==31){
			cout<<"You made a perfect score!"<<endl;
			Sleep(600);
		}
		break;
	case 6:
		if(move_counter==63){
			cout<<"You made a perfect score!"<<endl;
			Sleep(600);
		}
		break;
	}
	if(move_counter<=top_scores[disk_per_tower-3][4] || top_scores[disk_per_tower-3][4]==0){	// if you used less moves than those in the leaderboard or that part is occupied by 0 ( 0 used to show empty space )
		cout<<"You have made the leaderboard!"<<endl;
		cout<<"Enter a nickname: ";
		cin>>username;
		cin.clear();
		while(cin.get()!='\n'){}
		replace(disk_per_tower);	// place on leaderboard
		writeToLeaderBoard();		// write it to the external data files
		leaderboard();				// call leaderboard so they can see their stance
	}
	cout<<endl;
}
else{	// if they quit prematurely
	system("cls");
	cout<<"Sorry to see you leave!"<<endl;	// prompt
	Sleep(1000);
}
	gameMenu();	// call game menu at the end
}



void gameRules(){	// PRINT OUT GAME RULES
	system("cls");
	cout<<endl;
	cout<<"\t\t\t\t\t\t\tGAME RULES: \n\t\t\t\t\t\t\t-----------"<<endl;
	cout<<"\t\t\t\tIn this game, you have a number of disks stacked on a pole.\n\t\t\t\tYour goal is to transfer these disks to the third pole stacked in same order as initially.\n\t\t\t\tYou cannot place a bigger disk on a smaller disk! You should try to win in as few moves a possible!\n\n";
	cout<<"\t\t\t\t";
	system("pause");	// WAIT FOR INPUT
	system("cls");
	gameMenu();	// CALL GAME MENU
}


void leaderboard(){
	system("cls");
	cout<<endl;
	cout<<"\t\t\t\t\t\t\tLEADERBOARD:\n\t\t\t\t\t\t\t---------------"<<endl;
	int i,j;
	for(i=3;i<=6;i++){																// loop through arrays and print leaderboard
		cout<<"\t\t\t\t\t\t\t"<<i<<" disks:\n\t\t\t\t\t\t\t-----------\n";
		for(j=0;j<5;j++){
			if(top_scores[i-3][j]!=0){
				cout<<"\t\t\t\t\t\t\t"<<top_names[i-3][j]<<" : "<<top_scores[i-3][j];	// print name and moves
				if((i==3 && top_scores[i-3][j]==7) || (i==4 && top_scores[i-3][j]==15) || (i==5 && top_scores[i-3][j]==31) || (i==6 && top_scores[i-3][j]==63)){// if least possible moves
					cout<<" (Perfect score!) ";
				}
		}
			cout<<endl;
		}
		cout<<endl;
	}
	cout<<"\n\n";
	cout<<"\t\t\t\t\t\t\t";system("pause");	// wait for keyboard input
	system("cls");
	gameMenu();
}
void printTowers(Tower towers[]){	// FUNCTION TO PRINT TOWERS AND THE DISKS!
	int i,j,temp;
	for(i=0;i<=6;i++){	// loop through 6 lines. Printing is done from top to bottom
		for(j=0;j<79;j++){	// I require a total of 79 columns to print the three towers
			if(j<27){	//Start of tower 1
				if(j==12){
					if(i==6){
						cout<<"1";	// if in the middle of the tower at last line, print label of tower
					}
					else
						cout<<"|";	// else if not at the last line but in the middle, print the bar
				}
				else{	// anywhere else...
					if(towers[0].level[5-i]>0){	// if a disk exist in that level of the bar
						temp=towers[0].level[5-i];	// set temp to the radius of that disk
						temp*=2;	// i multiply by two so the difference between the disks is readily visible
						if(j<12 && 12-(temp+j)>0){	// whilst not in the area occupied by disk on one side print spaces
							cout<<" ";
						}

						else if(j>12 && (j-12)>temp){	// print spaces on other side of disk
							cout<<" ";
						}
						else{
							cout<<"=";	// if in the location of a disk, print =. To represent a fraction of the thickness of the disk
						}
					}
					else{
						cout<<" ";	// print space anywhere else
					}
				}
			}	// End of tower1
// THE ABOVE IS USED TO PRINT TOWER 2 AS WELL
			else if(j>=27 && j<52){
				if(j==39){
					if(i==6){
						cout<<"2";
					}
					else
						cout<<"|";
				}
				else{
					if(towers[1].level[5-i]>0){
						temp=towers[1].level[5-i];
						temp*=2;
						if(j<39 && 39-(temp+j)>0){
							cout<<" ";
						}

						else if(j>39 && (j-39)>temp){
							cout<<" ";
						}
						else{
							if(i==6){	// BECAUSE I USE 5-i, AT i=6, I GET A NEGATIVE INDEX. THIS MAKES IT PRINT = IN THE ROW MEANT FOR LABELS FOR DISKS EQUAL TO 6. THIS IF HERE FIXES IT
								cout<<" ";	// THIS PROBLEM ONLY PERSISTS IN THE 2ND TOWER
							}

							else{
								cout<<"=";
							}
						}
					}
					else{
						cout<<" ";
					}
				}
			}
			else{
				// SAME TECHNIQUE USED TO PRINT TOWER 3

				if(j==66){ // START OF TOWER 3
					if(i==6){
						cout<<"3";
					}
					else
						cout<<"|";
				}
				else{
					if(towers[2].level[5-i]>0){
						temp=towers[2].level[5-i];
						temp*=2;
						if(j<66 && 66-(temp+j)>0){
							cout<<" ";
						}

						else if(j>66 && (j-66)>temp){
							cout<<" ";
						}
						else{
							cout<<"=";
						}
					}
					else{
						cout<<" ";
					}
				}
			}
		}
		temp=0;	// RESET TEMP
		cout<<endl;	// END LINE AT END OF EACH ROW!
	}
	cout<<"\n"<<endl;	// SPACE AFTER PRINTING ALL THE TOWERS COMPELETELY.
}
void getLeaderBoard(){	// WHEN GAME STARTS, LOAD LEADERBOARD FILES TO MULTIDIMENSIONAL ARRAYS FOR USAGE IN THE PROGRAM
	int j,count;
	fstream fs;
for(count=0;count<4;count++){	// reads in the names
	fs.open(ld[count], fstream::in);	// open for reading
			for(j=0;j<5;j++)
			{
				fs >> top_names[count][j]; // read to location in array
			}
	fs.close();	// close file
}
for(count=4;count<8;count++){	// reads in the top scores. I make them correspond to each other. I don't know how to make a dictionary kind of thing where you assign a data value to a name :(
	fs.open(ld[count],fstream::in);
			for(j=0;j<5;j++){
				fs >> top_scores[count-4][j];
			}
	fs.close();
}
sort_lb();
}
void writeToLeaderBoard(){ 		// FUNCTION TO WRITE LEADERBOARD TO EXTERNAL FILES
	int j,count;
	fstream fs;
for(count=0;count<4;count++){	// LOOP THROUGH FIRST 4 FILES
	for(j=0;j<5;j++){
		if(j==0){
			fs.open(ld[count],fstream::out);	// IF FIRST TIME, OPEN FOR OUT WHICH MEANS IT CLEARS EVERYTHING ALREADY THERE. I utilize
												// an array of file names(ld[]) so I can loop through it.
												// I don't have mastery over file handling so I use multiple files so it's easy for me.
			fs<<top_names[count][j];			// WRITE FIRST NAME THERE
			fs.close();
		}
		else{
			fs.open(ld[count],fstream::app);	// SUBSEQUENTLY OPEN IT FOR APPENDING SO YOU DON'T CLEAR EXISTING DATA
			fs<<" "<<top_names[count][j];		// WRITE REST OF NAMES
			fs.close();							// CLOSE FILE
		}
	}
}

for(count=4;count<8;count++){					// LOOP THROUGH LAST FOUR FILES
	for(j=0;j<5;j++){
		if(j==0){
			fs.open(ld[count],fstream::out);	// OPEN FIRST FOR OUT
			fs<<top_scores[count-4][j];			// WRITE FIRST TOP SCORE
			fs.close();
		}
		else{
			fs.open(ld[count],fstream::app);	// NOW OPEN FOR APPENDING
			fs<<" "<<top_scores[count-4][j];	// APPEND REST OF TOP SCORES
			fs.close();
		}
	}
}
	sort_lb();
}
void replace(int i)
{	// replace a user in the leader board at the end ( one with largest moves )
	top_scores[i-3][4]=move_counter;
	top_names[i-3][4]=username;
	flip(i);	// used to place newest player in leaderboard above all those already in leaderboard with same number of moves.
	sort_lb();	// call sort function
}
void sort_lb(){	// function to sort leaderboard using bubble sort algorithm.
	int i,j,k,temp;
	string stemp;
	for(i=0;i<4;i++){
		for (j=0;j<4;j++){
			for(k=0;k<5-j-1;k++){
				if((top_scores[i][k]>=top_scores[i][k+1] && top_scores[i][k+1]!=0) || (top_scores[i][k]==0 && top_scores[i][k+1]!=0)){	// sort using top_scores. Place 0s at the end
					temp=top_scores[i][k];
					top_scores[i][k]=top_scores[i][k+1];
					top_scores[i][k+1]=temp;
					stemp=top_names[i][k];				// if need to flip a score, go ahead and flip corresponding names too
					top_names[i][k]=top_names[i][k+1];
					top_names[i][k+1]=stemp;
				}
			}
		}
	}
}
void flip(int i)
{
	// Used to flip new user to position of existing users with same scores. This ensures new users stay longer on leaderboard
	bool flipon=true;
	int j=4;
	int temp;
	string stemp;
	do{
		if(top_scores[i-3][j]==top_scores[i-3][j-1] || top_scores[i-3][j-1]==0){
			// switch scores
			temp=top_scores[i-3][j];
			top_scores[i-3][j]=top_scores[i-3][j-1];
			top_scores[i-3][j-1]=temp;
			// switch names
			stemp=top_names[i-3][j];
			top_names[i-3][j]=top_names[i-3][j-1];
			top_names[i-3][j-1]=stemp;
			j--;
		}
		else{
			flipon=false;
		}
	}while(flipon==true && j>=1);
}
