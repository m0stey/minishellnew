/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:14 by alegeber          #+#    #+#             */
/*   Updated: 2026/01/08 17:26:45 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Updates the PWD and OLDPWD environment
// variables after a directory change.
// If getcwd fails, it still attempts
// to update OLDPWD to keep state consistent.
static void	update_env_pwds(t_shell *shell, char *old_pwd)
{
	char	new_pwd[1024];

	if (getcwd(new_pwd, sizeof(new_pwd)))
	{
		ft_setenv(&shell->env_list, "OLDPWD", old_pwd);
		ft_setenv(&shell->env_list, "PWD", new_pwd);
	}
	else
	{
		perror("minishell: cd: error retrieving current directory");
		ft_setenv(&shell->env_list, "OLDPWD", old_pwd);
	}
}

// Resolves the target directory path.
// Returns $HOME if no arguments are provided,
// otherwise returns the first argument.
static char	*get_target_path(char **args, t_shell *shell)
{
	char	*path;

	if (!args[1] || (ft_strncmp(args[1], "--", 3) == 0 && !args[2]))
	{
		path = ft_getenv(shell->env_list, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = ft_getenv(shell->env_list, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (NULL);
		}
		ft_putendl_fd(path, 1);
	}
	else if (ft_strncmp(args[1], "--", 2) == 0)
	{
		path = args[2];
	}
	else
		path = args[1];
	return (path);
}

// Changes the current working directory (chdir syscall).
// Updates environment variables on success and
// handles errors (e.g. permission denied).
void	builtin_cd(char **args, t_shell *shell)
{
	char	*path;
	char	old_pwd[1024];

	shell->exit_code = 1;
	path = get_target_path(args, shell);
	if (!path)
		return ;
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		perror("minishell: cd: error retrieving current directory");
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return ;
	}
	update_env_pwds(shell, old_pwd);
	shell->exit_code = 0;
}
