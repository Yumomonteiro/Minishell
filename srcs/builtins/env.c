/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:49:57 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/02 13:49:57 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_env_list(t_env *env, char *var_name, char *args)
{
	char	env_name[BUFF_SIZE];

	if (strchr(args, '=') != NULL)
	{
		while (env)
		{
			get_env_name(env_name, env->value);
			if (ft_strcmp(var_name, env_name) == 0)
			{
				ft_memdel(env->value);
				env->value = ft_strdup(args);
				return (1);
			}
			env = env->next;
		}
	}
	return (0);
}

int	update_secret_list(t_env *secret, char *var_name, char *args)
{
	char	secret_name[BUFF_SIZE];

	if (strchr(args, '=') != NULL)
	{
		while (secret)
		{
			get_env_name(secret_name, secret->value);
			if (ft_strcmp(var_name, secret_name) == 0)
			{
				ft_memdel(secret->value);
				secret->value = ft_strdup(args);
				return (1);
			}
			secret = secret->next;
		}
	}
	return (0);
}

int	update_env_and_secret(t_env *env, t_env *secret, char *args)
{
	char	var_name[BUFF_SIZE];
	int		updated;

	updated = 0;
	get_env_name(var_name, args);
	updated += update_env_list(env, var_name, args);
	updated += update_secret_list(secret, var_name, args);
	if (updated > 0)
		return (1);
	else
		return (0);
}

int	ft_env(t_env *env)
{
	if (!env || !env->value)
	{
		return (0);
	}
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 1);
	return (SUCCESS);
}
