#include "../../includes/minishell.h"

int		is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int		is_valid_env(const char *env)
{
	int		i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

int		env_value_len(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(env) + 1;
	if (!(env_value = malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_memdel(env_val);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}


// char **alloc_env(char **env, int change)
// {
//     int i;
//     char **new;

//     i = 0;
//     if (!env)
//         return (NULL);
//     while (env[i])
//         i++;
//     new = malloc(sizeof(char *) * (i + 1 + change));
//     if (!new)
//         return (NULL);
//     return (new);
// }

// char **create_env(char **env)
// {
//     int i;
//     char **new_env;

//     i = 0;
//     new_env = alloc_env(env, 0);
//     while (env[i])
//     {
//         new_env[i] = ft_strdup(env[i]);
//         if(!new_env[i])
//         {
//             free_env(new_env);
//             return (NULL);
//         }
//         i++;
//     }
//     new_env[i] = NULL;
//     return (new_env);
// }

// char	**add_env(char *line, char **env)
// {
// 	int		i;
// 	char	**new_env;
// 	int count = 0;

// 	new_env = alloc_env(env, 1);
// 	if (!new_env)
// 		return (NULL);
// 	while(env[count])
// 		count++;
// 	i = -1;
// 	while (++i < count)
// 		new_env[i] = ft_strdup(env[i]);
// 	new_env[i] = ft_strdup(line);
// 	new_env[i + 1] = NULL;
// 	return (new_env);
// }

// char **rm_env(char **env, char *del_env)
// {
// 	int i;
// 	int j;
// 	char **new_env;
// 	char **temp;

// 	temp = env;
// 	new_env = alloc_env(env, -1);
// 	if(!new_env)
// 		return (NULL);
// 	i = -1;
// 	j = 0;
// 	while(temp[++i])
// 	{
// 		if(strncmp(temp[i], del_env, 4))
// 			new_env[j++] = temp[i];
			
// 		else
// 			free(temp[i]);	
// 	}
// 	free (temp);
// 	new_env[j++] = NULL;
// 	return (new_env);
// }

// void  free_env(char **env)
// {
//     int i;

//     i = 0;
//     while (env[i])
//     {
//         free(env[i]);
//         i++;
//     }
//     free(env);
// }


