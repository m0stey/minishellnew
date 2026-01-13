/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:56:41 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/18 14:22:17 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
