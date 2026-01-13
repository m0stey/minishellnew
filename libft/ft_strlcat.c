/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:56:21 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/19 16:40:05 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_length;
	size_t	src_length;
	size_t	i;
	size_t	j;

	dst_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	i = 0;
	j = dst_length;
	if (size == 0)
		return (src_length);
	if (size <= dst_length)
		return (size + src_length);
	while (src[i] != '\0' && i + j < size -1)
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (dst_length + src_length);
}
