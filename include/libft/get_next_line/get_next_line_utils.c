/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:02:12 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/06/12 16:10:26 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	is_eol(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

// get line len until '\n' previous allocated space + buffer
size_t	get_len(char *previous, char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (previous && previous[i])
		++i;
	j = 0;
	while (buffer && buffer[j] && buffer[j - 1] != '\n')
		++j;
	return (i + j);
}

// allocate space with buffer len
char	*strjoin(char *previous, char *buffer)
{
	int		len;
	int		i;
	int		j;
	char	*new_string;

	len = get_len(previous, buffer);
	new_string = malloc(sizeof(char) * (len + 1));
	if (!new_string)
	{
		free(previous);
		return (NULL);
	}
	i = 0;
	while (previous && previous[i])
	{
		new_string[i] = previous[i];
		++i;
	}
	j = -1;
	while (i < len)
		new_string[i++] = buffer[++j];
	new_string[i] = 0;
	free(previous);
	return (new_string);
}

char	*move_buffer(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		++i;
	j = 0;
	while (buffer[i])
	{
		buffer[j] = buffer[++i];
		++j;
	}
	while (buffer[j])
	{
		buffer[j] = 0;
		++j;
	}
	return (buffer);
}
