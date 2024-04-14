/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:53:16 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/14 13:36:52 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// FILE

void	msg_and_exit(char *msg);
void	perror_and_exit(char *msg);
int		count_words(const char *str);
int		ft_fgetc(int fd);

// libft

void	ft_putstr_fd(char *s, int fd);
char	**ft_split(const char *s, char c);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

/*
Prints an error message to stderr and exits the program with
specified exit code.
*/
void	msg_and_exit(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/*
Prints an error message to stderr via perror(), which also prints the last
encountered error. Then, exits the program with specified exit code.
*/
void	perror_and_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	create_color(int transparency, int red, int green, int blue)
{
	return (transparency << 24 | red << 16 | green << 8 | blue);
}

/*
Takes a string str as parameters.
Counts count the number of words in the given string, where words are separated
by spaces, newline characters or EOF.
*/
int	count_words(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ' && str[i] != '\n')
		{
			count++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		else
		{
			while (str[i] && str[i] == ' ')
				i++;
		}
	}
	return (count);
}
