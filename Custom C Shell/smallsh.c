// smallsh created by Jonathan Harijanto
// smallsh is a custom C shell that can implement simple command: "command [arg1 arg2 ...] [< input_file] [> output_file] [&]"
// where items in square brackets are option. It is also able to support three built in commands: exit, cd and status.
// The main purpose given this assignment is to test students' ability to read&open file, also to differentiate process between
// background and foreground.

// Credits mainly to Ben's slide, TAs, gnu.c, stackoverflow and stephan-brennan.com for becoming part of resources in this HW.

#include <stdio.h>            
#include <stdlib.h>          
#include <string.h>	    		
#include <unistd.h>         
#include <sys/wait.h>         
#include <sys/types.h>       
#include <sys/stat.h>         
#include <fcntl.h>          
#include <signal.h>
#include <errno.h>
#include <ctype.h>

// Constants
#define MAX_LENGTH 100
#define MAX_TOKENS 20

// Function Prototype
void* readsplitCommand(char **tokens);
void *readsplitCommand ( char *tokens[]);
int launch_command(char **arg,int in, int out);
int launch_backgroud(char **arg, int in, int out, int bg);

// Global variable to keep track of the current exit value to be used for "status"
int exitVal = 0;

// Function that accept signal number corresponding to the signal that needs to be handle
// The reason: want to catch signal from ^C during sleep or sleep &.
// Save the value of the signal too for the error message "terminated by signal X" 
void sig_handler(int signum) {
	if (signum == SIGINT) {
		printf(" : Terminated by signal %d \n", signum);
		exitVal = signum;
	}	
}

// Function that accepts line input from user and parses/split the line into tokens
// A function that do two things directly instead of 2 separates function because
// reduce the possible of returning and accepting the wrong value between functions
// The reason: parse the line in order to identify what kind of command the user really want.
// Impossible to execute user command without knowing what's being inputted if not parse.
void* readsplitCommand(char *tokens[]) 
{
	int bytes_read;
	int i=0;
	int token=0;
	size_t bufsize = MAX_LENGTH + 2; // Allocate size & accounts for end of string '\0' char
	char *commandInput; // Store the line read from getline

	// Allocate spaces for a MAX_LENGTH character line
	commandInput = (char *)malloc(bufsize + 1);

	if(commandInput == NULL) 
		return NULL;
	
	// Get the input line given from the user
	bytes_read = getline (&commandInput, &bufsize, stdin);
   
	// Condition for getline() failure
	if(bytes_read == -1) /*If getline() failed*/
	{
		free(commandInput); // Free up the memory to prevent memory leak 
		fprintf(stderr, "getline() failed\n");
		return NULL;
	}
	// Condition if the input given is too long	
	if(bytes_read > MAX_LENGTH+1) 
	{
		free(commandInput); // Free up the memory to prevent memory leak
		fprintf(stderr, "Too many characters in command\n");
		return NULL;
	}
   
	do 
	{
		// Traverse to know how many space and tab characters in the input 
		while(commandInput[i]==' ' || commandInput[i]=='\t') 
		{
			commandInput[i]='\0';
			i++;
		}
		
		// Condition when end of input is reached
		if(commandInput[i]=='\n')
		{ 
			// Condition when user input too many arguments, thus too many tokens
			if(token > MAX_TOKENS) 
			{
				free(commandInput); // Free up the memory to prevent memory leak
				fprintf(stderr, "Too many arguments\n");
				return NULL;
			}
		
			// replace '\n' with '\0' instead (end of string character) for execvp process 
			commandInput[i]='\0';
			tokens[token]=NULL;
			// return the pointer to the malloced memory so call can free it
			return commandInput;
		}
	  
		tokens[token]=&commandInput[i];
		token++;
		i++;
		// Grab rest of the characters in the token, isgraph() is for determines whether character is printable
		while(isgraph(commandInput[i]) && commandInput[i] != '\n')
		{
			i++;
		}
	}while(1);     
}


