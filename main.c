#include<stdlib.h>
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
	char* command;
	char* args[257];
} snCommand = {NULL, NULL};

/*
 * Function prototypes
 */ 
void interactive();
void batch();
int spawnProc(char* command);
void getArgs(struct sCommand* arglist, char* command);

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
		if(fgets(instBuffer, 511, stdin) == NULL) {
			if(DEBUG)
				fprintf(stderr, "\nEOF hit, terminating...\n");
			quitting = 1;
		}

		if(DEBUG)
			fprintf(stderr, "Current buffer is %s\n", instBuffer);

		//Check for "quit" command
		//Only compare the first four characters because they're the
		//Only relevant ones
		if(strncmp(instBuffer, "quit", 4) == 0) {
			if(DEBUG)
				fprintf(stderr, "Quitting interactive mode.\n");
			quitting = 1;
		}
		//Run command(s); check the first element to make sure 
		//it isn't empty
		//An empty string may cause problems with strtok down the line
		else if(instBuffer[0] != '\n' && quitting != 1) {
		
			if(spawnProc(instBuffer) == 1)
				fprintf(stderr, "Failed to spawn child process.\n");
		
		}
	
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
int spawnProc(char* command) {

	//Vars
	pid_t child; //PID returned by fork()
	int cstatus; //exit status of child
	pid_t c; //PID returned by wait()
	
	int i, j;
	//Array of structs to store the exploded arguments
	struct sCommand args[257];

	//Call getArgs() to pull out the argument list for the command
	if(DEBUG)
		fprintf(stderr, "Calling getArgs() from spawnProc()\n");
	getArgs(args, command);

	//Count the number of commands to know how many child processes will
	//spawn
	for(i = 0; args[i].command != NULL; i++){}
	
	//Spawn process
	if(DEBUG)
		fprintf(stderr, "Forking processes:\n");

	for(j = 0; j < i; j++) {
		if((child = fork()) == 0) {
			//If child, run execvp()

			execvp(args[j].args[0], args[j].args);

			if(DEBUG)
				fprintf(stderr, "Child process failed execvp()\n");
			exit(1);
		}
		else {
			//If parent, check to make sure the fork succeeded
			if(child == (pid_t) (-1)) {
				fprintf(stderr, "Fork failed.\n");
				exit(1);
				//If no child was spawned, offset i for the
				//wait() loop
				i--;
			}
		}
	}
	
	//Execute wait() enough times to handle each spawned child process
	for(j = 0; j < i; j++) {
		c = wait(&cstatus);
		//Report the exit status of the child
		if(DEBUG)
			fprintf(stderr, "Parent: child %ld exited with status %d\n",
					(long) c, cstatus);
	}

	return 0;
}

//Function to pull out args from a command, because they must be passed in 
//separately into execvp()
void getArgs(struct sCommand* arglist, char* command) {
	
	int i;
	char* token;
	char* delim = ";";

	//Remove any newline present in initial input
	command[strcspn(command, "\n")] = 0;
	
	//Break input up based on ; token
	token = strtok(command, delim);

	for(i = 0; token != NULL; i++) {

		if(DEBUG)
			fprintf(stderr, "Processing command %s\n", token);
		//Temporarily store the entire command in the command field
		arglist[i].command = token;
		//Fetch the next token
		token = strtok(NULL, delim); //!! It's still using whitespace to delimit

	}

	//Store the last thing read in by the loop
	arglist[i].command = token;

	//Set a NULL terminator at the end of the array
	arglist[i].command = NULL;
	//Next, cycle through each command and break it up into its arguments
	int j, k;
	delim = " ";

	for(j = 0; j <= i; j++) {

		token = strtok(arglist[j].command, delim);

		for(k = 0; token != NULL; k++) {
			if(DEBUG)
				fprintf(stderr, "Processing argument %s\n", token);

			arglist[j].args[k] = token;
			token = strtok(NULL, delim);
		}

		//Append a NULL at the end of the argument array
		arglist[j].args[k+1] = NULL;
	}
	

}
