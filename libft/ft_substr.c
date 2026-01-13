/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:00:03 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/23 19:02:04 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t length)
{
	char			*dup_string;
	size_t			i;
	size_t			len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (start >= len)
		return (ft_strdup(""));
	if (length > len - start)
		length = len - start;
	dup_string = (char *)malloc((length + 1) * sizeof(char));
	if (dup_string == NULL)
		return (NULL);
	i = 0;
	while (i < length && s[start + i] != '\0')
	{
		dup_string[i] = s[start + i];
		i++;
	}
	dup_string[i] = '\0';
	return (dup_string);
}
