/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:50:33 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/02 13:50:33 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_error(int error, const char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

char	*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	find_env_var(t_env *list, char *var_name)
{
	char	env_name[BUFF_SIZE];

	while (list)
	{
		get_env_name(env_name, list->value);
		if (ft_strcmp(var_name, env_name) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

static void	add_to_envs(char *arg, t_env *env, t_env *secret)
{
	int		updated;
	char	var_name[BUFF_SIZE];

	get_env_name(var_name, arg);
	if (strchr(arg, '=') != NULL)
	{
		updated = update_env_and_secret(env, secret, arg);
		if (updated == 1 && !find_env_var(env, var_name))
			env_add(arg, env);
		else if (updated == 0)
		{
			env_add(arg, env);
			if (!find_env_var(secret, var_name))
				env_add(arg, secret);
		}
	}
	else
	{
		updated = update_env_and_secret(env, secret, arg);
		if (updated == 0 && !find_env_var(secret, var_name))
			env_add(arg, secret);
		else if (updated == 1 && !find_env_var(env, var_name))
			env_add(arg, env);
	}
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int		error_ret;

	if (!env->value || !secret->value)
		return (0);
	if (!args[1])
	{
		print_sorted_env(secret);
		return (SUCCESS);
	}
	error_ret = is_valid_env(args[1]);
	if (args[1][0] == '=')
		error_ret = -3;
	if (error_ret <= 0)
		return (print_error(error_ret, args[1]));
	add_to_envs(args[1], env, secret);
	return (SUCCESS);
}
