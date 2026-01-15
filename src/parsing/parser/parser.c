/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:00:09 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:25:24 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		peek_token_type(t_list *tokens);
static t_node	*parse_pipe(t_list **tokens);
static t_node	*parse_commands(t_list **tokens);
static t_node	*syntax_error_null(t_node *left, char *msg);

t_node	*parser(t_list *tokens, t_shell *shell)
{
	t_list	*current;
	t_node	*ast;

	current = tokens;
	if (!current)
		return (NULL);
	ast = parse_pipe(&current);
	if (!ast)
	{
		shell->exit_code = 2;
		return (NULL);
	}
	if (current)
	{
		ft_putstr_fd("minishell: Syntax error (unexpected token)\n", 2);
		free_parser_ast(ast);
		shell->exit_code = 2;
		return (NULL);
	}
	return (ast);
}

static t_node	*syntax_error_null(t_node *left, char *msg)
{
	ft_putstr_fd(msg, 2);
	free_parser_ast(left);
	return (NULL);
}

static t_node	*parse_pipe(t_list **tokens)
{
	t_node	*left;
	t_node	*right;

	left = parse_commands(tokens);
	if (!left)
		return (NULL);
	if (peek_token_type(*tokens) == TOKEN_PIPE)
	{
		if (is_empty_cmd(left))
			return (syntax_error_null(left,
					"Minishell: Syntax error near unexpected token | \n"));
		*tokens = (*tokens)->next;
		if (!*tokens || peek_token_type(*tokens) == TOKEN_PIPE)
			return (syntax_error_null(left,
					"minishell: Syntax error (double pipe)\n"));
		right = parse_pipe(tokens);
		if (!right)
			return (free_parser_ast(left), NULL);
		return ((t_node *)init_pipe_node(left, right));
	}
	return (left);
}

static	t_node	*parse_commands(t_list **tokens)
{
	t_cmd_node	*cmd;
	int			token_type;

	cmd = init_cmd_node();
	if (!cmd)
		return (NULL);
	while (*tokens)
	{
		token_type = peek_token_type(*tokens);
		if (token_type == TOKEN_PIPE)
			break ;
		else if (token_type == TOKEN_WORD)
		{
			if (!add_words_to_args(cmd, (t_token *)(*tokens)->content))
				return (free_parser_ast((t_node *)cmd), NULL);
			*tokens = (*tokens)->next;
		}
		else
		{
			if (!handle_redirection(tokens, cmd))
				return (free_parser_ast((t_node *)cmd), NULL);
		}
	}
	return ((t_node *)cmd);
}

static int	peek_token_type(t_list *tokens)
{
	if (!tokens)
		return (-1);
	return (((t_token *)tokens->content)->type);
}
