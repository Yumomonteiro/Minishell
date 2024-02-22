/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:32:11 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/22 13:05:40 by yude-oli         ###   ########.fr       */
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
        int flag_space = 0;
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
                        while(cmd[i][j] == '$' && cmd[i][j + 1] != 32 && cmd[i][j + 1] && cmd[i])
                        {
                                env_var_name = cmd[i] + 1;
                                env_var_value = getenv(env_var_name);
                                if (env_var_value == NULL)
                                {
                                        if(!cmd[i + 1])
                                        {
                                                printf("\n");
                                                return;
                                        }
                                        flag_space = 1;
                                }
                                else
                                        printf("%s", env_var_value);
                                i++;
                                if(!cmd[i])
                                {
                                        printf("\n");    
                                        return;
                                }
                                if(flag_space == 0)
                                        printf(" ");
                                flag_space = 0;
                        }
                        printf("%s", cmd[i]);
                        i++;
                        if(!cmd[i])
                                break;
                        printf(" ");
                }
        }
        else
        {
                i = 1;
                while(cmd[i])
                {
                        j = 0;
                        while(cmd[i][j] == '$' && cmd[i][j + 1] != 32 && cmd[i][j + 1] && cmd[i])
                        {
                                env_var_name = cmd[i] + 1;
                                env_var_value = getenv(env_var_name);
                                if (env_var_value == NULL)
                                {
                                        if(!cmd[i + 1])
                                        {
                                                printf("\n");
                                                return;
                                        }  
                                        flag_space = 1;
                                }
                                else
                                        printf("%s", env_var_value);
                                i++;
                                if(!cmd[i])
                                {
                                        printf("\n");    
                                        return;
                                }
                                if(flag_space == 0)
                                        printf(" ");
                                flag_space = 0;
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

int check_env_var(char **env, char *var_env)
{
        int i = 0;
        while(env[i])
        {
                if(strncmp(env[i], var_env, ft_strlen(var_env)) == 0)
                        return (0);
                i++;       
        }
        return (1);
}
// static  char *get_dir(char **cmd, char **envp)
// {
//         char *dir;

//         dir = NULL;
//         if(!cmd[1])
//         {
//                 dir = get_env_var(envp, "HOME");
//                 if (dir == NULL)
//                         return (printf("error\n"));
//         }
        
// }
char     *get_env_var(char **env, char *env_var)
{
        int i = -1;
        while(env[++i])
        {
                if(strncmp(env[i], env_var, ft_strlen(env_var)) == 0)
                        return(env[i] + (ft_strlen(env_var) + 1));
        }
        return (NULL);
}

void    cd(char **cmd, char **env)
{
        
        char *dir;
        
        dir = NULL;
        if(!env)
                printf("nao tem env\n");
        
        if(!cmd[1])
        {
                dir = get_env_var(env, "HOME");
                //alterar pwd e alterar old pwd
                printf("%s\n", dir);
        }
        if(ft_strncmp(cmd[1], "-", 2) == 0)
        {
                printf("entrou\n");
                if(cmd[1][1])
                        printf("comando invalido, cd.. , cd -, cd folder");
                dir = get_env_var(env, "OLDPWD");
                printf("%s\n", dir);
        }
        else
                printf("to many arguments");
}
