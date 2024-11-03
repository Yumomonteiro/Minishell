/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:25:30 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/03 16:40:47 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	swap(t_env *a, t_env *b)
{
	char	*temp;

	temp = a->value;
	a->value = b->value;
	b->value = temp;
}

void	sort_env(t_env *env)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	if (env == NULL)
		return ;
	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = env;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->value, ptr1->next->value) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	print_sorted_env(t_env *env)
{
	sort_env(env);
	while (env && env->next != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env->value, 1);
	}
}

int	env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env == NULL)
		return (-1);
	if (env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (-1);
	new->value = ft_strdup(value);
	new->next = NULL;
	tmp = env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (SUCCESS);
}
