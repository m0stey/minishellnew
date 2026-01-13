/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:14:10 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/23 17:08:54 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_string;
	size_t	length;

	length = ft_strlen(s);
	new_string = (char *)malloc(length + 1);
	if (new_string == NULL)
		return (NULL);
	ft_memcpy(new_string, s, length);
	new_string[length] = '\0';
	return (new_string);
}
