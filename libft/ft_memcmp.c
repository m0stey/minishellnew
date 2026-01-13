/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:16:41 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/18 13:59:13 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*pntr1;
	const unsigned char	*pntr2;

	i = 0;
	pntr1 = (const unsigned char *)s1;
	pntr2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (pntr1[i] != pntr2[i])
			return (pntr1[i] - pntr2[i]);
		i++;
	}
	return (0);
}
