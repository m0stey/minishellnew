/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:00:22 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:25:28 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**realloc_args_array(char **old_args, char *new_word);

t_cmd_node	*init_cmd_node(void)
{
	t_cmd_node	*cmd;

	cmd = malloc(sizeof(t_cmd_node));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_CMD;
	cmd->args = NULL;
	cmd->redirs = NULL;
	return (cmd);
}

int	add_words_to_args(t_cmd_node *cmd, t_token *token)
{
	char	**new_args;

	new_args = realloc_args_array(cmd->args, token->value);
	if (!new_args)
		return (0);
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	return (1);
}

static char	**allocate_new_array(char **old_args, int *count)
{
	int		i;
	char	**new_args;

	i = 0;
	if (old_args)
		while (old_args[i])
			i++;
	*count = i;
	new_args = malloc(sizeof(char *) * (i + 2));
	return (new_args);
}

static char	**realloc_args_array(char **old_args, char *new_word)
{
	int		i;
	char	**new_args;

	new_args = allocate_new_array(old_args, &i);
	if (!new_args)
		return (NULL);
	if (old_args)
		ft_memcpy(new_args, old_args, sizeof(char *) * i);
	new_args[i] = ft_strdup(new_word);
	if (!new_args[i])
	{
		free(new_args);
		return (NULL);
	}
	new_args[i + 1] = NULL;
	return (new_args);
}

t_pipe_node	*init_pipe_node(t_node *left, t_node *right)
{
	t_pipe_node	*pipe;

	pipe = malloc(sizeof(t_pipe_node));
	if (!pipe)
		return (NULL);
	pipe->type = NODE_PIPE;
	pipe->left = left;
	pipe->right = right;
	return (pipe);
}
