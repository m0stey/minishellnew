/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:30 by alegeber          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:30 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_err(char *arg, int *exit_code)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*exit_code = 1;
}

static int	check_export_option(char *arg, int *exit_code)
{
	if (arg[0] == '-' && arg[1])
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": invalid option", 2);
		*exit_code = 2;
		return (1);
	}
	return (0);
}

// Adds or updates an environment variable.
// Parses the string for '=' to separate key
// and value, or adds as a key-only export.
static void	add_export(char *arg, t_shell *shell)
{
	char	*key;
	char	*eq;
	t_list	*node;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		ft_setenv(&shell->env_list, key, eq + 1);
		free(key);
	}
	else
	{
		node = find_env_node(shell->env_list, arg);
		if (!node)
			ft_setenv_add_new(&shell->env_list, ft_strdup(arg));
	}
}

// Exports variables to the environment.
// If no arguments, prints sorted env.
// Otherwise, validates and adds variables.
void	builtin_export(char **args, t_shell *shell)
{
	int	i;

	shell->exit_code = 0;
	if (!args[1])
	{
		print_sorted_env(shell);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (check_export_option(args[i], &shell->exit_code))
			return ;
		if (!is_valid_identifier(args[i]))
			print_export_err(args[i], &shell->exit_code);
		else
			add_export(args[i], shell);
		i++;
	}
}
