#include "../../includes/minishell.h"

char **alloc_env(char **env, int change)
{
    int i;
    char **new;

    i = 0;
    if (!env)
        return (NULL);
    while (env[i])
        i++;
    new = malloc(sizeof(char *) * (i + 1 + change));
    if (!new)
        return (NULL);
    return (new);
}

char **create_env(char **env)
{
    int i;
    char **new_env;

    i = 0;
    new_env = alloc_env(env, 0);
    while (env[i])
    {
        new_env[i] = ft_strdup(env[i]);
        // if(!new_env[i])
        // {
        //     free_env(new_env);
        //     return (NULL);
        // }
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}