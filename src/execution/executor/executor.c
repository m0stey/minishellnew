/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:20:27 by alegeber          #+#    #+#             */
/*   Updated: 2026/01/08 15:20:27 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_exec(t_cmd_node *cmd, t_shell *shell)
{
	char		**env;
	char		*path;
	struct stat	st;

	env = convert_env_list_to_array(shell->env_list);
	path = get_cmd_path(cmd->args[0], shell);
	if (!path)
		handle_exec_error(cmd->args[0], env, 127);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		free(path);
		handle_exec_error(cmd->args[0], env, 126);
	}
	execve(path, cmd->args, env);
	ft_putstr_fd("minishell: ", 2);
	perror(cmd->args[0]);
	free(path);
	free_array(env);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

static void	handle_child(t_cmd_node *cmd, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!handle_redirections(cmd->redirs))
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (cmd->args[0][0] == '\0')
	{
		ft_putendl_fd("minishell: : command not found", 2);
		exit(127);
	}
	if (check_builtin(cmd))
	{
		exec_builtin(cmd, shell);
		exit(shell->exit_code);
	}
	child_exec(cmd, shell);
}

// Forks a new process to run an external command.
void	run_external(t_cmd_node *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork failed");
		return ;
	}
	if (pid == 0)
		handle_child(cmd, shell);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, SIG_DFL);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = 128 + WTERMSIG(status);
}

// Orchestrates the execution of a single command node.
void	execute_cmd(t_cmd_node *cmd, t_shell *shell)
{
	int	original_stdin;
	int	original_stdout;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (check_builtin(cmd))
	{
		original_stdin = dup(STDIN_FILENO);
		original_stdout = dup(STDOUT_FILENO);
		if (handle_redirections(cmd->redirs))
			exec_builtin(cmd, shell);
		else
			shell->exit_code = 1;
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
	}
	else
		run_external(cmd, shell);
}

// Main traversal function for the AST.
void	execute_ast(t_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		execute_pipe((t_pipe_node *)node, shell);
	else if (node->type == NODE_CMD)
		execute_cmd((t_cmd_node *)node, shell);
}
