/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:56:18 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/24 16:23:16 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pntr;

	pntr = malloc(nmemb * size);
	if (pntr == NULL)
		return (NULL);
	ft_bzero(pntr, nmemb * size);
	return (pntr);
}
// #include <stdio.h>

// int main(void)
// {
// 	int *arr;
// 	size_t i, n = 5;

// 	arr = (int *)ft_calloc(n, sizeof(int));
// 	if (arr == NULL)
// 	{
// 		printf("Memory allocation failed\n");
// 		return (1);
// 	}

// 	for (i = 0; i < n; i++)
// 		printf("arr[%zu] = %d\n", i, arr[i]);

// 	free(arr);
// 	return (0);
// }