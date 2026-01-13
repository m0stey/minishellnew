/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:40:04 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/23 17:05:29 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_revstring(char *string, size_t num_count, int n, int if_negative)
{
	size_t	i;

	i = num_count;
	if (if_negative == 1)
	{
		string[0] = '-';
		n = -n;
	}
	while (i > 0)
	{
		string[i + if_negative - 1] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	string[num_count + if_negative] = '\0';
}

char	*ft_itoa(int n)
{
	int		if_negative;
	size_t	number_count;
	char	*string;
	int		store_n;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	store_n = n;
	if_negative = (n < 0);
	number_count = 0;
	if (n < 0)
		store_n = -store_n;
	while (store_n != 0)
	{
		store_n = store_n / 10;
		number_count++;
	}
	string = (char *)malloc(number_count + 1 + if_negative);
	if (string == NULL)
		return (NULL);
	ft_revstring(string, number_count, n, if_negative);
	return (string);
}
