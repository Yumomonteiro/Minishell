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

void	free_all(t_msh *mini)
{
	if (mini->env)
		free_env(mini->env);
	if (mini->secret_env)
		free_env(mini->secret_env);
	if (mini->start)
		free_token(mini->start);
	if (mini->env->value)
		free(mini->env->value);
	if (mini->secret_env->value)
		free(mini->secret_env->value);
}
