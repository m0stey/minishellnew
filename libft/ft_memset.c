/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:50:51 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/23 17:07:55 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pntr;

	pntr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		pntr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
