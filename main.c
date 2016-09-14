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
		else if(instBuffer[0] != '\0' && quitting != 1) {
		
			if(spawnProc(instBuffer) == 1)
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
int spawnProc(char* command) {

	//Array of structs to store the exploded arguments
	struct sCommand args[257];

	//Call getArgs() to pull out the argument list for the command
	if(DEBUG)
		fprintf(stderr, "Calling getArgs() from spawnProc()\n");
	getArgs(args, command);
	
	//TODO: Use execvp() here and pass in the command as-is
	return 0;
}

//Function to pull out args from a command, because they must be passed in 
//separately into execvp()
int getArgs(struct sCommand* arglist, char* command) {
	
	//First, break input up based on ; token
	int i;
	char* token;
	char* delim = ";";

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

	//Next, cycle through each command and break it up into its arguments
	int j, k;
	delim = " ";

	for(j = 0; j <= i; j++) {

		//Throw away the first token, since it's just the command name
		token = strtok(arglist[j].command, delim);

		token = strtok(NULL, delim);
		for(k = 0; token != NULL; k++) {
			if(DEBUG)
				fprintf(stderr, "Processing argument %s\n", token);

			arglist[j].args[k] = token;
			token = strtok(NULL, delim);
		}

		//Append a NULL at the end of the argument array
		arglist[j].args[k+1] = NULL;
	}
	
	if(DEBUG) {
		fprintf(stderr, "Arguments:\n");
		for(j = 0; j < i; j++) {
			fprintf(stderr, "\t%s | ", arglist[j].command);
			for(k = 0; arglist[j].args[k] != NULL; k++)
				fprintf(stderr, "%s ", arglist[j].args[k]);
			fprintf(stderr, "\n");
		}
	}

	return 0;
}
