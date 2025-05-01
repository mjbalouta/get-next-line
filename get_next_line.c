/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:08:03 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/05/01 11:58:55 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	remain[BUFFER_SIZE + 1];
	char		*result;
	int			found;
	char		buffer[BUFFER_SIZE];
	char		line[BUFFER_SIZE];
	int			bytes_read;
	
	found = 0;
	result = malloc(1 * sizeof(char));
	if (!result)
    	return (NULL);
	result = "";
	if (remain[0])
	{
		result = ft_strjoin(result, remain);
		ft_clean_array(remain);
	}
	while (found == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			return (result);
		found = ft_filling_line (line, bytes_read, buffer, remain);
		result = ft_strjoin(result, line);
		ft_clean_array(line);
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
	free(line);
	return (0);
}