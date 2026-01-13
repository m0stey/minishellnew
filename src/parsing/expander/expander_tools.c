/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:47:39 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:25:50 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_text_chunk(t_expd *data);
static int	handle_dollar_sign(t_expd *data);

t_list	*finalize_build(t_expd *data, int *unquoted)
{
	if (data->quote_char)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		ft_lstclear(data->chunk_l, &free);
		return (NULL);
	}
	if (data->i > data->start)
	{
		if (!add_new_chunk(data->chunk_l,
				ft_substr(data->raw_val, data->start, data->i - data->start)))
			return (ft_lstclear(data->chunk_l, &free), NULL);
	}
	*unquoted = data->in_unquoted;
	if (*data->chunk_l == NULL)
		return (ft_lstnew(ft_strdup("")));
	return (*data->chunk_l);
}

static int	handle_dollar_sign(t_expd *data)
{
	if (data->quote_char == 0)
		data->in_unquoted = 1;
	if (!add_text_chunk(data))
		return (0);
	if (!handle_var(data))
		return (0);
	data->start = data->i;
	return (1);
}

static int	add_text_chunk(t_expd *data)
{
	char	*chunk;

	if (data->i > data->start)
	{
		chunk = ft_substr(data->raw_val, data->start, data->i - data->start);
		if (!chunk)
			return (0);
		if (!add_new_chunk(data->chunk_l, chunk))
			return (0);
	}
	return (1);
}

int	add_new_chunk(t_list **chunk_list, char *content)
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	if (!new_node)
	{
		free(content);
		return (0);
	}
	ft_lstadd_back(chunk_list, new_node);
	return (1);
}

//If enter quote
//If exit quote
//If $ and not in '' and do_expansion
//Else just move forward
int	process_char_in_chunks(t_expd *data)
{
	char	c;

	c = data->raw_val[data->i];
	if (!data->quote_char && (c == '\'' || c == '"'))
	{
		if (!add_text_chunk(data))
			return (0);
		data->quote_char = c;
		data->start = data->i + 1;
		data->i++;
	}
	else if (data->quote_char && c == data->quote_char)
	{
		if (!add_text_chunk(data))
			return (0);
		data->quote_char = 0;
		data->start = data->i + 1;
		data->i++;
	}
	else if (c == '$' && data->quote_char != '\'' && data->do_expansion)
		return (handle_dollar_sign(data));
	else
		data->i++;
	return (1);
}
