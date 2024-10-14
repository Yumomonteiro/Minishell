/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:57:03 by yude-oli          #+#    #+#             */
/*   Updated: 2024/10/14 16:19:23 by ada-mata &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define HEREDOC 7
# define END 8

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANSION 36
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

typedef struct s_sig
{
	pid_t			pid;
}				t_sig;
typedef enum s_bool
{
	TRUE,
	FALSE,
}			t_bool;

typedef struct s_env
{
	struct s_env	*next;
	char			var_cpy[1024];
	char			*expanded_value;
	char			*value;
}				t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
	int				quoted;
	char			quote_type;
	int				quote_space;
}				t_token;

typedef struct s_redir
{
	char			*direction;
	char			type[2];
}				t_redir;

typedef struct s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

typedef struct s_msh
{
	t_token			*start;
	t_env			*env;
	t_env			*secret_env;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				parent;
	int				last;
	int				ret;
	int				exit;
}				t_msh;
// BUILTINS
int			ft_pwd(int flag);
int			ft_cd(char **cmd, t_msh *mini);
int			ft_unset(char **a, t_msh *mini);
int			ft_echo(t_msh *mini, char **args);
int			ft_export(char **args, t_env *env, t_env *secret);
int			env_init(t_msh *mini, char **env_array);
int			is_builtin(char *command);
int			ft_export(char **args, t_env *env, t_env *secret);
int			exec_builtin(char **args, t_msh *mini, int flag);
//ENV
int			env_add(const char *value, t_env *env);
int			is_valid_env(const char *env);
int			ft_env(t_env *env);
int			is_sep(char *line, int i);
int			env_init(t_msh *mini, char **env_array);
int			secret_env_init(t_msh *mini, char **env_array);
int			is_valid_env(const char *env);
int			ft_env(t_env *env);
t_env		*rm_env(t_env *env, char *del_env);
t_env		*add_env(char *line, t_env *env);
char		*get_env_name(char *dest, const char *src);
char		*env_to_str(t_env *lst);
char		*get_env_value(char *arg, t_env *env);
char		*get_env_value(char *arg, t_env *env);
char		*get_env_name(char *dest, const char *src);
void		print_sorted_env(t_env *env);
void		print_sorted_env(t_env *env);
void		*ft_memdel(void *ptr);
void		free_env(t_env *env);
//SIGNALS
void		handle_eof(void);
void		handle_sigint(int sig);
void		handle_sigint(int sig);
int			handle_sig_eof(char *line);
void		handle_eof(void);
//PIPES
int			check_path(char **args, t_env *env, t_msh *mini, char *path);
char		*path_join_pipe(const char *s1, const char *s2);
void		pipex_builtin(t_msh *mini, t_token *token);
int			pipex(t_msh *mini, t_token *token);
void		exec_pipe_cmd(t_msh *mini, t_token *token);
void		handle_child_process(int fd_in, t_token *token,
				int pipefd[2], t_msh *mini);
void		setup_child_process(int fd_in, t_token *token,
				int pipefd[2], t_msh *mini);
int			is_type(t_token *token, int type);
int			search_pipe(t_token *token);
char		**env_list_to_array(struct s_env *env_list);
//RESET AND CLOSE
void		reset_std(t_msh *mini);
void		close_fds(t_msh *mini);
void		reset_fds(t_msh *mini);
void		cleanup(t_msh *mini);
void		exit_error(void);
//EXEC
void		exec_cmd(t_msh *mini, t_token *token);
t_token		*skip_cmd(t_token *tmp);
t_token		*get_tokens(char *line, t_env *env, int ret);
t_token		*next_run(t_token *token, int skip);
t_token		*execute_command_or_pipe(t_msh *mini, t_token *token, t_token *tmp);
char		*find_executable(char *cmd, t_env *env);
int			count_args(t_token *token);
char		**cmd_tab(t_token *start);
void		check_type(t_msh *mini);
int			execute(char *path, char **args, t_env *env, t_msh *mini);
void		exec_cmd(t_msh *mini, t_token *token);
void		free_tab(char **tab);
char		**cmd_tab(t_token *start);
int			exec(char **args, t_env *env, t_msh *mini);
int			handle_special_tokens(t_msh *mini, t_token *tmp);
void		process_tokens(t_msh *mini);
void		minishell(t_msh *mini);
t_token		*next_run(t_token *token, int skip);
void		mini_exit(t_msh *mini, char **cmd);
void		free_token(t_token *start);
void		ft_close(int fd);
void		shell_lvl(t_env *env);
void		ft_skip_whitespaces(const char *str, int *i);
void		shell_level(t_env *env);
//REDIR
int			search_redir(t_token *token);
void		redir_builtin(char **cmd, t_msh *mini, t_token *token);
int			input(t_msh *mini, t_token *token);
int			redir(t_msh *mini, t_token *token);
int			heredoc(t_msh *mini, t_token *token);
//PARSE
int			check_args(char **args, t_token *token);
int			ignore_sep(char *line, int i);
int			quotes(char *line, int index);
void		type_arg(t_token *token, int separator);
void		handle_escapes(char *line, char *temp,
				int *j, int *i);
void		handle_variable_expansion(char **params, t_env *env,
				int *indices, int ret);
void		ft_skip_space(const char *str, int *i);
int			parse(t_msh *mini);
void		*ft_memdel(void *ptr);
void		type_arg(t_token *token, int separator);
void		handle_word_deliminator(char *c, int *i, char *line);
int			quotes(char *line, int index);
int			is_env_char(int c);
int			ret_size(int ret);
int			next_alloc(char *line, int *i);
int			quotes(char *line, int index);
int			is_type(t_token *token, int type);
int			quote_check(t_msh *mini, char **line);
int			get_var_len(const char *arg, int pos, t_env *env, int ret);
int			arg_alloc_len(const char *arg, t_env *env, int ret);
int			is_sep(char *line, int i);
int			ignore_sep(char *line, int i);
int			quotes(char *line, int index);
int			ft_strcmp(const char *s1, const char *s2);
void		type_arg(t_token *token, int separator);
int			is_env_char(int c);
char		*expansions(char *arg, t_env *env, int ret);
int			quotes(char *line, int index);
int			ft_strcmp(const char *s1, const char *s2);
void		free_tokens(t_token *token);
void		free_all(t_msh *mini);
void		exit_cleanup(char *s1, char **s2, char **s3);
void		mini_clean(t_msh *mini);
#endif