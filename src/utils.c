/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:53:16 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/11 20:50:43 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// libft
char	**ft_split(const char *s, char c);

void	msg_and_exit(char *msg, int exit_code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(exit_code);
}

void	perror_and_exit(char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}

int	create_color(int transparency, int red, int green, int blue)
{
	return (transparency << 24 | red << 16 | green << 8 | blue);
}

int	count_words(char *line)
{
	int	words;
	int	in_word;

	words = 0;
	in_word = 0;
	while (*line != '\0' && *line != '\n')
	{
		while (*line != '\0' && *line != '\n' && *line == ' ')
			line++;
		if (*line != '\0' && *line != '\n' && !in_word)
		{
			words++;
			in_word = 1;
		}
		while (*line != '\0' && *line != '\n' && *line != ' ')
			line++;
		if (*line == ' ')
			in_word = 0;
	}
	return (words);
}
