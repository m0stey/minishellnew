/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:37:03 by tbylund           #+#    #+#             */
/*   Updated: 2025/11/12 18:11:20 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **result_array)
{
	size_t	i;

	i = 0;
	if (result_array == NULL)
		return ;
	while (result_array[i])
	{
		free(result_array[i]);
		i++;
	}
	free(result_array);
}

static int	count_words(char const *s, char c)
{
	size_t	word_count;
	size_t	i;

	if (s == NULL)
		return (0);
	word_count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			word_count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (word_count);
}

static char	*get_next_word(const char *s, size_t *i, char c)
{
	size_t	start;
	size_t	length;
	char	*word;

	start = 0;
	length = 0;
	while (s[*i] == c && s[*i] != '\0')
		(*i)++;
	start = *i;
	while (s[*i] != c && s[*i] != '\0')
	{
		length++;
		(*i)++;
	}
	word = malloc((length + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	ft_memcpy(word, &s[start], length);
	word[length] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result_array;
	size_t	i;
	size_t	word_index;
	size_t	word_count;

	i = 0;
	word_index = 0;
	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	result_array = malloc((word_count + 1) * sizeof(char *));
	if (result_array == NULL)
		return (NULL);
	while (word_index < word_count)
	{
		result_array[word_index] = get_next_word(s, &i, c);
		if (result_array[word_index] == NULL)
		{
			free_split(result_array);
			return (NULL);
		}
		word_index++;
	}
	result_array[word_index] = NULL;
	return (result_array);
}