// Main function where all the input entered, received and processed.
// Most of the process done in individual functions, main just calling each function.
// main() mostly declaring list of variables and creating "sigaction" with its signal.
// Sigaction used to change the action taken by process when receiving specific signal.
// Reason: This hw problem (including foreground and background) is kind of abstract process and indication need
// indication when something is not right, or something is done. Thus, the only thing is to rely on signal.
// main() used while (1) which basically infinitely loop that saying 'as long process working fine, shell
// going to keep asking for another prompt which is (: )"
// While loop can only be break when user type "exit", which is return 0    
int main(){
	char *args[20];
	char *inputString;
        int status,count,inputIndex,outputIndex,backgroundIndex;
	int dead; // Variable to store the value of waitpid() & indicate whether child dead or not
  
	// Use sigaction to help examine and change a signal action	
	struct sigaction act;
	struct sigaction new_act;

	// Declare variable under "sigset_t" data type to represent signal set
	sigset_t newSet, origSet;
  	sigset_t set;
	// Initializes or reset the signal set pointed by the set (newSet)
  	sigfillset( &newSet );

	// Help to indentifies action to be associated with specified signal (sig_handler, in this case)  
	new_act.sa_handler = sig_handler;
	// Provide addtional instructions flag, set to zero instead since not planning to set any flag
  	new_act.sa_flags = 0;
	// Indentifies set of signals before signal catching is invoked
  	new_act.sa_mask = set;

	//Loop forever because (1)
	while(1) {
		// Loop to prevent from missing possible dead children during the process
		while ((dead=waitpid(-1,&status,WNOHANG)) > 0){
			// If exit normally without interruption
			if (WIFEXITED(status)){
				printf("Background pid %d is done. Exit Value is %d\n",dead,status);
				exitVal = status;
			}
			// If exit caused by termination, ^C is one of the possible
			else if (WIFSIGNALED(status)){
				printf("Background pid %d is done. Terminated by signal %d\n",dead,status);
				exitVal = status;
			}
		}

		fprintf (stdout, ": ");
		sigaction(SIGINT, &new_act, NULL);

		// Read and extract user input, store it to inputString for later to be free()
		inputString = readsplitCommand(args);

		count = 0;
        	inputIndex = 0; // Count how many input user entered
        	outputIndex = 0; // Count how many output entered
        	backgroundIndex = 0; // Check whether input for background running (1 means for bg running)

		// If blank line, ignored & ask to input next command 
		if(args[0] == NULL) {
			exitVal=0; 
			continue;
		}
		// If comment line, ignored & ask to input next command
		else if (strcmp (args[0],"#") == 0){
			exitVal=0;
			continue;
		}
		// Builtin #1: exit
		// If exit, break the loop and exit the smallsh shell
		else if(strcmp(args[0], "exit") == 0) {
                       break;
			 //return 0;
                }
		// Builtin #2: cd
		else if(strcmp(args[0], "cd") == 0){
			// If no argument, navigate to home dir	
			if(args[1] == NULL){
				chdir(getenv("HOME"));
				exitVal=0;	
			}
			// If there is argument, "go" to that directory
			else{
                        	chdir(args[1]);
				exitVal=0;
			}
		}
		// Builtin #3: status
		// Prints last foreground exit status or terminating signal
		else if(strcmp(args[0],"status") == 0) {
			if (exitVal == 0){
				printf("Exit value %d\n",exitVal);
			}
			else if (exitVal == 1) {
				printf("Exit value %d\n",exitVal);
			}
			else {
				printf("Terminated by signal %d\n",exitVal);
			}
		}
		// Other condition if user type something but not the build-in 
		else if ( args [0] != NULL ){
			// Traverse the argument word by word 
		        while ( args[count] != NULL ){
				// If it is command for take input
                		if ( strcmp(args[count], "<") == 0 ){
                        		inputIndex = count;
                        		args[count] = NULL;
                		}
				// If it is command for output	
                		else if (strcmp(args[count], ">") == 0 ){
                        		outputIndex = count ;
                        		args[count] = NULL;
                		}
				// If it is command for background running		
                		else if (strcmp(args[count], "&") == 0 ){
                        		backgroundIndex = count;
                        		args[count] = NULL;
                		}
                		count ++;
        		}
			// If it is command for non-background related, call function that perform 
			// in foreground
			if (backgroundIndex == 0 ){
				launch_command (args,inputIndex,outputIndex);
			}
			// If it is command for background related, call function that perform in background
			else if (backgroundIndex != 0 ){
				launch_backgroud (args, inputIndex, outputIndex, backgroundIndex);
			}
		}
		// Free up the memory from the variable that contain value from readsplitCommand	
		free(inputString);
	}
	return 0;
}

