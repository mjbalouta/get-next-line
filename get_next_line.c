/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:08:03 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/05/02 22:18:52 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_filling_line(char *line, int b_read, char *buffer, char *remain)
{
	int	i;
	int	z;
	int	found;

	i = 0;
	z = 0;
	found = 2;
	while (buffer[i] != '\n' && buffer[i] != '\0' && i < b_read)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	if (i++ < b_read)
	{
		while (i < b_read)
			remain[z++] = buffer[i++];
		remain[z] = '\0';
		found = 1;
	}
	return (found);
}

static int	ft_read_and_fill(int fd, char *line, char *remain)
{
	int		bytes_read;
	char	buffer[BUFFER_SIZE];
	int		found;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0)
		return (0);
	found = ft_filling_line (line, bytes_read, buffer, remain);
	return (found);
}

static char	*ft_join_clean_free(char *result, char *str, int clean)
{
	char	*temp;

	temp = ft_strjoin(result, str);
	free(result);
	if (clean)
		ft_clean_array(str);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	remain[BUFFER_SIZE + 1];
	char		*result;
	int			found;
	char		line[BUFFER_SIZE];

	found = 2;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	if (remain[0])
		result = ft_join_clean_free(result, remain, 1);
	while (found == 2)
	{
		found = ft_read_and_fill(fd, line, remain);
		if (found == -1)
			return (free(result), NULL);
		if (found == 0)
		{
			if (result[0] == '\0')
				return (free(result), NULL);
			return (result);
		}
		result = ft_join_clean_free(result, line, 1);
	}
	result = ft_join_clean_free(result, "\n", 0);
	return (result);
}
// #include <stdio.h>
// int	main(int argc, char **argv)
// {	
// 	if (argc < 2)
// 		return (write(2, "Error. Missing file or input.", 29));
// 	int fd = open(argv[1], O_RDONLY);
// 	char *line;
// 	int i = 0;
// 	while(i < 10){
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
	
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// free(line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// free(line);
// 	close(fd);
// 	return (0);
// }