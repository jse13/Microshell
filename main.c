#include<string.h>
#include<stdio.h>
#include<sys/types.h> // For pid_t type
#include<sys/wait.h>  // For wait()
#include<unistd.h>    //Declarations for execvp(), access(), etc


#define DEBUG 1
/*
 * Function prototypes
 */ 
void interactive();
void batch();
int spawnproc(char* command);


/*
 * Main function
 */ 
int getArgs(char* arglist, char* command);

int main(int argc, char* argv[]) {

	//Determine whether this shell is being run in interactive mode
	//or batch mode
	if(argc == 1)
		interactive();
	else
		batch();

	return 0;
}

//Controlling function for interactive mode
void interactive() {
	int quitting = 0;

	if(DEBUG)
		printf("Starting in interactive mode\n");

	//TODO: create a loop to get user input
	while(!quitting) {
		//Display prompt string
		//printf("|> ");
		//TODO: ask for input
		//TODO: check input for ; or "quit"
		//TODO: run command(s)
	}
}

//Controlling function for batch mode
void batch() {

	if(DEBUG)
		printf("Starting in batch mode\n");

	//TODO: create loop to parse batch file
		//TODO: get the command
		//TODO: echo the command before running it
		//TODO: check for ; or "quit"
		//TODO: run command(s)
}

//Function to spawn a child process and let it execute
int spawnproc(char* command) {
	//TODO: Call getArgs() to pull out the argument list for the command
	//TODO: Use execvp() here and pass in the command as-is
}

//Function to pull out args from a command, because they must be passed in separately
//into execvp()
int getArgs(char* arglist, char* command) {

}
