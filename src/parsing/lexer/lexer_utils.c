/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 13:21:13 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:24:43 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (ft_strchr(WHITESPACE, c))
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (ft_strchr(OPERATORS, c))
		return (1);
	return (0);
}

static void	free_token(void *token)
{
	t_token	*temp;

	temp = (t_token *)token;
	if (temp)
	{
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

void	free_token_list(t_list **tokens)
{
	ft_lstclear(tokens, free_token);
}

int	add_token(t_list **tokens, char *value, int type)
{
	t_token	*token;
	t_list	*new_node;

	token = malloc(sizeof(t_token));
	if (!token)
		return (free(value), 0);
	token->value = value;
	token->type = type;
	token->heredoc_quote_flag = 0;
	new_node = ft_lstnew(token);
	if (!new_node)
	{
		free(token);
		free(value);
		return (0);
	}
	ft_lstadd_back(tokens, new_node);
	return (1);
}
