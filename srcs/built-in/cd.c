#include "../../includes/minishell.h"

char *get_env_var_cd(t_env *env, char *env_var)
{
    while(env)
    {
        if(strncmp(env->value, env_var, strlen(env_var)) == 0)
            return(env->value);
        env = env->next;
    }
    return (NULL);
}

char *get_env_var_value_cd(t_env *env, char *env_var)
{
    while(env)
    {
        if(strncmp(env->value, env_var, strlen(env_var)) == 0)
            return(env->value + (strlen(env_var) + 1));
        env = env->next;
    }
    return (NULL);
}

t_env *rm_env(t_env *env, char *del_env)
{
    t_env *prev = NULL;
    t_env *current = env;
    while(current)
    {
        if(strncmp(current->value, del_env, strlen(del_env)) == 0)
        {
            if(prev)
                prev->next = current->next;
            else
                env = current->next;
            free(current->value);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
    return env;
}

t_env *add_env(char *line, t_env *env)
{
    t_env *new_env = malloc(sizeof(t_env));
    new_env->value = strdup(line);
    new_env->next = env;
    return new_env;
}

void change_env_oldpwd(t_msh *mini)
{
    char *pwd;
    char *pwd_var;
    pwd = getcwd(NULL, 0);
    pwd_var = malloc(strlen("PWD=") + strlen(pwd) + 1);
    strcpy(pwd_var, "PWD=");
    strcat(pwd_var, pwd);
    mini->env = rm_env(mini->env, "PWD");
    mini->env = add_env(pwd_var, mini->env);
}

void change_env_pwd(t_msh *mini, char *oldpwd)
{
    char *oldpwd_var;
    oldpwd_var = malloc(strlen("OLDPWD=") + strlen(oldpwd) + 1);
    strcpy(oldpwd_var, "OLDPWD=");
    strcat(oldpwd_var, oldpwd);
    mini->env = rm_env(mini->env, "OLDPWD");
    mini->env = add_env(oldpwd_var, mini->env);
}

int ft_cd(char **cmd, t_msh *mini)
{
    char *dir;
    char *oldpwd;

    oldpwd = NULL;
    dir = NULL;
    if(!mini->env)
        printf("nao tem env\n");

    if(!cmd[1])
    {
        oldpwd = getcwd(NULL, 0);
        dir = get_env_var_value_cd(mini->env, "HOME");
        if(dir)
        {
            if(chdir(dir) != 0)
                perror("Erro ao alterar diretorio");
            change_env_pwd(mini, oldpwd);
            change_env_oldpwd(mini);
        }
    }
    else if (strcmp(&cmd[1][0], "-") == 0)
    {       
        oldpwd = getcwd(NULL, 0);
        dir = get_env_var_value_cd(mini->env, "OLDPWD");
        if(chdir(dir) != 0)
        {
            perror("Erro ao alterar de diretorio");
        }
        change_env_pwd(mini, oldpwd);;
        change_env_oldpwd(mini);
    }
    else if (cmd[1])
    {
        oldpwd = getcwd(NULL, 0);
        printf("entrou no cd (diretorio)\n");
        if(chdir(cmd[1]) != 0)
        {
            perror("Erro ao alterar de diretorio");
        }
        change_env_pwd(mini, oldpwd);
        change_env_oldpwd(mini);
    }
    return 0;
}