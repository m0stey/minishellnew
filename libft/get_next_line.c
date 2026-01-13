/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:49:39 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/10 17:42:44 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Simple, frees the static char and the buffer.
char	*free_all_values(char **save_value)
{
	if (save_value && *save_value)
	{
		free (*save_value);
		*save_value = NULL;
	}
	return (NULL);
}

char	*combine_all_values(char **save_value, char *buffer)
{
	char	*temp;

	if (*save_value == NULL)
	{
		*save_value = ft_strdup(buffer);
		if (*save_value == NULL)
			return (NULL);
	}
	else
	{
		temp = *save_value;
		*save_value = ft_strjoin(temp, buffer);
		free(temp);
		if (*save_value == NULL)
			return (NULL);
	}
	return (*save_value);
}

//Reads into the buffer, checks if EoF or error, combines values.
char	*fill_line_buffer(int fd, char **save_value)
{
	int		total_bytes;
	char	buffer[BUFFER_SIZE +1];

	while (1)
	{
		total_bytes = read(fd, buffer, BUFFER_SIZE);
		if (total_bytes < 0)
			return (free_all_values(save_value));
		if (total_bytes == 0)
			break ;
		buffer[total_bytes] = '\0';
		if (combine_all_values(save_value, buffer) == NULL)
			return (NULL);
		if (ft_strchr(*save_value, '\n'))
			break ;
	}
	return (*save_value);
}

//
char	*find_new_line(char **save_value)
{
	char	*new_line_pos;
	char	*type_value;
	char	*temp;

	if (*save_value == NULL || **save_value == '\0')
		return (free_all_values(save_value));
	new_line_pos = ft_strchr(*save_value, '\n');
	if (new_line_pos != NULL)
	{
		type_value = ft_substr(*save_value, 0, new_line_pos - *save_value + 1);
		if (type_value == NULL)
			return (free_all_values(save_value));
		temp = *save_value;
		*save_value = ft_strdup(new_line_pos + 1);
		free (temp);
		return (type_value);
	}
	else
	{
		type_value = ft_strdup(*save_value);
		if (type_value == NULL)
			return (free_all_values(save_value));
		free_all_values(save_value);
		return (type_value);
	}
}

char	*get_next_line(int fd)
{
	static char	*save_value;
	char		*type_value;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fill_line_buffer(fd, &save_value) == NULL)
		return (NULL);
	type_value = find_new_line(&save_value);
	return (type_value);
}

// int main()
// {
//     int fd;
//     char *str;

//     fd = open("test.txt", O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return (1);
//     }
//     while ((str = get_next_line(fd)) != NULL)
//     {
//         printf("%s", str);
//         free(str);
//     }
//     close(fd);
//     return (0);
// }