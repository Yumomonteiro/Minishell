#include "../includes/minishell.h"

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
	char	**new_env;
	int count = 0;

	new_env = alloc_env(env, 1);
	if (!new_env)
		return (NULL);
	while(env[count])
		count++;
	i = -1;
	while (++i < count)
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(line);
	new_env[i + 1] = NULL;
	return (new_env);
}

char **rm_env(char **env, char *del_env)
{
	int i;
	int j;
	char **new_env;
	char **temp;

	temp = env;
	new_env = alloc_env(env, -1);
	if(!new_env)
		return (NULL);
	i = -1;
	j = 0;
	while(temp[++i])
	{
		if(strncmp(temp[i], del_env, 4))
			new_env[j++] = temp[i];
			
		else
			free(temp[i]);	
	}
	free (temp);
	new_env[j++] = NULL;
	return (new_env);
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