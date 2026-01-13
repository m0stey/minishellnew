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

static char	**realloc_args_array(char **old_args, char *new_word)
{
	int		i;
	char	**new_args;
	char	*word_copy;

	i = 0;
	if (old_args)
		while (old_args[i])
			i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	if (old_args)
	{
		while (old_args[i])
		{
			new_args[i] = old_args[i];
			i++;
		}
	}
	word_copy = ft_strdup(new_word);
	if (!word_copy)
		return (free(new_args), NULL);
	new_args[i] = word_copy;
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

// int	is_builtin(char *cmd)
// {
// 	if (!cmd)
// 		return (0);
// 	if (ft_strcmp(cmd, "echo") == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "cd") == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "pwd") == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "export") == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "unset") == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "env") == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "exit") == 0)
// 		return (1);
// 	return (0);
// }
