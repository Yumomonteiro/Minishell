/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:24:07 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/02 14:24:50 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_skip_whitespaces(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
		|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

static int	invalid_lvl(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	get_lvl(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	ft_skip_whitespaces(str, &i);
	if (invalid_lvl(str))
		return (0);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

void	shell_level(t_env *env)
{
	int		shell_level;
	char	env_name[BUFF_SIZE];
	char	*shlvl;
	char	*shell_level_value;

	shell_level_value = get_env_value("SHLVL", env);
	if (ft_strcmp(shell_level_value, "") == 0)
		return ;
	shell_level = get_lvl(shell_level_value) + 1;
	ft_memdel(shell_level_value);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp("SHLVL", env_name) == 0)
		{
			ft_memdel(env->value);
			shlvl = ft_itoa(shell_level);
			env->value = ft_strjoin("SHLVL=", shlvl);
			ft_memdel(shlvl);
			return ;
		}
		env = env->next;
	}
}

t_env	*rm_env(t_env *env, char *del_env)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = env;
	while (current)
	{
		if (strncmp(current->value, del_env, strlen(del_env)) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env = current->next;
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
	return (env);
}
