/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:08:03 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/05/06 16:50:16 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_clean_free(char *result, char *str, int clean, int rem)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strjoin(result, str);
	free(result);
	if (clean)
	{
		while (str[i])
			str[i++] = '\0';
	}
	i = 0;
	if (rem == 1)
	{
		while (result[i] != '\n')
			result[i++] = '\0';
		result = result + i + 1;
	}
	return (temp);
}

int	ft_filling_line(char *line, int b_read, char *buffer, char **remain)
{
	int		i;
	int		found;
	int		z;

	i = 0;
	found = 2;
	z = 0;
	if (!line || !buffer)
		return (-1);
	while (buffer[i] != '\n' && buffer[i] != '\0' && i < b_read)
	{
		line[i] = buffer[i];
		i++;
	}
	if (i < b_read)
	{
		i++;
		while (i < b_read && buffer[i] != '\n')
			(*remain)[z++] = buffer[i++];
		found = 1;
	}
	return (ft_clean_array(buffer), found);
}

int	ft_read_and_fill(int fd, char *line, char **remain)
{
	int		bytes_read;
	char	buffer[BUFFER_SIZE + 1];
	int		found;

	found = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes_read] = '\0';
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0)
		return (0);	
	found = ft_filling_line(line, bytes_read, buffer, remain);
	return (found);
}

void	ft_free_arrays(char *remain, char *result, char *line)
{
	if (remain)
	{
		free(remain);
		remain = NULL;
	}
	if (result)
	{
		free(result);
		result = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*result;
	int			found;
	char		*line;

	found = 2;
	result = ft_calloc(1, sizeof(char));
	if (!remain)
		remain = ft_calloc(BUFFER_SIZE, sizeof(char));
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!remain || !result || !line)
		return (NULL);
	if (remain[0])
		result = ft_join_clean_free(result, remain, 1, 0);
	while (found == 2)
	{
		found = ft_read_and_fill(fd, line, &remain);
		if (found == -1 || (found == 0 && result[0] == '\0'))
			return (ft_free_arrays(remain, result, line), NULL);
		if (found == 0)
			return (ft_free_arrays(remain, NULL, line), result);
		result = ft_join_clean_free(result, line, 1, 0);
	}
	result = ft_join_clean_free(result, "\n", 0, 0);
	return (ft_free_arrays(NULL, NULL, line), result);
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