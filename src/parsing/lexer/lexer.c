/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:51:36 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:25:00 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_status(char c, char *quote_char)
{
	if (*quote_char == 0 && (c == '\'' || c == '\"'))
		*quote_char = c;
	else if (*quote_char == c)
		*quote_char = 0;
}

static int	handle_word(char **line, t_list **tokens)
{
	char	*start;
	char	*value;
	int		len;
	char	quote_char;

	len = 0;
	quote_char = 0;
	start = *line;
	while (start[len])
	{
		update_quote_status(start[len], &quote_char);
		if (quote_char == 0 && (is_whitespace(start[len])
				|| is_operator(start[len])))
			break ;
		len++;
	}
	value = ft_substr(start, 0, len);
	if (!value)
		return (0);
	if (!add_token(tokens, value, TOKEN_WORD))
		return (free(value), 0);
	*line = start + len;
	return (1);
}

static int	create_op(char **line, t_list **tokens, char*val, t_token_type type)
{
	char	*op;

	op = ft_strdup(val);
	if (!op || !add_token(tokens, op, type))
	{
		free(op);
		return (0);
	}
	*line += ft_strlen(val);
	return (1);
}

static int	handle_operators(char **line, t_list **tokens)
{
	if (**line == '>' && *(*line + 1) == '>')
		return (create_op(line, tokens, ">>", TOKEN_APPEND));
	if (**line == '<' && *(*line + 1) == '<')
		return (create_op(line, tokens, "<<", TOKEN_HEREDOC));
	if (**line == '>')
		return (create_op(line, tokens, ">", TOKEN_REDIR_OUT));
	if (**line == '<')
		return (create_op(line, tokens, "<", TOKEN_REDIR_IN));
	if (**line == '|')
		return (create_op(line, tokens, "|", TOKEN_PIPE));
	return (1);
}

t_list	*lexer(char *line)
{
	t_list	*tokens;
	int		error_flag;

	tokens = NULL;
	error_flag = 1;
	while (*line && error_flag)
	{
		if (is_whitespace(*line))
			line++;
		else if (is_operator(*line))
			error_flag = handle_operators(&line, &tokens);
		else
			error_flag = handle_word(&line, &tokens);
	}
	if (!error_flag)
	{
		free_token_list(&tokens);
		ft_putstr_fd("Error: Lexer failure (malloc)\n", 2);
		return (NULL);
	}
	return (tokens);
}
