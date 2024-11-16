/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:08:24 by ada-mata          #+#    #+#             */
/*   Updated: 2024/11/16 11:56:31 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_special_redir_cases(t_msh *mini, t_token *token)
{
	if (is_type(token, TRUNC) || is_type(token, APPEND))
	{
		redir(mini, token);
		return (1);
	}
	if (is_type(token, INPUT))
	{
		input(mini, token);
		return (1);
	}
	if (is_type(token, HEREDOC))
	{
		heredoc(mini, token);
		return (1);
	}
	if (is_type(token, PIPE))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|' \n", 2);
		mini->ret = 258;
		return (1);
	}
	return (0);
}