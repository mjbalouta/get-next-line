/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:55:55 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/29 12:48:50 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# define BUFFER_SIZE 3

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	int			i;
	int			first;
	char		*str;
	int			z;
	static char	remainder[BUFFER_SIZE];
	int			y;
	int			bytes_read;

	i = 0;
	z = 0;
	y = 0;
	first = 1;
	while (buffer[i] != '\n' || first == 1)
	{
		if (i >= bytes_read || first == 1)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			i = 0;
		}
		if (first == 1)
		{
			while (buffer[i] != '\n' && buffer[i])
				i++;
			str = (char *)malloc(sizeof(char) * (i + 1));
			str[i] = '\0';
			i = 0;
			first = 0;
		}
		if (buffer[i] == '\n')
		{
			while (i < bytes_read)
			{
				remainder[y] = buffer[i + 1];
				y++;
				i++;
			}
			return (str);
		}
		str = ft_strjoin(str, buffer);	
		i = i + BUFFER_SIZE;	
	}
	return (str);
}

int	main(int argc, char **argv)
{	
	int	i;
	
	i = 0;
	if (argc < 2)
		return (write(2, "Error. Missing file or input.", 29));
	int fd = open(argv[1], O_RDONLY);
	char *line = get_next_line(fd);
	while (line[i])
		write(1, &line[i++], 1);
	return (0);
}