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

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->value);
		free(temp);
	}
}

void	free_all(t_msh *mini)
{
	if (mini->env)
		free_env(mini->env);
	if (mini->secret_env)
		free_env(mini->secret_env);
	if (mini->start)
		free_token(mini->start);
	if (mini->env)
		free_env_list(mini->env);
	if (mini->secret_env)
		free_env_list(mini->secret_env);
}

void	close_in_out(t_msh *mini)
{
	ft_close(mini->in);
	ft_close(mini->out);
	if (mini->env)
		free_env(mini->env);
	if (mini->secret_env)
		free_env(mini->secret_env);
	if (mini->args)
		free_tab(mini->args);
	if (mini->line_arg)
		free(mini->line_arg);
	if (mini->bin)
		free_tab(mini->bin);
	if (mini->cmd)
		free_tab(mini->cmd);
}
