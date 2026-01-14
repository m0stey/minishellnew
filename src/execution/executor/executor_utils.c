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
int	handle_redirections(t_list *redirs)
{
	t_list	*tmp;
	t_redir	*redir;

	tmp = redirs;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		if (!apply_redir(redir))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	handle_exec_error(char *path, char **env_array, int code)
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

	c = cmd->args[0];
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
