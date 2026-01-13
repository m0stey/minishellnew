/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:16:53 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:26:02 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expand_delim_str(char *delim, t_list *env)
{
	char	*val;

	if (delim[0] == '$' && delim[1])
	{
		val = ft_getenv(env, delim + 1);
		if (val)
			return (ft_strdup(val));
		return (ft_strdup("")); 
	}
	return (ft_strdup(delim));
}

static void	read_input_loop(int fd, char *delimiter, int expand, t_list *env_l, int last_exit_code)
{
	char	*line;
	int		stdin_backup;
	char	*expanded_line;

	stdin_backup = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_signal_handler);
	while (1)
	{
		line = readline("> ");
		if (g_signal == 130 || !line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (expand)
		{
			expanded_line = expand_heredoc_line(line, env_l, last_exit_code);
			free(line);
			line = expanded_line;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
}

static int	process_single_heredoc(t_redir *redir, t_list *env_l, int last_exit_code)
{
	char	*tmp;
	int		fd;
	char	*real_delimiter;

	tmp = generate_heredoc_filename();
	if (!tmp)
		return (0);
	fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (free(tmp), 0);
	if (!redir->heredoc_quoted && ft_strchr(redir->filename, '$'))
		real_delimiter = expand_delim_str(redir->filename, env_l);
	else
		real_delimiter = ft_strdup(redir->filename);
	read_input_loop(fd, real_delimiter, !redir->heredoc_quoted, env_l, last_exit_code);
	close(fd);
	if (g_signal == 130)
	{
		unlink(tmp);
		return (free(tmp), 0);
	}
	free(redir->filename);
	free(real_delimiter);
	redir->filename = tmp;
	redir->type = REDIR_INPUT;
	return (1);
}

static int	process_cmd_redirs(t_cmd_node *cmd, t_list *env_l, int last_exit_code)
{
	t_list	*current;
	t_redir	*redir;

	current = cmd->redirs;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->type == REDIR_HEREDOC)
			if (!process_single_heredoc(redir, env_l, last_exit_code))
				return (0);
		current = current->next;
	}
	return (1);
}

int	preprocess_heredocs(t_node *node, t_list *env_l, int last_exit_code)
{
	t_pipe_node	*pipe;

	if (!node)
		return (1);
	if (node->type == NODE_PIPE)
	{
		pipe = (t_pipe_node *)node;
		if (!preprocess_heredocs(pipe->left, env_l, last_exit_code)
			|| !preprocess_heredocs(pipe->right, env_l, last_exit_code))
			return (0);
	}
	else if (node->type == NODE_CMD)
	{
		if (!process_cmd_redirs((t_cmd_node *)node, env_l, last_exit_code))
			return (0);
	}
	return (1);
}
