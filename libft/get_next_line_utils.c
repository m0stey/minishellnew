/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:49:35 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/10 17:42:38 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0' || s[i] == ((char)c))
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*new_string;
	size_t	length;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	new_string = (char *)malloc(length + 1);
	if (new_string == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[length] = '\0';
	return (new_string);
}

size_t	ft_strlen(const char *s)
{
	size_t	length;

	if (s == NULL)
		return (0);
	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

char	*ft_substr(char const *s, unsigned int start, size_t length)
{
	char			*dup_string;
	size_t			i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (length > length - start)
		length = length - start;
	dup_string = (char *)malloc((length + 1) * sizeof(char));
	if (dup_string == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dup_string[i] = s[start + i];
		i++;
	}
	dup_string[i] = '\0';
	return (dup_string);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*combined;
	size_t	length;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	combined = (char *)malloc(length + 1);
	if (combined == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		combined[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		combined[i++] = s2[j++];
	combined[i] = '\0';
	return (combined);
}
