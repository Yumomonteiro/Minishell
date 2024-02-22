#include "./includes/minishell.h"

void print_env1(char **env, char *name)
{
    int i;

    i = 0;

    while (env[i] != NULL)
    {
        char *key = strtok(env[i], "=");
        char *value = strtok(NULL, "=");
        if(ft_strncmp(key, name, 3) == 0)
            printf("%s:%s\n", name, value);
        i++;
    }
}

void print_env(char **env)
{
    int i;

    i = 0;

    while (env[i] != NULL)
    {
        while(env[i] != NULL)
        {
            printf("%s\n", env[i]);
            i++;
        }
    }
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_env *var;
    var = (t_env *)malloc(sizeof(t_env));
    var->env = create_env(env);
    char *new = "VAR=this";
    var->env = add_env(new, var->env);
    print_env(var->env);
    // print_env1(var->env, "VAR");
    var->env = rm_env(var->env, "LESS");
    printf("REMOVENDO VAR\n");
    print_env(var->env);
    //print_env1(var->env, "PATH");
    free_env(var->env);
    free(var);
    return (0);
}

// Function to print the environment