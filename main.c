/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:45:25 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/22 13:01:15 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
        (void)argc;
        (void)argv;
        t_env *var;
        t_cmd *cmds;
        cmds = (t_cmd *)malloc(sizeof(t_cmd));
        var = (t_env *)malloc(sizeof(t_env));
        var->env = create_env(envp);
        char *str;
                while(1)
                {
                        //\033[32m➜ \033[0m \033[36m\033[1mminishell \033[34mgit:(\033[31mmain\033[34m)\033[0m 👍 "
                        str = readline("minishell :");
                        cmds->cmd = cmd_parsing(str, cmds->cmd);
                        if(strcmp(str, "pwd") == 0)
                                pwd();
                        else if(strcmp(str, "env") == 0)
                                env(var->env);
                        else if(strcmp(str, "minishell") == 0)
                                printf("alooow\n");
                        else if(strncmp(str, "echo", 4) == 0)
                        {
                                echo(cmds->cmd);
                        }
                        else if(strncmp(str, "exit", 4) == 0)
                        {
                                printf("entrou");
                                exit(0);
                        }
                        else if(strncmp(str, "cd", 3) == 0)
                                cd(cmds->cmd, var->env);
                                
                        free(str);
                }
                
}