/*
This file contains functions for terminating the program in a controlled manner
whenever an error occurs (such as invalid user input, failed file opening,
memory allocation errors, etc.). Before terminating the program, informative
error messages are printed to stderr, and all dynamically allocated memory
within the FDF structure is deallocated.
*/

#include "fdf.h"

// IN FILE

void	msg_and_exit(char *msg, t_fdf *fdf);
void	perror_and_exit(char *msg, t_fdf *fdf);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Prints an error message to stderr, frees memory allocated within the
fdf structure and exits the program.
*/
void	msg_and_exit(char *msg, t_fdf *fdf)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	free_fdf(&fdf);
	exit(EXIT_FAILURE);
}

/*
Prints an error message to stderr via perror(), which also prints the last
encountered error and frees memory allocated within the fdf structure.
Then, exits the program.
*/
void	perror_and_exit(char *msg, t_fdf *fdf)
{
	perror(msg);
	free_fdf(&fdf);
	exit(EXIT_FAILURE);
}
