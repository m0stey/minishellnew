/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:04:22 by tbylund           #+#    #+#             */
/*   Updated: 2026/01/08 17:41:49 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static char	*get_user_input(void)
{
	char	*line;
	char	*tmp;

	if (isatty(STDIN_FILENO))
		return (readline("minishell$ "));
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	tmp = ft_strtrim(line, "\n");
	free(line);
	return (tmp);
}

static void	execute_and_cleanup(t_node *ast, t_shell *shell)
{
	if (preprocess_heredocs(ast, shell->env_list, shell->exit_code))
		execute_ast(ast, shell);
	free_parser_ast(ast);
}

static void	process_line(char *line, t_shell *shell)
{
	t_list	*tokens;
	t_list	*clean_tokens;
	t_node	*ast;

	tokens = lexer(line);
	if (!tokens)
		return ;
	if (check_syntax(tokens, shell))
	{
		shell->exit_code = 2;
		free_token_list(&tokens);
		return ;
	}
	clean_tokens = expander(tokens, shell->env_list, shell->exit_code);
	if (!clean_tokens)
	{
		shell->exit_code = 0;
		return ;
	}
	ast = parser(clean_tokens, shell);
	free_token_list(&clean_tokens);
	if (!ast)
		return ;
	execute_and_cleanup(ast, shell);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, handle_sigint_interactive);
		signal(SIGQUIT, SIG_IGN);
		line = get_user_input();
		if (g_signal != 0)
		{
			shell->exit_code = 128 + g_signal;
			g_signal = 0;
		}
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (*line)
		{
			if (isatty(STDIN_FILENO))
				add_history(line);
			process_line(line, shell);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.exit_code = 0;
	shell.env_list = init_env(envp);
	if (!shell.env_list)
		return (1);
	shell_loop(&shell);
	ft_lstclear(&shell.env_list, free);
	return (shell.exit_code);
}
