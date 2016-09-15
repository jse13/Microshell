# COP4610 Operating Systems Project 1: Shell
## By: Julian Engel (jse13)

##Design Overview
The overall structure of this program is as follows:
- Two helper functions, `interactive()` and `batch(char*)`
- One generic process-handling function, `spawnProc(char*)`
- One generic input-parsing function, `getArgs(sCommand*, char*)`.

`main()` will call either `interactive()` or `batch(char*)` depending on the
number of command-line arguments passed in. `batch` will only be called
if the number of command-line arguments is *exactly* one - two or more
arguments will cause an error.
`interactive()` is a loop that takes in commands from `stdin`, provided by the 
user at runtime. Multi-commands can be specified by separating them with a `;`
character (this behavior differs from other shells in that the commands are run
in parallel, not in serial). `interactive()` will exit upon the `quit` command,
or if `EOF` is simulated with <C-d>.
`batch(char*)` receives a filename as a string, which is a file containing 
several lines of commands to be run. This loop ends when `quit` is encountered
in the batch file, or an `EOF` is encountered. 
`spawnProc(char*)` takes a command in the form of a string, has it broken up
into usable segments by `getArgs(sCommand*, char*)`, then runs each command
in parallel (in the event of a multi-command). This function uses `execvp`
to run the commands. The function will not end until each command has been
run - this is controlled via a secondary loop calling `wait` the same number
of times as processes that were spawned. Since `wait` simply waits for a
change in any child process, it will wait until there are no more children
left before continuing execution. Also, if a multi-command is read in that
includes `quit`, `spawnProc` will execute as normal, but also return 1 to let
whatever function called it know that it needs to exit - in this case, both
`interactive` and `batch` maintain a setinel variable called `quitting` that, when 0,
allows the loop to continue running.
`getArgs(sCommand*, char*)` takes in a command, and a struct of type `sCommand`,
breaks up the command into segments that are useable by `execvp` (that is, the
command and each of its arguments are separate strings within an array, terminated
by a `NULL`). The broken down commands are stored inside of the array of structs.
The `sCommand` struct contains a string to hold the initial command, and an array
of strings to hold arguments. 

##Complete Specification
- This program will not execute if too many arguments are passed in (currently more than 0 or 1).
  - `argc` is checked before `interactive()` or `batch(char*)` are run.
- This program will not execute if the file provided for batch processing doesn't exist.
  - The return value of `fopen` is verified before the main loop begins, and will
  break early if necessary.
- This program will not error out if there are unnecessary `;`.
  - This is because of the nature of `strtok`, using `;` as a delimiter, and a loop that will not exit
  unless `strtok` is returning `NULL`.
- This program will not error out if no input is given.
  - `spawnProc` will not be run if there are no commands to execute.
- This program will not error out if bad commands are given.
  - Proper error handling is implemented after running `execvp`; that is, if
  the process has not been transformed into something else it will self terminate.
  - The program will not call `wait` for processes that prematurely fail.
- This program does not accept input larger than 512 characters - 'fgets' is given
a hard limit of 511 characters.
  - 511 characters will be read and any valid ones will be executed, however.

##Known Bugs/Problems
The struct sCommands is completely unnecessary - a simple array of char arrays
would suffice. sCommands arose out of my initial lack of understanding of the
`execvp()` command's syntax (thinking that the command itself had to be stored
separately from the arguments). By the time I realized this, `getArgs()` already
relied heavily on the structure of sCommands, so I did not rework the code. If
I were to further develop this shell I would do so to reduce complexity and 
space requirements. 

