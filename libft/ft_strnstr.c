/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:34:50 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/20 20:46:07 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		{
			j = 0;
			while (little[j] != '\0' && i + j < len && big[i + j] == little[j])
				j++;
		}
		if (little[j] == '\0')
		{
			return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
// int	main(void)
// {
// 	const char	*big = "Hello, this is a simple string for testing.";
// 	const char	*little1 = "simple";
// 	const char	*little2 = "world";
// 	const char	*little3 = "";
// 	size_t		len = 30;

// 	printf("Test 1 - Looking for 'simple' in 'big':\n");
// 	char *result1 = ft_strnstr(big, little1, len);
// 	if (result1 != NULL)
// 		printf("Found: %s\n", result1);
// 	else
// 		printf("Not found.\n");

// 	printf("Test 2 - Looking for 'world' in 'big':\n");
// 	char *result2 = ft_strnstr(big, little2, len);
// 	if (result2 != NULL)
// 		printf("Found: %s\n", result2);
// 	else
// 		printf("Not found.\n");

// 	printf("Test 3 - Looking for an empty string in 'big':\n");
// 	char *result3 = ft_strnstr(big, little3, len);
// 	if (result3 != NULL)
// 		printf("Found: %s\n", result3);
// 	else
// 		printf("Not found.\n");

// 	printf("Test 4 - Looking for 'simple' in 'big' with len = 5:\n");
// 	char *result4 = ft_strnstr(big, little1, 5);
// 	if (result4 != NULL)
// 		printf("Found: %s\n", result4);
// 	else
// 		printf("Not found.\n");

// 	return 0;
// }
