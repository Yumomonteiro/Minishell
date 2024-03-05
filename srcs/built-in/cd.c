/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:32:11 by yude-oli          #+#    #+#             */
/*   Updated: 2024/03/05 16:03:14 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    pwd(int flag)
{
        char *pwd;
        pwd = getcwd(NULL, 0);
        if(!pwd)
        {
                perror("-> minishell error: pwd");
                return ;
        }
        if(flag == 0)
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
char     *get_env_var(char **env, char *env_var)
{
        int i = -1;
        while(env[++i])
        {
                if(strncmp(env[i], env_var, ft_strlen(env_var)) == 0)
                        return(env[i]);
        }
        return (NULL);
}

char     *get_env_var_value(char **env, char *env_var)
{
        int i = -1;
        while(env[++i])
        {
                if(strncmp(env[i], env_var, ft_strlen(env_var)) == 0)
                        return(env[i] + (ft_strlen(env_var) + 1));
        }
        return (NULL);
}

void change_env_oldpwd(t_env *env)
{
        char *pwd;
        char *pwd_var;
        // altera o pwd nas variaveis de ambiente.
        //remove a antiga e aloca uma nova variavel com o valor PWD novo
        pwd = getcwd(NULL, 0);
        pwd_var = ft_strjoin("PWD=", pwd);
        env->env = rm_env(env->env, "PWD");
        env->env = add_env(pwd_var, env->env);
}
void change_env_pwd(char *oldpwd, t_env *env)
{
        char *oldpwd_var;
        oldpwd_var = NULL;
     
        //altera o OLDPWD, removendo o antigo e alocando a nova string nas variaveis ambientais
        oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
        env->env = rm_env(env->env, "OLDPWD");
        env->env = add_env(oldpwd_var, env->env);
}
void    cd(char **cmd, t_env *env)

{
        char *dir;
        char *oldpwd;

        oldpwd = NULL;
        dir = NULL;
        if(!env->env)
                printf("nao tem env\n");
        
        if(!cmd[1])
        {
                oldpwd = getcwd(NULL, 0);
                dir = get_env_var_value(env->env, "HOME");
                if(dir)
                {
                        if(chdir(dir) != 0)
                                perror("Erro ao alterar diretorio");
                        change_env_pwd(oldpwd, env);
                        change_env_oldpwd(env);
                }
        }
        else if (strcmp(&cmd[1][0], "-") == 0)
        {
                printf("entrou no cd -\n");
                dir = get_env_var_value(env->env, "OLDPWD");
                if(chdir(dir) != 0)
                {
                        perror("Erro ao alterar de diretorio");
                }
        }
        else if (cmd[1])
        {
                printf("entrou no cd (diretorio)\n");
                if(chdir(cmd[1]) != 0)
                {
                        perror("Erro ao alterar de diretorio");
                }
        }
}

void    signals(int sig)
{
        if(sig == SIGINT)
        {
                printf("\n");
                return;
        }     
}