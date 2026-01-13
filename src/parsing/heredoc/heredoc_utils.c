/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:38:57 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:25:59 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_expanded_value(char *str, int *i, t_list *env_l, int last_exit_code)
{
	int		length;
	char	*name;
	char	*value;

	if (str[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(last_exit_code));
	}
	length = get_var_name_length(str + *i + 1);
	if (length == 0)
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	name = ft_substr(str, *i + 1, length);
	value = find_var_value(name, env_l);
	free(name);
	*i += length + 1;
	return (value);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*name;

	num = ft_itoa(i++);
	if (!num)
		return (NULL);
	name = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	return (name);
}

char	*expand_heredoc_line(char *line, t_list *env_l, int last_exit_code)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalnum(line[i + 1])
				|| line[i + 1] == '_' || line[i + 1] == '?'))
			result = ft_append_str(result, get_expanded_value(line, &i, env_l, last_exit_code));
		else
		{
			result = ft_append_str(result, ft_substr(line, i, 1));
			i++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}
