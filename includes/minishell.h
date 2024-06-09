/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:57:03 by yude-oli          #+#    #+#             */
/*   Updated: 2024/06/06 20:21:41 by marvin           ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

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

 typedef enum s_bool
 {
    TRUE,
    FALSE,
 } t_bool;

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
	int             quoted;
	char            quote_type;
}				t_token;

typedef struct s_redir
{
	char			*direction;
	char			type[2];
}				t_redir;

typedef struct	s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

typedef struct	s_msh
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
	int				pid;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
}				t_msh;

int			ft_unset(char **a, t_msh *mini);
int			ft_echo(char **args);
int			ft_export(char **args, t_env *env, t_env *secret);
int			env_init(t_msh *mini, char **env_array);
char		*get_env_value(char *arg, t_env *env);
void		print_sorted_env(t_env *env);
void		*ft_memdel(void *ptr);
int			is_sep(char *line, int i);
int			ignore_sep(char *line, int i);
int			quotes(char *line, int index);
t_token		*get_tokens(char *line);
int			exec_builtin(char **args, t_msh *mini);
int			ft_strcmp(const char *s1, const char *s2);
void		free_env(t_env *env);
char		*get_env_name(char *dest, const char *src);
char		*env_to_str(t_env *lst);
int		is_valid_env(const char *env);
int		ft_env(t_env *env);
int		is_builtin(char *command);
void exec_cmd(t_msh *mini, t_token *token);
void	free_tab(char **tab);
char	**cmd_tab(t_token *start);
void	type_arg(t_token *token, int separator);
int		is_env_char(int c);
char			*expansions(char *arg, t_env *env, int ret);
int		quotes(char *line, int index);
int		expand_check(char *line, int index);

// void    pwd(void);
// void     env(char **envp);
// // void    ft_echo(char **cmd, t_cmd *check);
// char **cmd_parsing(char *str, char **cmd);
// void    cd(char **cmd, char **env);
// void get_input(char *input, int *current_pos, t_cmd *cmd);
// // ENV variables
// // void  free_env(char **env);
// char **create_env(char **env);
// char **alloc_env(char **env, int change);
// char **rm_env(char **env, char *limit);
// char  **add_env(char *line, char **env);
// void print_env(char **env);
// // QUOTES
// void sing_quote(char *cmd);
// void dub_quote(char *cmd);
// int check_dub_quote(char **str);
// int check_sing_quote(char **str);
// int check_nest_quote(char **str);
// // PARSING
// int ft_is_space(char c);
// int is_quote(char c);
// int cmd_delimiter(char c);
// int token_delimiter(char c);
// void skip_space(char *input, int *current_pos);
// void literal_check(t_cmd *cmd, char **str);
// void del_quote(char *cmd);
// void	skip_quote(const char *input, int *curr_pos);
// // COMMANDS
// int token_delimiter(char c);
// int cmd_delimiter(char c);
// char *get_token(char *input, int *current_pos);
// // void exec_builtin(t_cmd *cmd, t_env *var, t_msh *msh);
// void	get_cmd(char **cmd, char **envp, t_cmd *input);
// void exec_cmd(t_cmd *cmd, t_env *var, t_msh *msh);
// // PIPEX
// int	find_path(char *cmd, char **envp);
// void pipex(int argc, char **argv, char **env);
// void error(char *str);
// void	child_process(char **argv, char **env, int *fd);
// void	parent_process(char **argv, char **env, int *fd);

#endif