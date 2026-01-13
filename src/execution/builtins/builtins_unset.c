/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:33 by alegeber          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:33 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Removes a specific variable node from the linked list environment.
// Handles pointer reconnection to maintain list integrity.
static void	remove_node(t_shell *shell, char *key)
{
	t_list	*curr;
	t_list	*prev;
	int		len;

	curr = shell->env_list;
	prev = NULL;
	len = ft_strlen(key);
	while (curr)
	{
		if (!ft_strncmp(curr->content, key, len)
			&& (((char *)curr->content)[len] == '='
			|| ((char *)curr->content)[len] == '\0'))
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env_list = curr->next;
			ft_lstdelone(curr, free);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

// Removes variables from the environment.
// Iterates through arguments and removes corresponding keys if they exist.
void	builtin_unset(char **args, t_shell *shell)
{
	int	i;

	shell->exit_code = 0;
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] != '\0')
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			shell->exit_code = 1;
			return ;
		}
		remove_node(shell, args[i]);
		i++;
	}
}
