/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:08:03 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/05/08 14:42:10 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_result_line(char *result, int bytes_read, char *buffer, char **remain, int *found)
{
	char	*line;
	char	*temp;
	int		i;
	int		z;
	
	i = -1;
	z = 0;
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (++i < bytes_read && buffer[i] != '\n' && buffer[i] != '\0')
		line[i] = buffer[i];
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		ft_clean_array(*remain);
		while (++i < bytes_read)
			(*remain)[z++] = buffer[i];
		*found = 1;
	}
	temp = ft_strjoin(result, line);
	ft_free_arrays(result, line);
	return (temp);
}

char	*ft_read_and_fill(int fd, char *result, char **remain, int *found)
{
	int		bytes_read;
	char	*buffer;
	
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if(!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (ft_free_arrays(buffer, NULL), NULL);
	if (bytes_read == 0)
	{
		free(*remain);
		*remain = NULL;
		*found = 0;
		if (result[0] == '\0')
		{
			free(result);
			result = NULL;
		}
		return (ft_free_arrays(buffer, NULL), result);
	}
	result = ft_join_result_line(result, bytes_read, buffer, remain, found);
	return (ft_free_arrays(buffer, NULL), result);
}

void	ft_fill_w_remain(char *result, char **remain, int *found)
{
	int		i;
	int		z;

	i = 0;
	z = 0;
	while ((*remain)[i] && (*remain)[i] != '\n' && i < BUFFER_SIZE)
	{
		result[i] = (*remain)[i];
		i++;
	}
	if ((*remain)[i] == '\n')
	{
		result[i] = '\n';
		*found = 1;
		i++;
		while ((*remain)[i])
			(*remain)[z++] = (*remain)[i++];
		while (z < BUFFER_SIZE + 1)
			(*remain)[z++] = 0;
	}
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*result;
	int			found;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	found = 2;
	result = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!remain)
		remain = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!remain || !result)
		return (free(result), NULL);
	if (remain[0])
		ft_fill_w_remain(result, &remain, &found);
	while (found == 2)
	{
		result = ft_read_and_fill(fd, result, &remain, &found);
		if (result == NULL)
		{
			free(remain);
			remain = NULL;
			return (ft_free_arrays(result, NULL), NULL);
		}
	}
	return (result);
}
#include <stdio.h>
int	main(int argc, char **argv)
{	
	if (argc < 2)
		return (write(2, "Error. Missing file or input.", 29));
	int fd = open(argv[1], O_RDONLY);
	char *line;
	while((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}	
	close(fd);
	return (0);
}