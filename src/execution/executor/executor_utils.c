/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:12:31 by alegeber          #+#    #+#             */
/*   Updated: 2026/01/08 17:28:04 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Opens specific file based on redir type,
// swaps shell's standard input/output for
// that file using dup2.
static int	apply_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_INPUT)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == REDIR_OUTPUT)
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->filename);
		return (0);
	}
	if (redir->type == REDIR_INPUT)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	return (close(fd), 1);
}

// Iterates through list of redirections for current cmd
// and applies them in order.
// Returns 1 on success, 0 on failure
int handle_redirections(t_list *redirs)
{
	t_list *tmp;
	t_redir *redir;

	tmp = redirs;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		//TODO implement helper
		if (!apply_redir(redir))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
