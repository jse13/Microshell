#---------------------------------------------------------------------#
# COP4610 Operating Systems Project 1: Shell
# By: Julian Engel (jse13)
#---------------------------------------------------------------------#

##Design Overview:
	The overall structure of this program is as follows:
		Two helper functions, `interactive()` and `batch(char*)`
		One generic process-handling function, `spawnProc(char*)`
		One generic input-parsing function, `getArgs(sCommand*, char*)`
	`main()` will call either `interactive()` or `batch(char*)` depending on the
	number of command-line arguments passed in. `batch` will only be called
	if the number of command-line arguments is *exactly* one - two or more
	arguments will cause an error.

##Complete Specification:

##Known Bugs/Problems:

