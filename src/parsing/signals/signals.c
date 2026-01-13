/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:10:54 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:26:31 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal_handler(int sig)
{
	(void)sig;
	g_signal = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	handle_sigint_interactive(int sig)
{
	(void)sig;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	print_syntax(char	*token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'", 2);
	return (1);
}

int	redir_signal_handler(t_token *token, t_list *expanded_file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token->value, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	free_token_list(&expanded_file);
	return (1);
}
