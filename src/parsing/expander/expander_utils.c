/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:33:25 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:25:47 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_name_length(char *str)
{
	int	length;

	length = 0;
	if (str[0] == '?')
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	length++;
	while (str[length] && (ft_isalnum(str[length]) || str[length] == '_'))
		length++;
	return (length);
}

t_list	*build_chunks(t_expd *data, int *unquoted)
{
	t_list	*chunk_list;

	chunk_list = NULL;
	data->chunk_l = &chunk_list;
	data->i = 0;
	data->start = 0;
	data->quote_char = 0;
	data->in_unquoted = 0;
	while (data->raw_val[data->i])
	{
		if (!process_char_in_chunks(data))
			return (ft_lstclear(&chunk_list, &free), NULL);
	}
	return (finalize_build(data, unquoted));
}

char	*join_string_chunks(t_list *chunk_l)
{
	t_list	*current;
	char	*final_str;
	char	*temp;

	final_str = ft_strdup("");
	if (!final_str)
		return (NULL);
	current = chunk_l;
	while (current)
	{
		temp = final_str;
		final_str = ft_strjoin(temp, (char *)current->content);
		free(temp);
		if (!final_str)
			return (NULL);
		current = current->next;
	}
	ft_lstclear(&chunk_l, &free);
	return (final_str);
}

int	add_split_tokens(t_list **clean_tokens, char **split_words)
{
	int	i;

	i = 0;
	while (split_words[i])
	{
		if (!add_token(clean_tokens, split_words[i], TOKEN_WORD))
		{
			free(split_words[i]);
			free(split_words);
			return (0);
		}
		i++;
	}
	free(split_words);
	return (1);
}

int	handle_heredoc(t_list **clean_tokens,
		t_token *raw_token, int last_exit_code)
{
	t_token	*last_token;
	char	*delimiter;
	int		is_unquoted;
	int		has_quotes;
	t_expd	data;

	has_quotes = 0;
	if (ft_strchr(raw_token->value, '\'') || ft_strchr(raw_token->value, '\"'))
		has_quotes = 1;
	data.raw_val = raw_token->value;
	data.env_l = NULL;
	data.last_exit_code = last_exit_code;
	data.do_expansion = 0;
	delimiter = join_string_chunks(build_chunks(&data, &is_unquoted));
	if (!delimiter)
		return (0);
	if (!add_token(clean_tokens, delimiter, TOKEN_WORD))
	{
		free(delimiter);
		return (0);
	}
	last_token = (t_token *)(ft_lstlast(*clean_tokens)->content);
	last_token->heredoc_quote_flag = has_quotes;
	return (1);
}
