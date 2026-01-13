/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:19 by alegeber          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:19 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	is_n_flag(char *arg)
// {
// 	int	i;

// 	if (!arg || ft_strncmp(arg, "-n", 2) != 0)
// 		return (0);
// 	i = 1;
// 	while (arg[i])
// 	{
// 		if (arg[i] != 'n')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

void	builtin_echo(char **args, t_shell *shell)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	shell->exit_code = 0;
}
