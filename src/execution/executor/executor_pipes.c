/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:52:09 by alegeber          #+#    #+#             */
/*   Updated: 2026/01/08 17:28:02 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_status(pid_t pid[2], t_shell *shell)
{
	int	status;

	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = 128 + WTERMSIG(status);
}

static void	exec_pipe_child(t_node *n, int p[2], t_shell *shell, int left)
{
	if (left)
	{
		close(p[0]);
		if (dup2(p[1], STDOUT_FILENO) == -1)
			exit(1);
		close(p[1]);
	}
		else
	{
		close(p[1]);
		if (dup2(p[0], STDIN_FILENO) == -1)
			exit(1);
		close(p[0]);
	}
	execute_ast(n, shell);
	exit(shell->exit_code);
}

static int	fork_children(t_pipe_node *node, int p[2], t_shell *shell, pid_t *pid)
{
	pid[0] = fork();
	if (pid[0] == -1)
	{
		close(p[0]);
		close(p[1]);
		return (0);
	}
	if (pid[0] == 0)
		exec_pipe_child(node->left, p, shell, 1);

	pid[1] = fork();
	if (pid[1] == -1)
	{
		close(p[0]);
		close(p[1]);
		kill(pid[0], SIGTERM);
		waitpid(pid[0], NULL, 0);
		return (0);
	}
	if (pid[1] == 0)
		exec_pipe_child(node->right, p, shell, 0);
	return (1);
}

void	execute_pipe(t_pipe_node *node, t_shell *shell)
{
	int		p[2];
	pid_t	pid[2];

	if (pipe(p) == -1)
	{
		perror("minishell: pipe");
		shell->exit_code = 1;
		return ;
	}
	if (!fork_children(node, p, shell, pid))
	{
		perror("minishell: fork");
		close(p[0]);
		close(p[1]);
		shell->exit_code = 1;
		return ;
	}
	close(p[0]);
	close(p[1]);
	wait_status(pid, shell);
}
