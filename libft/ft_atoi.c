/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:16:13 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/24 16:12:35 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	i = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
		if (nptr[i] == '-' || nptr[i] == '+')
			return (0);
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
// #include <stdio.h>

// int	main(void)
// {
// 	const char *test1 = "   -1234";
// 	const char *test2 = "42";
// 	const char *test3 = "   +5678";
// 	const char *test4 = "   2147483647";
// 	const char *test5 = "   -2147483648";
// 	const char *test6 = "   +00001234";
// 	const char *test7 = "   -00001234";
// 	const char *test8 = "   1234abc567";

// 	printf("Test 1: %s -> %d\n", test1, ft_atoi(test1));
// 	printf("Test 2: %s -> %d\n", test2, ft_atoi(test2));
// 	printf("Test 3: %s -> %d\n", test3, ft_atoi(test3));
// 	printf("Test 4: %s -> %d\n", test4, ft_atoi(test4));
// 	printf("Test 5: %s -> %d\n", test5, ft_atoi(test5));
// 	printf("Test 6: %s -> %d\n", test6, ft_atoi(test6));
// 	printf("Test 7: %s -> %d\n", test7, ft_atoi(test7));
// 	printf("Test 8: %s -> %d\n", test8, ft_atoi(test8));

// 	return 0;
// }