#include "./includes/minishell.h"

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

void  free_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
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
        if(!new_env[i])
        {
            free_env(new_env);
            return (NULL);
        }
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}

char	**add_env(char *line, char **env)
{
	int		i;
	char	**temp;

	temp = env;
	env = alloc_env(env, 1);
	i = -1;
	while (temp[++i])
		env[i] = temp[i];
	env[i] = line;
	env[++i] = NULL;
	free(temp);
	return (env);
}


void print_env1(char **env)
{
    int i;

    i = 0;

    while (env[i] != NULL)
    {
        char *key = strtok(env[i], "=");
        char *value = strtok(NULL, "=");
        if(ft_strncmp(key, "PATH", 4) == 0)
            printf("PATH: %s\n", value);
        i++;
    }
}

// void print_env(char **env)
// {
//     int i;

//     i = 0;

//     while (env[i] != NULL)
//     {
//         while(env[i] != NULL)
//         {
//             printf("%s\n", env[i]);
//             i++;
//         }
//     }
// }

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_env *var;
    var = (t_env *)malloc(sizeof(t_env));
    var->env = create_env(env);
    print_env1(var->env);
    free_env(var->env);
    free(var);
    return (0);
}