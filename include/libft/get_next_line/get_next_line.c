/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:05:26 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/06/12 16:00:16 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*result;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result = NULL;
	bytes_read = 1;
	while (bytes_read)
	{
		if (!buf[0])
			bytes_read = read(fd, buf, BUFFER_SIZE);
		if ((!buf[0] && !bytes_read && !result) || bytes_read == -1)
		{
			free(result);
			return (NULL);
		}
		result = strjoin(result, buf);
		if (!result)
			return (NULL);
		move_buffer(buf);
		if (is_eol(result))
			break ;
	}
	return (result);
}

/*
int main(int argc, char **argv)
{
  int fd;
  char *result;

  if (argc != 2)
    return (1);
  fd = open(argv[1], O_RDONLY);
  if (fd < 0)
    return (2);

  while ((result = get_next_line(fd)))
  {
	  printf("%s", result);
	  free(result);
  }
  close(fd);
  return (0);
}
*/
