#include<string.h>
#include<stdio.h>
#include<sys/types.h> // For pid_t type
#include<sys/wait.h>  // For wait()
#include<unistd.h>    //Declarations for execvp(), access(), etc
#include<string.h>    //String operations like strcmp()

#define DEBUG 1

/*
 * Struct for instructions
 */ 
struct sCommand {
	char command[512];
	char* args[257];
};

/*
 * Function prototypes
 */ 
void interactive();
void batch();
int spawnproc(char* command);
int getArgs(struct sCommand* arglist, char* command);

/*
 * Main function
 */ 

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

	//Buffer for read-in instruction, with max size of 256
	char instBuffer[512];

	if(DEBUG)
		printf("Starting in interactive mode\n");

	//create a loop to get user input
	while(!quitting) {
		//Display prompt string
		printf("|> ");

		//ask for input; check against EOF in case <C-d> was pressed
		if(scanf("%511s", instBuffer) == EOF) {
			if(DEBUG)
				fprintf(stderr, "EOF hit, terminating...\n");
			quitting = 1;
		}

		//Check for "quit" command
		if(strcmp(instBuffer, "quit") == 0) {
			if(DEBUG)
				fprintf(stderr, "Quitting interactive mode.\n");
			quitting = 1;
		}
		//TODO: run command(s); check the first element to make sure 
		//it isn't empty
		else if(instBuffer[0] != '\0') {
		
			if(spawnproc(instBuffer) == 1)
				fprintf(stderr, "Failed to spawn child process.\n");
		
		}

		//TODO: check if command line is empty
	
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

	//Array of structs to store the exploded arguments
	struct sCommand args[257];
	//TODO: Call getArgs() to pull out the argument list for the command
	//TODO: Use execvp() here and pass in the command as-is
	return 0;
}

//Function to pull out args from a command, because they must be passed in 
//separately into execvp()
int getArgs(struct sCommand* arglist, char* command) {
	
	//strtok();
	return 0;
}
