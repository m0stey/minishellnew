/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:22 by alegeber          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:22 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints all environment variables that have a value assigned.
// Variables without an '=' (exported but empty) are ignored.
void	builtin_env(char **args, t_shell *shell)
{
	t_list	*curr;

	(void)args;
	curr = shell->env_list;
	while (curr)
	{
		if (ft_strchr((char *)curr->content, '='))
			ft_putendl_fd((char *)curr->content, 1);
		curr = curr->next;
	}
	shell->exit_code = 0;
}
