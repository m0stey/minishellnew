/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:52:18 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:25:44 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc_token(t_list **current_raw,
				t_list **clean_tokens, int last_exit_code);

int	word_expander(t_list **clean_tokens,
				char *raw_value, t_list *env_l, int last_exit_code)
{
	t_list	*chunk_list;
	char	*joined_str;
	char	**split_words;
	int		unquoted;

	chunk_list = build_chunks(raw_value, env_l, &unquoted, 1, last_exit_code);
	if (!chunk_list)
		return (0);
	joined_str = join_string_chunks(chunk_list);
	if (!joined_str)
		return (0);
	if (unquoted)
	{
		split_words = ft_split(joined_str, ' ');
		free(joined_str);
		if (!split_words)
			return (0);
		return (add_split_tokens(clean_tokens, split_words));
	}
	else
	{
		if (!add_token(clean_tokens, joined_str, TOKEN_WORD))
			return (free(joined_str), 0);
	}
	return (1);
}

int	clone_token(t_list **clean_tokens, t_token *raw_token)
{
	char	*cloned_value;

	cloned_value = ft_strdup(raw_token->value);
	if (!cloned_value)
		return (0);
	if (!add_token(clean_tokens, cloned_value, raw_token->type))
		return (free(cloned_value), 0);
	return (1);
}

t_list	*expander(t_list *raw_tokens, t_list *env_l, int last_exit_code)
{
	t_list	*clean_tokens;
	t_list	*current_raw;
	int		error_flag;

	clean_tokens = NULL;
	current_raw = raw_tokens;
	error_flag = 1;
	while (current_raw && error_flag)
		error_flag = process_tkn(&current_raw,
				&clean_tokens, env_l, last_exit_code);
	free_token_list(&raw_tokens);
	if (!error_flag)
	{
		free_token_list(&clean_tokens);
		if (g_signal == 0)
			ft_putstr_fd("Error: Expander failed (malloc)\n", 2);
		return (NULL);
	}
	return (clean_tokens);
}

int	process_tkn(t_list **current_raw,
	t_list **clean_tokens, t_list *env_l, int last_exit_code)
{
	t_token	*token;
	t_list	*current;

	current = *current_raw;
	token = (t_token *)current->content;
	if (token->type == TOKEN_HEREDOC)
		return (process_heredoc_token(
				current_raw, clean_tokens, last_exit_code));
	else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND)
		return (process_redir_token(
				current_raw, clean_tokens, env_l, last_exit_code));
	else if (token->type != TOKEN_WORD)
	{
		if (!clone_token(clean_tokens, token))
			return (0);
		*current_raw = current->next;
	}
	else
	{
		if (!word_expander(clean_tokens, token->value, env_l, last_exit_code))
			return (0);
		*current_raw = current->next;
	}
	return (1);
}

static int	process_heredoc_token(t_list **current_raw,
	t_list **clean_tokens, int last_exit_code)
{
	t_list	*current;

	current = *current_raw;
	if (!clone_token(clean_tokens, (t_token *)current->content))
		return (0);
	current = current->next;
	if (!current)
	{
		*current_raw = NULL;
		return (1);
	}
	if (!handle_heredoc(clean_tokens,
			(t_token *)current->content, last_exit_code))
		return (0);
	*current_raw = current->next;
	return (1);
}
