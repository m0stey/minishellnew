/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:23:18 by alegeber          #+#    #+#             */
/*   Updated: 2026/01/08 17:28:12 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_in_paths(char *cmd, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_triple_join(paths[i], "/", cmd);
		if (access(full_path, F_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

// Main function to resolve command path
char	*get_cmd_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*path_env;

	if (ft_strchr(cmd, '/') || cmd[0] == '.')
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = ft_getenv(shell->env_list, "PATH");
	if (!path_env)
		path_env = DEFAULT_PATH;
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(cmd, paths));
}
