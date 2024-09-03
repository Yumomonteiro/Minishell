/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:17:08 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/03 13:17:08 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		ft_memdel(tmp->value);
		ft_memdel(tmp);
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

void	free_token(t_token *start)
{
	while (start && start->next)
	{
		ft_memdel(start->str);
		start = start->next;
		ft_memdel(start->prev);
	}
	if (start)
	{
		ft_memdel(start->str);
		ft_memdel(start);
	}
}

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_memdel(tab[i]);
		i++;
	}
	if (tab)
		ft_memdel(tab);
}

void	cleanup(t_msh *mini)
{
	reset_std(mini);
	close_fds(mini);
	reset_fds(mini);
}
