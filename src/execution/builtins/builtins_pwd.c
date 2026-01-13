/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:32 by alegeber          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:32 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints the absolute path of the current working directory to standard output.
// Uses getcwd to retrieve the path.
void	builtin_pwd(char **args, t_shell *shell)
{
	char	cwd[1024];

	(void)args;
	(void)shell;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		shell->exit_code = 0;
	}
	else
	{
		perror("pwd");
		shell->exit_code = 1;
	}
}
