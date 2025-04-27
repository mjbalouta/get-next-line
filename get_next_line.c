/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:57:21 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/26 11:57:21 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# define BUFFER_SIZE 2

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	int			bytes_read;
	int			i;
	char		*str;
	static char	*remainder;
	int			z;

	i = 0;
	z = 0;
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
	i = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return NULL;
	if (!remainder)
	{
		while (buffer[i] != '\n' && buffer[i] != '\0' && i < bytes_read)
			i++;
		str = (char *)malloc(sizeof(char) * (i + 1));
		if (!str)
			return (NULL);
		str[i] = '\0';
		i = 0;
	}
	else 
	{
		while (remainder[i] != '\n' || remainder[i] != '\0' || i < bytes_read)
			i++;
		str = (char *)malloc(sizeof(char) * (i + 1));
		if (!str)
			return (NULL);
		str[i] = '\0';
		i = 0;
		if (remainder[i])
		{
			while (remainder[i] != '\0')
			{
				str[i] = remainder[i];
				i++;
				if (remainder[i] == '\n')
				{
					remainder[i] = '\n';
					return (str);
				}
			}
		}
	}
	while (i < bytes_read)
	{
		if (buffer[i] == '\n')
		{
			remainder = (char *)malloc(sizeof(char) * (bytes_read - i));
			if (!remainder)
				return NULL;
			str[i] = '\n';
			return (str);
		}
		str[i] = buffer[i];
		i++;
	}
	i = i + 1;
	while (i < bytes_read)
		remainder[z++] = buffer[i++]; 
	return (str);
}

int	main(int argc, char **argv)
{
	char	*str = "NULL";
	int		fd;
	int		i;
	int		z;

	i = 0;
	z = 0;
	if (argc < 2)
		return (write(2, "Error", 5));
	fd = open(argv[1], O_RDONLY);
	while (z < 3)
	{
		str = get_next_line(fd);
		while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
		z++;
		i = 0;
	}
	return (0);
}


