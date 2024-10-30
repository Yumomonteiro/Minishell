/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:27:46 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/02 13:27:46 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*add_env(char *line, t_env *env)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	new_env->value = strdup(line);
	new_env->next = env;
	return (new_env);
}

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(sizeof(char) * size_env(lst) + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i++] = lst->value[j++];
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int	env_init(t_msh *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	if (!env || !env->value)
	{
		env_add("SHELL=/bin/bash", env);
		env_add("HOME=/home/user", env);
		env_add("PATH=/home/ada-mata/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/c/Program Files (x86)/NVIDIA Corporation/PhysX/Common:/mnt/c/Program Files/NVIDIA Corporation/NVIDIA NvDLISR:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files (x86)/dotnet/:/mnt/c/xampp/mysql/bin:/mnt/c/xampp/php:/mnt/c/Program Files/nodejs/:/mnt/c/Program Files/Git/cmd:/mnt/c/Program Files/dotnet/:/mnt/c/ProgramData/ComposerSetup/bin:/mnt/c/Users/admil/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/admil/AppData/Local/GitHubDesktop/bin:/mnt/c/Users/admil/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/admil/AppData/Roaming/npm:/mnt/c/MinGW/bin:/mnt/c/Users/admil/AppData/Roaming/Composer/vendor/bin:/home/ada-mata/.local/bin:/home/ada-mata/.local/bin:/home/ada-mata/.local/bin", env);
		return (0);
	}
	return (0);
}

int	secret_env_init(t_msh *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->secret_env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
