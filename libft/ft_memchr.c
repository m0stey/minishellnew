/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:55:37 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/18 14:47:50 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*pntr;

	pntr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (pntr[i] == (const unsigned char)c)
			return ((void *)(const unsigned char *)&pntr[i]);
		i++;
	}
	return (NULL);
}
