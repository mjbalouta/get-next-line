/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:54:30 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/05/01 11:59:03 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*ptr;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] != '\n')
		{
			ptr[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		ptr[i++] = s2[j++];
	}
	return (ptr);
}
// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void	*ptr;
// 	size_t	i;
// 	char	*temp;

// 	i = 0;
// 	if (size != 0 && nmemb > (__SIZE_MAX__ / size))
// 		return (NULL);
// 	ptr = malloc(nmemb * size);
// 	if (ptr == NULL)
// 		return (NULL);
// 	temp = (char *)ptr; 
// 	while (i < (nmemb * size))
// 	{
// 		temp[i] = '\0';
// 		i++;
// 	}	
// 	return (ptr);
// }

void	ft_clean_array(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		ptr[i] = '\0';
		i++;
	}
}

int	ft_filling_line(char *line, int bytes_read, char *buffer, char *remain)
{
	int	i;
	int	z;
	int found;

	i = 0;
	z = 0;
	found = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0' && i < bytes_read)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	if (i++ < bytes_read)
	{
		while (i < bytes_read)
			remain[z++] = buffer[i++];
		remain[z] = '\0';
		found = 1;
	}
	return (found);
}

// void	ft_read_and_fill(int fd, char *result, char *line, char *remain)
// {
// 	int		bytes_read;
// 	char	buffer[BUFFER_SIZE];
	
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read < 0)
// 			return (NULL);
// 		if (bytes_read == 0)
// 			return (result);
// }

