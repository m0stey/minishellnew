/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:26 by alegeber          #+#    #+#             */
/*   Updated: 2026/01/08 17:27:08 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if a string consists entirely
// of digits (handling optional sign).
// Used to validate the exit code argument.
static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Frees all resources held by the shell
// (environment list, etc.) before exiting.
static void	cleanup_shell(t_shell *shell)
{
	if (shell->env_list)
		ft_lstclear(&shell->env_list, free);
}

// Exits the shell with a status code.
// Handles numeric arguments, error checking for
// non-numeric args, and 'too many arguments' errors.
void	builtin_exit(char **args, t_shell *shell)
{
	long long	exit_code;

	ft_putendl_fd("exit", 2);
	if (!args[1])
	{
		cleanup_shell(shell);
		exit(shell->exit_code);
	}
	if (!ft_isnumber(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		cleanup_shell(shell);
		exit(2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_code = 1;
		return ;
	}
	exit_code = ft_atoi(args[1]);
	cleanup_shell(shell);
	exit((unsigned char)exit_code);
}
