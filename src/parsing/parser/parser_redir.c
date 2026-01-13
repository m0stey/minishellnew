/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:54:48 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:25:30 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_redir_type	get_redir_type(t_token_type token_type)
{
	if (token_type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_INPUT);
	if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUTPUT);
	return (REDIR_HEREDOC);
}

static	t_redir	*create_redir_node(t_redir_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	redir->type = type;
	return (redir);
}

int	handle_redirection(t_list **tokens, t_cmd_node *cmd)
{
	t_token		*op_token;
	t_token		*filename;
	t_redir		*redir;
	t_list		*new_list_node;

	op_token = (t_token *)(*tokens)->content;
	*tokens = (*tokens)->next;
	if (!*tokens)
		return (ft_putstr_fd("minishell: syntax error near unexpected token\n", 2), 0);
	filename = (t_token *)(*tokens)->content;
	if (!filename || filename->type != TOKEN_WORD)
		return (ft_putstr_fd("minishell: syntax error near unexpected token\n", 2), 0);
	redir = create_redir_node(get_redir_type(op_token->type), filename->value);
	if (!redir)
		return (0);
	if (op_token->type == TOKEN_HEREDOC && filename->heredoc_quote_flag)
		redir->heredoc_quoted = 1;
	else
		redir->heredoc_quoted = 0;
	new_list_node = ft_lstnew(redir);
	if (!new_list_node)
		return (free_redir(redir), 0);
	ft_lstadd_back(&cmd->redirs, new_list_node);
	*tokens = (*tokens)->next;
	return (1);
}
