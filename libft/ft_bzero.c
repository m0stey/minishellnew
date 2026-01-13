/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:28:33 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/18 14:46:07 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*pntr;

	pntr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		pntr[i] = 0;
		i++;
	}
}

// int	main(void)
// {
//     char str[20] = "Hello, World!";

//     // Print original string
//     printf("Before ft_bzero: %s\n", str);

//     // Call your ft_bzero function to zero out part of the string
//     ft_bzero(str + 7, 6);  // Zeroes out "World!"

//     // Print result after calling ft_bzero
//     printf("After ft_bzero: %s\n", str);  // Only "Hello, " should remain

//     return 0;
// }