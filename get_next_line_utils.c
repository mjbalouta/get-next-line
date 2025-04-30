/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:54:30 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/30 14:23:58 by mjoao-fr         ###   ########.fr       */
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

// char	*ft_strjoin(char const *s1, char const *s2, int limit)
// {
// 	int		size;
// 	char	*ptr;
// 	int		i;
// 	int		j;
// 	int		end;

// 	size = ft_strlen(s1) + ft_strlen(s2);
// 	ptr = (char *)malloc(sizeof(char) * (size + 1));
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	end = 0;
// 	while (s1[i])
// 	{
// 		if (s1[i] != '\n')
// 		{
// 			ptr[i] = s1[i];
// 			i++;
// 		}
// 		if (i >= limit)
// 			end = 1;
// 	}
// 	while (s2[j])
// 	{
// 		if (s2[j] == '\n' && end != 1)
// 			return (ptr);
// 		ptr[i++] = s2[j++];
// 	}
// 	return (ptr);
// }
char	*ft_strndup(const char *s, int limit)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
	{
		return (NULL);
	}
	while (i < len && i < limit)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char )c)
		i++;
	if (s[i] == (char )c || !c)
		return ((char *)(s + i));
	return (NULL);
}