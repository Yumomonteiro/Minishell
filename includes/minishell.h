/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:57:03 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/16 13:43:35 by ada-mata         ###   ########.fr       */
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

char **create_env(char **env);
void  free_env(char **env);
char **create_env(char **env);
char **alloc_env(char **env, int change);
char **rm_env(char **env, char *limit);
char  **add_env(char *line, char **env);
void print_env(char **env);

#endif