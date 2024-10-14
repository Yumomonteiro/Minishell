/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:14:48 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/03 19:45:26 by ada-mata         ###   ########.fr       */
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

int     check_args(char **args, t_token *token)
{
    if (args && args[0] && ft_strncmp(args[0], "cat", 3) == 0
        && !args[1] && token && token->next && token->next->type == PIPE)
    {
        return (1);
    }
    return (0);
}
