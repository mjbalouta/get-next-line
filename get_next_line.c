/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:08:03 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/30 23:53:02 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# define BUFFER_SIZE 1

char	*get_next_line(int fd)
{
	static char	remain[BUFFER_SIZE];
	int			z;
	char		*result;
	int			found;
	int			i;
	char		buffer[BUFFER_SIZE];
	char		line[BUFFER_SIZE];
	int			bytes_read;
	
	z = 0;
	found = 0;
	i = 0;
	result = ft_calloc(1, sizeof(char));
	if (!result)
    	return (NULL);
	if (remain[0])
	{
		result = ft_strjoin(result, remain);
		while (remain[z])
			remain[z++] = '\0';
	}
	while (found == 0)
	{
		i = 0;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			return (result);
		while (buffer[i] != '\n' && buffer[i] != '\0' && i < bytes_read)
		{
			line[i] = buffer[i];
			i++;
		}
		line[i] = '\0';
		if (i < bytes_read)
		{
			i++;
			while (i < bytes_read)
				remain[z++] = buffer[i++];
			remain[z] = '\0';
			found = 1;
		}
		result = ft_strjoin(result, line);
		i = 0;
		while (line[i])
			line[i++] = '\0';
	}
	result = ft_strjoin(result, "\n");
	return (result);
}
#include <stdio.h>
int	main(int argc, char **argv)
{	
	if (argc < 2)
		return (write(2, "Error. Missing file or input.", 29));
	int fd = open(argv[1], O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	free(result);
	return (0);
}