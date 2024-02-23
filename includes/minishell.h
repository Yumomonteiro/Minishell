/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:57:03 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/22 16:28:40 by ada-mata         ###   ########.fr       */
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

typedef struct s_env
{
    char	**env;
    int    size;
    int    status;
}	t_env;

typedef struct s_cmd
{
    char **cmd;
} t_cmd;


void    pwd(void);
void     env(char **envp);
void    echo(char **cmd);
char **cmd_parsing(char *str, char **cmd);
void    cd(char **cmd, char **env);

void  free_env(char **env);
char **create_env(char **env);
char **alloc_env(char **env, int change);
char **rm_env(char **env, char *limit);
char  **add_env(char *line, char **env);
void print_env(char **env);
void sing_quote(char *cmd);
void dub_quote(char *cmd);

#endif