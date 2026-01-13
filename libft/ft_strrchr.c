/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:29:30 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/23 17:28:54 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	j;

	j = ft_strlen(s);
	while (j > 0)
	{
		if (s[j] == (char)c)
			return ((char *)&s[j]);
		j--;
	}
	if (s[0] == (char)c)
		return ((char *)&s[0]);
	return (NULL);
}
