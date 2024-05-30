/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:57:03 by yude-oli          #+#    #+#             */
/*   Updated: 2024/03/04 18:12:55 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
// # include "history.h"
# include "../libs/libft/libft.h"
// # include "readline.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

# define WHITE_SPACE " \t\n\r\v\f"
 #define MAX_TOKENS 100

typedef struct s_env
{
    char	**env;
    int    size;
    int    status;
}	t_env;

typedef struct s_redir
{
    char type[3];
    char *direction;
} t_redir;

typedef struct s_cmd
{
    char **token;
    int     max_token;
    char **redir;
} t_cmd;

typedef struct s_token
{
    char *token;
    struct s_token *next;
} t_token;



void    pwd(void);
void     env(char **envp);
void    ft_echo(char **cmd);
char **cmd_parsing(char *str, char **cmd);
void    cd(char **cmd, char **env);
void get_cmd(char *input, int *current_pos, t_cmd *cmd);
// ENV variables
void  free_env(char **env);
char **create_env(char **env);
char **alloc_env(char **env, int change);
char **rm_env(char **env, char *limit);
char  **add_env(char *line, char **env);
void print_env(char **env);
// QUOTES
void sing_quote(char *cmd);
void dub_quote(char *cmd);
int token_delimiter(char c);
int cmd_delimiter(char c);
void del_quote(char *cmd);
void	skip_quote(const char *input, int *curr_pos);
char *get_token(char *input, int *current_pos);
// PIPEX
char	*find_path(char *cmd, char **envp);
void pipex(int argc, char **argv, char **env);
void	exec_cmd(char *argv, char **envp);
void	error(void);
void	child_process(char **argv, char **env, int *fd);
void	parent_process(char **argv, char **env, int *fd);

#endif