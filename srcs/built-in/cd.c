/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:32:11 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/17 17:17:21 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    pwd(void)
{
        char *pwd;
        pwd = getcwd(NULL, 0);
        if(!pwd)
        {
                perror("-> minishell error: pwd");
                return ;
        }
        //write(1, pwd, 1);
        printf("%s\n", pwd);
        free(pwd);
}

void     env(char **envp)
{
        if(!*envp || !envp)
                perror("Minishell error: env does not exist");
        while(*envp)
                ft_putendl_fd(*envp++, 1);

}

void    echo(char **cmd)
{
        int i;
        if(!cmd[1])
        {
                perror("Minishell -> error : echo comando invalido");
                return ;
        }
        if(strncmp(cmd[1], "-n", 3) == 0)
        {
                i = 2;
                while(strcmp(cmd[i], "-n") == 0)
                {
                        i++;
                }
                while(cmd[i])
                {
                        printf("%s", cmd[i]);
                        i++;
                        if(!cmd[i])
                        {
                                printf("%%");
                                printf("\n");
                                break;
                        }
                        write(1, " ", 1);
                }
                
        }
        else
        {
                i = 1;
                while(cmd[i])
                {
                        printf("%s", cmd[i]);
                        i++;
                        if(!cmd[i])
                        {
                                printf("\n");
                            break;    
                        }
                        printf(" ");
                }
                
        }
                        
}

void    cd(char ** cmd)
{
        if(!cmd[1])
                printf("IR PARA HOME");
        if(strncmp(cmd[1], "-", 2) == 0)
                printf("OLDPWD");
        if(strncmp(cmd[1], "../", 4) == 0 || strncmp(cmd[1], "..", 3) == 0)
                
}
