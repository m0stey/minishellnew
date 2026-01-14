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

static void	handle_error(char *path, char **env_array, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (code == 126)
		ft_putendl_fd(": Is a directory", 2);
	else if (code == 127)
	{
		if (ft_strchr(path, '/'))
			ft_putendl_fd(": No such file or directory", 2);
		else
			ft_putendl_fd(": command not found", 2);
	}
	if (env_array)
		free_array(env_array);
	exit(code);
}

static void	handle_child(t_cmd_node *cmd, t_shell *shell)
{
	char		**env;
	char		*path;
	struct stat	st;

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
	env = convert_env_list_to_array(shell->env_list);
	path = get_cmd_path(cmd->args[0], shell);
	if (!path)
		handle_error(cmd->args[0], env, 127);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		free(path);
		handle_error(path, env, 126);
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

// Checks if the command is a builtin.
int	check_builtin(t_cmd_node *cmd)
{
	char	*c;

	if (!cmd->args || !cmd->args[0])
		return (0);
	c = cmd->args[0];
	if (!ft_strncmp(c, "echo", 5) || !ft_strncmp(c, "cd", 3)
		|| !ft_strncmp(c, "pwd", 4) || !ft_strncmp(c, "export", 7)
		|| !ft_strncmp(c, "unset", 6) || !ft_strncmp(c, "env", 4)
		|| !ft_strncmp(c, "exit", 5))
		return (1);
	return (0);
}

void	exec_builtin(t_cmd_node *cmd, t_shell *shell)
{
	char	*c;

	*c = cmd->args[0];
	if (!ft_strncmp(c, "echo", 5))
		builtin_echo(cmd->args, shell);
	else if (!ft_strncmp(c, "cd", 3))
		builtin_cd(cmd->args, shell);
	else if (!ft_strncmp(c, "pwd", 4))
		builtin_pwd(cmd->args, shell);
	else if (!ft_strncmp(c, "export", 7))
		builtin_export(cmd->args, shell);
	else if (!ft_strncmp(c, "unset", 6))
		builtin_unset(cmd->args, shell);
	else if (!ft_strncmp(c, "env", 4))
		builtin_env(cmd->args, shell);
	else if (!ft_strncmp(c, "exit", 5))
		builtin_exit(cmd->args, shell);
}

// Orchestrates the execution of a single command node.
// Uses save/restore logic for builtins to avoid corrupting parent FDs.
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
		{
			exec_builtin(cmd, shell);
		}
		else
		{
			shell->exit_code = 1;
		}
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
	}
	else
	{
		run_external(cmd, shell);
	}
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
