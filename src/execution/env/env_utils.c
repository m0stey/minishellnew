/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:34 by alegeber          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:34 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Traverses the environment list to find the node matching a specific key.
// Returns the node if found, or NULL.
t_list	*find_env_node(t_list *env_list, char *key)
{
	int		len;
	char	*content;

	len = ft_strlen(key);
	while (env_list)
	{
		content = (char *)env_list->content;
		if (!ft_strncmp(content, key, len)
			&& (content[len] == '=' || content[len] == '\0'))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

// Helper function to free the content of a list node.
void	free_env_node(void *content)
{
	free(content);
}

// // Frees the entire environment linked list and its contents.
// void	free_env_list(t_list **env_list)
// {
// 	ft_lstclear(env_list, free_env_node);
// }

// Creates a new node with the given content
// and appends it to the end of the environment list.
void	ft_setenv_add_new(t_list **env_list, char *new_content)
{
	t_list	*new_node;

	new_node = ft_lstnew(new_content);
	if (!new_node)
		return ;
	ft_lstadd_back(env_list, new_node);
}

// Frees a NULL-terminated array of strings (e.g. the array used for execve).
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
