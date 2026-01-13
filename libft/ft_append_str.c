/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:47:37 by tbylund           #+#    #+#             */
/*   Updated: 2025/11/23 16:40:05 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append_str(char *dest, char *src)
{
	char	*temp;

	if (!src)
		return (dest);
	if (!dest)
		return (src);
	temp = dest;
	dest = ft_strjoin(temp, src);
	free(temp);
	free(src);
	return (dest);
}
