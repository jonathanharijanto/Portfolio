// HW ASSIGNMENT 2 CS 344 - ADVENTURE GAME
// BY JONATHAN HARIJANTO
// PURPOSE: TO PRACTICE READ AND WRITE A FILE IN C PROGRAMMING LANGUAGE
// DESCRIPTION: A TEXT BASED ADVENTURE GAME THAT USER MUST TRAVEL TO SPECIFIC ROOM(AREA) IN ORDER TO WIN THE GAME. THIS TEXT BASED GAME CREATE 7 DIFFERENT FILES
// WITH 10 DIFFERENT ROOM NAMES, THAT BEING NAMED RANDOMLY. THEN THESE 7 FILES STORED IN A DIRECTORY CALLED "HARIJANJ.ROOMS.<PROCESS ID>". AFTER THAT, EACH OF 
// THESE ROOM WILL HAVE A RANDOM CONNECTIONS TO THE REST OF THE ROOM (3-6) AND THEY BOTH HAVE CONNECTION TO GO BACK AND FORTH FROM FILE TO FILE. EXAMPLE:
// IF ROOM A CAN GO TO ROOM B, THE ROOM B CAN GO BACK TO ROOM A. THIS GAME USE THE CONCEPTS OF "FSEEK" AND "FGETS" TO MATCH USER ANSWER WITH THE FILE IT CONTAINS.
// THIS GAME WILL END BY INFORMING USER THAT HE/SHE ALREADY REACH THE 'END' PLACE AND ALSO TELLING THE NUMBER OF STEPS TAKEN WITH THE NAME OF ROOMS VISITED BY USER.

// CREDITS TO THE HELP OF STACKOVERFLOW, TAs, CLASSMATES(DISCUSSIONBOARD), AND INSTRUCTOR BEN FOR THIS HW 2 ASSIGNMENT. 

// Include list of libraries
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

// Declare a global char pointer (because not using struct in this assignment) 
char *startRoom;
char *endRoom; 

// Function Prototype
void shuffle(char **array, size_t n);


