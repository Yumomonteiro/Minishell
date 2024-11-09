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

int	add_env_variable(t_env **env, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->value = ft_strdup(value);
	new->next = NULL;
	(*env)->next = new;
	*env = new;
	return (0);
}

int	env_init(t_msh *mini, char **env_array)
{
	t_env	*env;
	char	*pwd;
	int		i;

	pwd = getcwd(NULL, 0);
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
		if (add_env_variable(&env, env_array[i++]))
			return (1);
	if (!env || !env->value)
		special_env(env, pwd);
	free(pwd);
	return (0);
}

int	secret_env_init(t_msh *mini, char **env_array)
{
	t_env	*env;
	char	*pwd;
	int		i;

	pwd = getcwd(NULL, 0);
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->secret_env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
		if (add_env_variable(&env, env_array[i++]))
			return (1);
	if (!env || !env->value)
		special_env(env, pwd);
	return (0);
}
