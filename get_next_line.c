/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:08:03 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/05/05 15:33:25 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_filling_line(char *line, int b_read, char *buffer, char *remain)
{
	int	i;
	int	found;

	i = 0;
	found = 2;
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (-1);
	while (buffer[i] != '\n' && buffer[i] != '\0' && i < b_read)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	if (i < b_read)
	{
		ft_strjoin(remain, buffer);
		found = 1;
	}
	return (found);
}

int	ft_read_and_fill(int fd, char *line, char *remain)
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

char	*ft_join_clean_free(char *result, char *str, int clean)
{
	char	*temp;

	temp = ft_strjoin(result, str);
	free(result);
	if (clean)
		free(str);
	return (temp);
}
void	ft_initialize_arrays(char *remain, char *result, char *line)
{
	result = ft_calloc(1, sizeof(char));
	remain = ft_calloc(1, sizeof(char));
	line = ft_calloc(1, sizeof(char));
	if (!remain || !result || !line)
		return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*result;
	int			found;
	char		*line;

	found = 2;
	ft_initialize_arrays(remain, result, line);
	if (remain[0])
		result = ft_join_clean_free(result, remain, 1);
	while (found == 2)
	{
		found = ft_read_and_fill(fd, line, remain);
		if (found == -1)
			return (ft_free_arrays(remain, result, line), NULL);
		if (found == 0)
		{
			if (result[0] == '\0')
				return (ft_free_arrays(remain, result, line), NULL);
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
// 	while(i < 1){
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