// Code from Stackoverflow answer (threadname: shuffle array in C )
// This function will shuffle the array based on random seed taken from usec time.
// The usage of this is to make easier to assign random names for files & assign connection room names   
void shuffle(char **array, size_t n) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int usec = tv.tv_usec;
	srand48(usec);

	if (n > 1) {
		size_t i;
		for (i = n -1; i > 0; i--) {
			size_t j = (unsigned int) (drand48()*(i+1));
			char * t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}				

// This is where all the code to run the game located. Not using list of functions because want to minimize error.
// Not that efficient because hardcoded all in main() instead of just calling functions in main(). Going to change
// this bad habit in next assignment.


// Process of main function are: 
// 1. Get process id so can be used to name the directory. Use this technique because want to make each directory unique
// 2. Hard-coded list of room names to be assigned as the file name and ROOM_NAME
// 3. Shuffle the array (to get random order) and append the name into files as ROOM_NAME
// 4. Generate random number of to assign which file will get START ROOM , MID ROOMS, and FINAL ROOM
// 5. Generate random number to assign number of connection that each room will have
// 6. Shuffle the room name available to be connected with each other room
// 7. Ask user to enter the name of room he/she wants to visit
// 8. Compare the answer to the names from the avaiable connection that room have
// 9. If it is a match, bring the user to that room, if not print "try again" message (fseek and fgets)
// 10.While doing that, keep on counting the steps taken and saving the name list of rooms visited
// 11.When the user finds the ENDROOM, it will print a "congratulation" message and print the number
//    of steps taken and the list of room names visited.
int main (void) {

	// Get the number of process ID. The reason to do this to make the each directory name unique 
	int pid = getpid();
	// Provide space of array for directory name
	char DIRECTORY_NAME[30];
	sprintf(DIRECTORY_NAME, "harijanj.rooms.%d", pid);
	if (mkdir(DIRECTORY_NAME, 0777)!= 0) {
		fprintf(stderr, "Fail to create directory %s\n", DIRECTORY_NAME);
		exit(1);
	}	
	
	srand(time(NULL));
	
	// Hard coded the ten list of room name to be assigned to 7 files later. 
	// The reason hardcoded manually to minimize error such as seg.fault in declaring name & pointer array
	char *room_name[10];
	room_name[0]="Library";
	room_name[1]="Dixon";
	room_name[2]="Kelley";
	room_name[3]="Weniger";
	room_name[4]="Dearborn";
	room_name[5]="MU";
	room_name[6]="BeaverStore";
	room_name[7]="Chipotle";
	room_name[8]="Subway";
	room_name[9]="Cordley";
 
	// Provide temporary size and pointer array to open a file
	int bufSize = 128;
	char *currentFile = malloc(bufSize);
	int count;
	int i,j;
	int nroom_name = 9;
	
	// Randomize the element in room_name array, when being called the position will not be
	// the same as the hardcoded above. 
	shuffle(room_name,10);
	
	// Loop 7 times (since there are 7 files to assign), to create file and name it randomnly
	// taking from the list of names created earlier.
	for (count = 0; count < 7 ; count++) {
		snprintf(currentFile, bufSize, "%s/%s", DIRECTORY_NAME, room_name[count]);
		// "w+" means open the text file for update. 
		FILE *fp = fopen(currentFile,"w+");
		if (fp != 0) {
			fprintf(fp, "ROOM NAME: %s\n", room_name[count]);
			fclose(fp);
		} 
	}
	
	// Create new pointer array to store all the chosen names for the file
	// The reason it is created to prevent getting mixed with the list of unchosen name for files
	char *new_room_name[7];
	for (count = 0; count < 7; count ++) {
		new_room_name[count] = room_name[count];
	}
 	
	// Determine random start and end rooms
	int counter;
	int start = rand () % 7;
	int finish = rand() % 7;
	// The reason use while to prevent getting same number (from 0-7) with the START ROOM
	while (start == finish) {
		finish = rand() % 7;
	}

	// Store the number of connection that each file going to have
	int connectionNumb;
	char * connection;
	// Represents a counter in 'for' loop
	int index;
		
	// For loop to assign how many connections each file will get.
	// Also assigning the list of name of connection that each file will get
	for (i=0; i < 7; i++){
		// Shuffle the element in the array to make sure completely random
		shuffle(new_room_name, 7);
		snprintf(currentFile, bufSize ,"%s/%s",DIRECTORY_NAME,room_name[i]);
		// Open the file (one by one) and APPEND 'a' instead of 'w' sincce dont want to overwrite
		// the string that already there in each file (room name) 
		FILE *fp = fopen(currentFile,"a");

		if (fp == NULL) {
			perror("Error in opening the file. \n");
		} else {
			// Simple math to make sure that the results will fall between (3-6)
			connectionNumb = rand() % 4 + 3;
			index = 0;
			// Loop that will assign each of the avaiable connection that each file has
			// and give each of that connection a name
			for (j=0; j < connectionNumb; j ++) {
				connection = new_room_name[index];
				// Condition to prevent self loop by assigning the name of the connection
				// with the next element of the array. The reason is to prevent self loop
				// which will ruin the game eventually if self loop to the room itself happens
				if (connection == room_name[i]) {
					index++;
					connection = new_room_name[index];
				}
				// Print the name of the connection if all conditions passed		
				fprintf(fp, "CONNECTION %d: %s\n", j+1, connection);
				index++;
			}
			// Match with the randomize 'start' declared before the 'for' loop  to assign which file
			// gets the START ROOM 	
			if (i == start) {
				fprintf(fp,"ROOM TYPE: START_ROOM \n");
				startRoom = room_name[i]; 
			} else if (i == finish) {
				// Match with randomize 'finish' declared before the 'for' loop to assign which file
				// gets the END ROOM
				fprintf(fp,"ROOM TYPE: END_ROOM \n");
				endRoom = room_name[i];
			} else {
				// If not same with 'finish' or 'start', just assigned the room as MID ROOM 
				fprintf(fp,"ROOM TYPE: MID_ROOM \n");
			}
		}
		fclose(fp);
	}

//	----------------------------------------------------------------------------

//	HIDDEN CHEAT CODE! (UNCOMMENT THESE LINES TO USE THE CHEAT) 
	
//	printf("CHEAT CODE ACTIVATED!\n", NULL );	
	char * userLocation = startRoom;
//	printf("START ROOM SUPPOSED TO BE ----> %s",userLocation);
	char * endLocation = endRoom;
//	printf("\nGO TO ----> %s <---- TO WIN THIS GAME!",endLocation);

//	-----------------------------------------------------------------------------


	int k;

	// Total number of steps that a player has take
	int totalStep= 0;

	// Create an array of 8 elements each of which is an array of 20 chars
	//
	char visitedRoom[8][20]; //store the name of rooms visited
	char contents[8][20];

	int setFlag;
	// Iterate throughout the file to scane each character in the file	
	int scanChar; 
	// Count how many lines per file contain.
	// The reason is to grab the list of CONNECTIONS each file
	int countLine;
	// Store the input of user room choices  
	char userAnswer[20]; 

	// A 'giant' (main) loop that takes part during the user interface. This while loop
	// will basically making sure that the current user location is not equal to the 
	// designated end room. 
	// If not equal yet, then this file will keep on opening file, read from it, comparing
	// the string and close, then open other file and do the same thing all over again
	// untill the current user location is equal to the final room (user wins). 
	while (!(strcmp(userLocation, endLocation)) == 0) {
		snprintf(currentFile,bufSize,"%s/%s",DIRECTORY_NAME,userLocation);
		// Open the file and "READ". This command will not append or write anything
		// It just comparing each designated string with the user input 
		FILE *fp = fopen(currentFile,"r");
		countLine = 0;
		if (fp) {
			// Loop to calculate how many lines avaiable at that file. Each file will
			// automatically have two lines because of ROOMNAME and ROOMTYPE, the rest
			// are the CONNECTION #. Thus the reason want to calculate the lines 
			// avaiable is to know how many connections that each room have.
			while (( scanChar = getc(fp)) != EOF) {
				if (scanChar == '\n') {
					countLine++;	
				}	
			}
		}
		// The reason use ( - 2) because dont want to count the line of ROOMNAME and ROOMTYPE
		countLine = countLine - 2;
		// Temporary storage for ROOM_NAME
		char tempStr[20];
		// "Seek" through the file to get the name of the room. The reason put '11' because 
		// the word 'ROOM NAME: ' takes 11 char. So it is used as starting point of 'seeking' 
	 	fseek(fp, 11, SEEK_SET);
		// Grab the name of the file and store it in temporary array
		fgets(tempStr, 20, fp);
		// Count the length of the element in array
		int len = strlen(tempStr);
		// The reason to do this to remove new line (if there is) from fgets
		if (tempStr[len-1] == '\n'){
			tempStr[len-1] = '\0';
		}
		// Copy the value from temporary array to 'content' 
		strcpy(contents[0], tempStr);

		//-------------Debugging purposes------------------------
		//printf("\nCURRENT ROOM NAME: %s", contents[0]);	

		for(k = 1; k <= countLine; k++) {
			// Seek through the file to get the name of connections. The reason put "14" because
			// the word "CONNECTION #:" takes 13 char. So starting point starts from "14"
			fseek(fp,14,SEEK_CUR);
			// Grab the name of the connection name and store in temp array	
			fgets(tempStr,20,fp);
			// Count the length of element in array
			int len = strlen(tempStr);
			// The reason to do this is to remove new line if any from fgets
			if (tempStr[len-1] == '\n'){
				tempStr[len-1] = '\0';
			}
			strcpy(contents[k], tempStr);
		}
		//------------------Debugging Purposes-------------------------------
		/*
		for (k = 1; k <= countLine; k++) {
			printf("\nLIST OF CONNECTIONS FOR THIS ROOM: %s", contents[k]);
		}	
		*/	

		// Initialize flag and set it to flase first
		// The reason use flag is to differentiate between valid input from user or no
		// If input not valid then print an error message 
		setFlag = 0;

		// Loop that will print the user current location and list of available 
		// locations to be visited
		while(setFlag == 0) {
			printf("\nCURRENT LOCATION: %s\n", contents[0]); 
			printf("POSSBILE CONNECTIONS: ");
			for (k = 1; k <= countLine; k++) {
				if (k == countLine) {
					printf("%s.\n", contents[k]);
				} else {
					printf("%s, ", contents[k]);
				}
			}
			// Read input from user keyboard and pause until input is received	 		
			printf("WHERE TO?>");
			scanf("%s", userAnswer);
			// Loop that will compare user answer with the list of avaiable room
			// If it is a match, then visit that room (open that file)
			for(k = 1; k <= countLine; k++) {
				if (strcmp(userAnswer, contents[k]) == 0) {
					setFlag = 1;
					userLocation = userAnswer;
				}
			}
			// If user input is not valid (no similar to what being written in options)
			// It will print error message and ask user to re-input	
			if (setFlag != 1) {
				printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN. \n\n");
			}
		}
		printf("\n");
		strcpy(visitedRoom[totalStep], userLocation);
		// Increment the total steps for each input given, except invalid input
		totalStep = totalStep + 1;
		fclose(fp);
	} 		
		
	printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEP(S). YOUR PATH TO VICTORY WAS:\n", totalStep);
	// Print all the elements in the array that keeps recording the input from user 
	for (k = 0; k < totalStep; k ++) {
		printf("%s\n", visitedRoom[k]);
	}		

	// Exit status that saying the program worked fine 
	return 0;
}