// Function that will executed if the process is in the foreground (foreground job).
int launch_command(char **args, int in, int out){
	int status;
	int input,output,background;
	// Used to obtain process id 
	pid_t child;
	
	// Declar variable under sigset_t data type to represent signal set
	sigset_t newSet, origSet;
	sigset_t set;
	// Initialize/ reset the signal set to have all types of signals	
	sigfillset( &newSet );
 	struct sigaction act, new_act;
 
	// Help to idtentify action associated with signal (default action in this case)
 	new_act.sa_handler = SIG_DFL;
	// Provide additional instruction flags, set to zero instead because not plan use it
 	new_act.sa_flags = 0;
	// What signal should be block while signal handler is executing
  	new_act.sa_mask = set;

	// Set value to each variables been declared
	input = in;
	output = out;
	background = 0;

	// Declare new variable
	int fd_input,fd_output;

	// Double check if the command entered is not background process instead
	if ( background == 0){
		// Check whether user input any input or ouput redirection file.
		// This is the condition when user entered just command only  
		if (input == 0 && output == 0){
			child = fork();					
			if (child == -1){
				printf ("fork failed!\n");
				exitVal = 1;	
				return exitVal;			
			}
			// If fork success, do the command and display output to the screen
			else if (child == 0 ){
				sigaction(SIGINT, &new_act, &act);
				//execvp (args[0],args);
				
				// Condition check if the argument is not executable (random command
				// or word enter by user) 
				if (execvp(args[0],args) <= 0) {
					printf("No such file or directory\n");
					exitVal = 1;
					exit(1);
				}
				exitVal = 1;
			}
			else{
				if (args[1] != NULL && args[2]!= NULL) {
					exitVal = 1;
				} 
				// "Tell" parent to wait for the child 
				waitpid(child,&status,0);
			}
		}
		// This is the condition when the user want to perform input process (command < file)
		else if (input != 0 && output == 0){
			child = fork();
			// Condition if fork fail
			if (child == -1 ){
				perror ("fork failed!\n");
				exitVal = 1;	
				return exitVal;
			}
			// If fork success; open input file, the execute command, and display output to screen
			else if (child == 0){
				sigaction(SIGINT, &new_act, &act);
				// Opening the given input file 
				fd_input = open (args[input+1],O_RDONLY);
				// Condition if fail to open the input file
				if (fd_input == -1) {
					perror("open");
					exitVal = 1;
					exit(1);
				}
				// Change where stdin is pointing	
				dup2(fd_input,0);
				execvp(args[0],args);
				exitVal = 0;
			}
			else {
				// Tell parent to wait for the child
                                waitpid(child,&status,0);               
			}
		}
		// Condition when the user want to perform output proccess (command > file)
		else if (input == 0 && output != 0){
			child = fork();
			// Condition if fork fail
                        if (child == -1 ){
                                perror ("fork failed!\n");
				exitVal = 1;
				return exitVal;
                        }
			// If fork success; open output file, execute command and diplay the output to screen 
                        else if (child == 0){
                                sigaction(SIGINT, &new_act, &act);
				fd_output = open (args[output+1],O_WRONLY|O_CREAT|O_TRUNC,0644);
				// Condition if fail to open the output file
				if (fd_output == -1) {
					perror("open");
					exitVal = 1;
					exit(1);
				}
				// Change where stdout is pointing	
                                dup2(fd_output,1);
                                execvp(args[0],args);
				exitVal = 0;
                        }
                        else {
				// Tell the parent to wait for the child
                                waitpid(child,&status,0);               
                        }
		}
	}
	return 0;
}

// Function that will execut a process in the background, allowing the shell remain in the foreground
// and continues to read commands from the terminal.
int launch_backgroud (char **args, int in, int out, int bg){
        int input,output,backgorund;
	// Used to represent the process id of variable child
        pid_t child;

	// Set the values to each variable
        input = in;       
        output = out;
	
	// Declare new variable
        int fd_input,fd_output;
	
	// Condition when user entered just command only (no input output) 
	if (input == 0 && output == 0){				
		child = fork();
		// Condition if failed to fork						
		if (child == -1){
			printf ("Fork failed!\n");
			exitVal = 1;
			return exitVal;
		}
		// If fork success then do the command and display output to /dev/null
		else if (child == 0 ){			 
			printf("Background PID is %d \n",getpid());
			// user stdin redirected from /dev/null if not specifiy some other file to take stdin from
			fd_input = open("/dev/null",O_RDONLY);
			if (fd_input == -1) {
				perror("open");
				exitVal = 1;
				exit(1);
			}
			// Change where stdin is pointing	
			dup2 (fd_input,0);
			execvp (args[0],args);
			close(fd_input);
			exitVal = 0;
		}
	}
	// Condition when user want to perform input process (command <file)
	else if (input != 0 && output == 0){				
		child = fork();
		// Condition if fork fail
		if (child == -1 ){
			perror ("Fork failed!\n");	
			exitVal = 1;
			return exitVal;
		}
		// If fork success, open the input file, execute the command and output display to screen
		else if (child == 0){		
			printf("Background PID is %d \n",getpid());
			fd_input = open (args[input+1],O_RDONLY);
			// Condition if fail to open the input file
			if (fd_input == -1) {
				perror("open");
				exitVal = 1;
				exit(1);
			}
			// Change where stdin is pointing	
			dup2(fd_input,0);
			execvp(args[0],args);
			close(fd_input);
			exitVal = 0;	
		}
	}
	// Condition when user want to perform output process (command > file)			
	else if (input == 0 && output != 0){				
		child = fork();
		// Condition if user fail to fork
                if (child == -1 ){
                	perror ("Fork failed!\n");
			exitVal = 1;
			return exitVal;	
                }
		// Fork success, then open outputfile, execute command and output to fd_output instead	
                else if (child == 0){   
			printf(" Background PID is %d \n",getpid());
			fd_input = open ("/dev/null",O_RDONLY);
			if (fd_input == -1) {
				perror("open");
				exitVal = 1;
				exit(1);
			}	
                	fd_output = open (args[output+1],O_WRONLY|O_CREAT|O_TRUNC,0644);
			if (fd_output == -1) {
				perror("open");
				exitVal = 1;
				exit(1);
			}
			// Change where stdin and stdout are pointing	
			dup2(fd_input,0);
                	dup2(fd_output,1);
                	execvp(args[0],args);
			close(fd_input);
			close(fd_output);
			exitVal = 0;
                }
	}
	return 0;
}

