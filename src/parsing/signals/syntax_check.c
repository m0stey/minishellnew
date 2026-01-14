/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:46:46 by tbylund           #+#    #+#             */
/*   Updated: 2025/11/27 16:07:20 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_redirection(t_token_type type);
static int	check_token_rules(t_list *current, t_token *token);

t_token	*get_content(t_list *node)
{
	if (!node)
		return (NULL);
	return ((t_token *)node->content);
}

static	int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

int	check_syntax(t_list *tokens, t_shell *shell)
{
	t_list	*current;
	t_list	*last;

	current = tokens;
	if (current && get_content(current)->type == TOKEN_PIPE)
	{
		shell->exit_code = 2;
		return (print_syntax("|"));
	}
	while (current)
	{
		if (check_token_rules(current, get_content(current)))
		{
			shell->exit_code = 2;
			return (1);
		}
		current = current->next;
	}
	last = ft_lstlast(tokens);
	if (last && get_content(last)->type == TOKEN_PIPE)
	{
		shell->exit_code = 2;
		return (print_syntax("|"));
	}
	return (0);
}

static int	check_token_rules(t_list *current, t_token *token)
{
	t_token	*next_token;

	next_token = get_content(current->next);
	if (token->type == TOKEN_PIPE)
	{
		if (!next_token || next_token->type == TOKEN_PIPE)
			return (print_syntax("|"));
	}
	else if (is_redirection(token->type))
	{
		if (!next_token)
			return (print_syntax("newline"));
		if (is_redirection(next_token->type)
			|| next_token->type == TOKEN_PIPE)
			return (print_syntax(next_token->value));
	}
	return (0);
}

int	process_redir_token(t_list **curr_raw, t_list **clean_tokens,
	t_list *env_l, int last_exit_code)
{
	t_list	*current;
	t_list	*expanded_file;
	t_token	*raw_file;

	current = *curr_raw;
	if (!clone_token(clean_tokens, (t_token *)current->content))
		return (0);
	current = current->next;
	if (!current)
		return (*curr_raw = NULL, 1);
	expanded_file = NULL;
	raw_file = (t_token *)current->content;
	if (!word_expander(&expanded_file, raw_file->value, env_l, last_exit_code))
		return (0);
	if (ft_lstsize(expanded_file) != 1)
	{
		redir_signal_handler(raw_file, expanded_file);
		free_token_list(&expanded_file);
		return (0);
	}
	ft_lstadd_back(clean_tokens, expanded_file);
	*curr_raw = current->next;
	return (1);
}
