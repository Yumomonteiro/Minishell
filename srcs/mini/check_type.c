/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:14:48 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/14 13:58:53 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	search_redir(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, TRUNC) || is_type(token, APPEND))
			return (1);
		token = token->next;
	}
	return (0);
}

int	search_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

int	is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}
