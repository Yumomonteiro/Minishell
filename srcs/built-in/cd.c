/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:32:11 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/19 16:18:52 by yude-oli         ###   ########.fr       */
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
        int j;
        char *env_var_name;
        char *env_var_value;
        if (!cmd[1])
                return ;
        if (strncmp(cmd[1], "-n", 3) == 0)
        {
                i = 2;
                while (strcmp(cmd[i], "-n") == 0)
                        i++;
                while (cmd[i])
                {
                        j = 0;
                        if(cmd[i][j] == '$' && cmd[i][j + 1] != 32 && cmd[i][j + 1])
                        {
                                env_var_name = cmd[i] + 1;
                                env_var_value = getenv(env_var_name);
                                if (env_var_value == NULL)
                                {
                                        printf("\n");
                                        return ;
                                }
                                printf("%s", env_var_value);
                                i++;
                                if(!cmd[i])
                                {
                                        printf("\n");    
                                        return;
                                }
                                printf(" ");
                        }
                        printf("%s", cmd[i]);
                        i++;
                        if(!cmd[i])
                        {
                                printf("%%");
                                printf("\n");
                                break;
                        }
                        printf(" ");
                }
        }
        else
        {
                i = 1;
                while(cmd[i])
                {
                        j = 0;
                        if(cmd[i][j] == '$' && cmd[i][j + 1] != 32 && cmd[i][j + 1])
                        {
                                env_var_name = cmd[i] + 1;
                                env_var_value = getenv(env_var_name);
                                if (env_var_value == NULL)
                                {
                                        printf("\n");
                                        return ;
                                }
                                printf("%s", env_var_value);
                                i++;
                                if(!cmd[i])
                                {
                                        printf("\n");    
                                        return;
                                }
                                printf(" ");
                        }
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
void cd_home(char *env, char *cmd);
void    cd(char **cmd, char **env)
{
        char *homedir;
        printf("entrouuuu\n");
        if(env)
                printf("v\n");
        if(!cmd[1])
        {
                homedir = getenv("HOME");
                if(!homedir)
                        return ;
                if (chdir(homedir) != 0)
                        return ;
        }
        
        // if(strncmp(cmd[1], "-", 2) == 0)
        //         printf("oldpwdddd");
                
}
