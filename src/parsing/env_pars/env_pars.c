/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:11:44 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:30:16 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parse_envp(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	char	*env_str;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		env_str = ft_strdup(envp[i]);
		if (!env_str)
			return (ft_lstclear(&env_list, &free_env_list), NULL);
		new_node = ft_lstnew(env_str);
		if (!new_node)
		{
			free(env_str);
			ft_lstclear(&env_list, &free_env_list);
			return (NULL);
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

char	*find_var_value(char *var_name, t_list *env_l)
{
	char	*env_str;
	size_t	name_len;

	name_len = ft_strlen(var_name);
	while (env_l)
	{
		env_str = (char *)env_l->content;
		if (ft_strncmp(env_str, var_name, name_len) == 0
			&& env_str[name_len] == '=')
			return (ft_strdup(env_str + name_len + 1));
		env_l = env_l->next;
	}
	return (ft_strdup(""));
}

int	handle_var(t_expd *data)
{
	char	*var_value;

	data->i++;
	if (data->raw_val[data->i] == '?')
	{
		var_value = ft_itoa(data->last_exit_code);
		data->i++;
		if (!var_value)
			return (0);
		return (add_new_chunk(data->chunk_l, var_value));
	}
	else
		return (handle_normal_var(data));
}

int	handle_normal_var(t_expd *data)
{
	char	*var_name;
	char	*var_value;
	int		var_name_len;

	var_name_len = get_var_name_length(&data->raw_val[data->i]);
	if (var_name_len == 0)
		return (add_new_chunk(data->chunk_l, ft_strdup("$")));
	var_name = ft_substr(data->raw_val, data->i, var_name_len);
	if (!var_name)
		return (0);
	var_value = find_var_value(var_name, data->env_l);
	free(var_name);
	data->i += var_name_len;
	if (!var_value)
		return (0);
	return (add_new_chunk(data->chunk_l, var_value));
}

char	**env_list_to_array(t_list *env_l)
{
	int		count;
	char	**env_array;
	int		i;
	t_list	*current;

	i = 0;
	count = ft_lstsize(env_l);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_l;
	while (current)
	{
		env_array[i] = ft_strdup((char *)current->content);
		if (!env_array)
			return (free_split(env_array), NULL);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
