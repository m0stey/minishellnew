/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:35:27 by alegeber          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:27 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Validates variable names for export.
// Must start with letter/underscore
// and contain only alphanumerics/underscore.
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// Sorts an array of environment strings alphabetically.
// Used for the 'export' command output when no arguments are provided.
static void	sort_env(char **arr, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j]) + 1) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// Displays environment variables in alphabetical order,
// prefixed with 'declare -x'.
// Converts the list to an array, sorts it, prints it, then frees the array.
void	print_sorted_env(t_shell *shell)
{
	char	**arr;
	int		i;

	arr = convert_env_list_to_array(shell->env_list);
	if (!arr)
		return ;
	sort_env(arr, ft_lstsize(shell->env_list));
	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(arr[i], 1);
		i++;
	}
	free_array(arr);
}
