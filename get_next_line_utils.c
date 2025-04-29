/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:54:30 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/29 23:19:59 by mjoao-fr         ###   ########.fr       */
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
	int		end;

	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	end = 0;
	while (s1[i])
	{
		if (s1[i] != '\n')
			ptr[i] = s1[i++];
	}
	while (s2[j])
	{
		if (s2[j] == '\n')
			return (ptr);
		ptr[i++] = s2[j++];
	}
	return (ptr);
}
