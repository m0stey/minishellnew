/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:59:51 by alegeber          #+#    #+#             */
/*   Updated: 2026/01/08 16:59:51 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

// --- Standard Libraries ---
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <sys/stat.h>

// --- Readline ---
# include <readline/readline.h>
# include <readline/history.h>

// --- Libft ---
# include "../libft/libft.h"

// --- Macros ---
# define WHITESPACE " \t\n\v\f\r"
# define OPERATORS "|<>"

// --- Global Variable ---
extern int	g_signal;

// --- STRUCTURES ---

// --- Enums ---
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_CMD
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

// --- Data Structures ---

// Token (Lexer output)
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				heredoc_quote_flag;
}	t_token;

// Abstract Syntax Tree (AST) Nodes
typedef struct s_node
{
	t_node_type		type;
}	t_node;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	int				heredoc_quoted;
}	t_redir;

typedef struct s_cmd_node
{
	t_node_type		type;
	char			**args;
	t_list			*redirs;
}	t_cmd_node;

typedef struct s_pipe_node
{
	t_node_type		type;
	t_node			*left;
	t_node			*right;
}	t_pipe_node;

// Shell State
typedef struct s_shell
{
	t_list	*env_list;
	int		exit_code;
}	t_shell;

// Expander Utils
typedef struct s_expd
{
	char	*raw_val;
	t_list	**chunk_l;
	t_list	*env_l;
	int		last_exit_code;
	int		i;
	int		start;
	char	quote_char;
	int		in_unquoted;
	int		do_expansion;
}	t_expd;

// --- PROTOTYPES ---

// --- PARSING: Lexer ---
t_list		*lexer(char *line);
int			is_whitespace(char c);
int			is_operator(char c);
int			add_token(t_list **tokens, char *value, int type);
void		free_token_list(t_list **tokens);
void		print_token_list(t_list *tokens);

// --- PARSING: Expander ---
t_list		*expander(t_list *raw_tokens, t_list *env_list, int last_exit_code);
int			process_tkn(t_list **current_raw, t_list **clean_tokens, t_list *env_l, int last_exit_code);
int			word_expander(t_list **clean_tokens, char *raw_value, t_list *env_l, int last_exit_code);
int			clone_token(t_list **clean_tokens, t_token *raw_token);
int			handle_heredoc(t_list **clean_tokens, t_token *raw_token, int last_exit_code);

// Expander Utils
int			get_var_name_length(char *str);
t_list		*build_chunks(char *raw_val, t_list *env_l, int *unquoted, int expand, int last_exit_code);
char		*join_string_chunks(t_list *chunk_list);
int			process_chunks(t_expd *data);
int			add_split_tokens(t_list **clean_tokens, char **split_words);
int			add_new_chunk(t_list **chunk_list, char *content);
int			process_char_in_chunks(t_expd *data);
t_list		*finalize_build(t_expd *data, int *unquoted);

// --- PARSING: Parser ---
t_node		*parser(t_list *tokens, t_shell *shell);
t_cmd_node	*init_cmd_node(void);
t_pipe_node	*init_pipe_node(t_node *left, t_node *right);
int			add_words_to_args(t_cmd_node *cmd, t_token *token);
int			handle_redirection(t_list **tokens, t_cmd_node *cmd);
void		free_parser_ast(t_node *node);
void		free_redir(void *redir);

// --- PARSING: Heredoc ---
int			preprocess_heredocs(t_node *node, t_list *env_l, int last_exit_code);
char		*generate_heredoc_filename(void);
char		*expand_heredoc_line(char *line, t_list *env_l, int last_exit_code);
void		heredoc_signal_handler(int sig);

// --- SIGNALS & SYNTAX ---
void		handle_sigint_interactive(int sig);
int			print_syntax(char *token);
int			check_syntax(t_list *tokens, t_shell *shell);
int			redir_signal_handler(t_token *token, t_list *expanded_file);
t_token		*get_content(t_list *node);
int			process_redir_token(t_list **curr_raw, t_list **clean_tokens, t_list *env_l, int last_exit_code);

// --- ENVIRONMENT ---
t_list		*init_env(char **envp);
char		*ft_getenv(t_list *env_list, char *key);
void		ft_setenv(t_list **env_list, char *key, char *value);
void		ft_setenv_add_new(t_list **env_list, char *new_content);
char		**convert_env_list_to_array(t_list *env_list);
t_list		*find_env_node(t_list *env_list, char *key);
void		free_env_list(void *content);
void		free_env_node(void *content);
void		free_array(char **array);

// Variable Expansion Helpers
char		*find_var_value(char *var_name, t_list *env_l);
int			handle_var(t_expd *data);
int			handle_normal_var(t_expd *data);

// --- EXECUTOR ---
void		execute_ast(t_node *node, t_shell *shell);
void		execute_cmd(t_cmd_node *cmd, t_shell *shell);
void		execute_pipe(t_pipe_node *node, t_shell *shell);
void		run_external(t_cmd_node *cmd, t_shell *shell);
char		*get_cmd_path(char *cmd, t_shell *shell);
int			handle_redirections(t_list *redirs);

// --- BUILTINS ---
void		builtin_echo(char **args, t_shell *shell);
void		builtin_cd(char **args, t_shell *shell);
void		builtin_pwd(char **args, t_shell *shell);
void		builtin_export(char **args, t_shell *shell);
void		builtin_unset(char **args, t_shell *shell);
void		builtin_env(char **args, t_shell *shell);
void		builtin_exit(char **args, t_shell *shell);
int			check_builtin(t_cmd_node *cmd);
void		exec_builtin(t_cmd_node *cmd, t_shell *shell);



// Builtin Utils
int			is_valid_identifier(char *str);
void		print_sorted_env(t_shell *shell);

#endif
