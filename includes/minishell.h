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
# define HEREDOCS 8

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
	int						 quote_space;
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

int		ft_unset(char **a, t_msh *mini);
int		ft_echo(char **args);
int		ft_export(char **args, t_env *env, t_env *secret);
int		env_init(t_msh *mini, char **env_array);
int		secret_env_init(t_msh *mini, char **env_array);
int		is_sep(char *line, int i);
int		ignore_sep(char *line, int i);
int		quotes(char *line, int index);
int		exec_builtin(char **args, t_msh *mini);
int		ft_strcmp(const char *s1, const char *s2);
int		is_valid_env(const char *env);
int		ft_env(t_env *env);
int		is_builtin(char *command);
int		quotes(char *line, int index);
int		expand_check(char *line, int index);
int		is_env_char(int c);
int		ret_size(int ret);
int		next_alloc(char *line, int *i);
int		quotes(char *line, int index);
int		is_type(t_token *token, int type);
int		quote_check(t_msh *mini, char **line);
int		get_var_len(const char *arg, int pos, t_env *env, int ret);
int		arg_alloc_len(const char *arg, t_env *env, int ret);


char	*get_env_value(char *arg, t_env *env);
char	*get_env_name(char *dest, const char *src);
char	*env_to_str(t_env *lst);
char	*expansions(char *arg, t_env *env, int ret);
char	**cmd_tab(t_token *start);


void	print_sorted_env(t_env *env);
void	*ft_memdel(void *ptr);
void	type_arg(t_token *token, int separator);
void	free_env(t_env *env);
void	exec_cmd(t_msh *mini, t_token *token);
void	free_tab(char **tab);
void	type_arg(t_token *token, int separator);
void 	handle_escapes(char *line, char *temp, int *j, int *i);
void 	handle_variable_expansion(char *line, t_env *env, char *temp, int *j, int *i, int ret, char quote);
void	ft_skip_space(const char *str, int *i);
void	parse(t_msh *mini);
void	*ft_memdel(void *ptr);
void	free_tab(char **tab);


t_token *get_tokens(char *line, t_env *env, int ret);



#endif