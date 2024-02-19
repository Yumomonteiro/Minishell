/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:57:03 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/16 15:47:13 by yude-oli         ###   ########.fr       */
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
#define MAX_PATH_LENGTH 1024

typedef struct s_env
{
    char	**env;
    int    size;
    int    status;
}	t_env;

// t_env env;

typedef struct s_cmd
{
        char    **cmd;
}               t_cmd;

char **create_env(char **env);
void    pwd(void);
void     env(char **envp);
void    echo(char **cmd);
char **cmd_parsing(char *str, char **cmd);

#endif