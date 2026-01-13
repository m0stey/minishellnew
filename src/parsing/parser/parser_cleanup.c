/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:00:33 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:25:34 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(void *content)
{
	t_redir *redir;

	redir = (t_redir *)content;
	if (!redir)
		return ;
	if (redir->filename)
	{

		if (redir->type == REDIR_INPUT && access(redir->filename, F_OK) == 0)
		{
			if (ft_strnstr(redir->filename, "sh-thd-", ft_strlen(redir->filename)))
				unlink(redir->filename);
		}
		free(redir->filename);
	}
	free(redir);
}

static void	free_str_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_parser_ast(t_node *node)
{
	t_pipe_node	*pipe;
	t_cmd_node	*cmd;

	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
	{
		pipe = (t_pipe_node *)node;
		free_parser_ast(pipe->left);
		free_parser_ast(pipe->right);
	}
	if (node->type == NODE_CMD)
	{
		cmd = (t_cmd_node *)node;
		free_str_array(cmd->args);
		ft_lstclear(&cmd->redirs, &free_redir);
	}
	free (node);
}

void	free_env_list(void *content)
{
	free(content);
}
