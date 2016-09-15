#---------------------------------------------------------------------#
# COP4610 Operating Systems Project 1: Shell
# By: Julian Engel (jse13)
#---------------------------------------------------------------------#

##Design Overview
The overall structure of this program is as follows:
- Two helper functions, `interactive()` and `batch(char*)`
- One generic process-handling function, `spawnProc(char*)`
- One generic input-parsing function, `getArgs(sCommand*, char*)`
`main()` will call either `interactive()` or `batch(char*)` depending on the
number of command-line arguments passed in. `batch` will only be called
if the number of command-line arguments is *exactly* one - two or more
arguments will cause an error.

##Complete Specification

##Known Bugs/Problems
The struct sCommands is completely unnecessary - a simple array of char arrays
would suffice. sCommands arose out of my initial lack of understanding of the
`execvp()` command's syntax (thinking that the command itself had to be stored
separately from the arguments). By the time I realized this, `getArgs()` already
relied heavily on the structure of sCommands, so I did not rework the code. If
I were to further develop this shell I would do so to reduce complexity and 
space requirements. 

