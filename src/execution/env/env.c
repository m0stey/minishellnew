/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:36 by alegeber          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:36 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Iterates through envp, duplicates every string into a linked list node.
// This ensures that the shell owns its own data.
t_list	*init_env(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	char	*content;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		content = ft_strdup(envp[i]);
		if (!content)
			return (NULL);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			free(content);
			return (NULL);
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

// Searches a list for a matching key (e.g. $HOME or $PATH )
char	*ft_getenv(t_list *env_list, char *key)
{
	t_list	*node;
	char	*content;
	int		len;

	node = find_env_node(env_list, key);
	if (!node)
		return (NULL);
	content = (char *)node->content;
	len = ft_strlen(key);
	if (content[len] == '=')
		return (content + len + 1);
	return (NULL);
}

// Checks for existing key,
// if found: frees old string, replaces it with new KEY=VALUE string,
// if not found: appends new node to end of list.
void	ft_setenv(t_list **env_list, char *key, char *value)
{
	t_list	*node;
	char	*tmp;
	char	*new_str;

	if (!key || !value)
		return ;
	tmp = ft_strjoin(key, "=");
	new_str = ft_strjoin(tmp, value);
	free(tmp);
	if (!new_str)
		return ;
	node = find_env_node(*env_list, key);
	if (node)
	{
		free(node->content);
		node->content = new_str;
	}
	else
		ft_setenv_add_new(env_list, new_str);
}

// Converts the env linked list into a char** array for execve (syscall)
// to handle before executing external command (e.g ls or grep)
char	**convert_env_list_to_array(t_list *env_list)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env_list)
	{
		arr[i] = ft_strdup((char *)env_list->content);
		env_list = env_list->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
