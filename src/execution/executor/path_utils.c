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
#define DEFAULT_PATH "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"
// Helper: Frees the split array used for PATH
// static void	free_paths(char **paths)
// {
// 	int	i;

// 	i = 0;
// 	if (!paths)
// 		return ;
// 	while (paths[i])
// 	{
// 		free(paths[i]);
// 		i++;
// 	}
// 	free(paths);
// }

// Helper: Joins directory + "/" + command and checks access
// static char	*try_path(char *dir, char *cmd)
// {
// 	char	*tmp;
// 	char	*full_path;

// 	tmp = ft_strjoin(dir, "/");
// 	if (!tmp)
// 		return (NULL);
// 	full_path = ft_strjoin(tmp, cmd);
// 	free(tmp);
// 	if (!full_path)
// 		return (NULL);
// 	if (access(full_path, F_OK) == 0)
// 		return (full_path);
// 	free(full_path);
// 	return (NULL);
// }

// Iterates through the split PATH to find the binary.
// static char	*search_in_path(char *cmd, char **paths)
// {
// 	int		i;
// 	char	*valid_path;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		valid_path = try_path(paths[i], cmd);
// 		if (valid_path)
// 			return (valid_path);
// 		i++;
// 	}
// 	return (NULL);
// }

// Main function to resolve command path
// 1. Handle absolute or relative paths (e.g., /bin/ls or ./script.sh)
// 2. Get PATH variable
// 3. Split PATH and search
char	*get_cmd_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

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
