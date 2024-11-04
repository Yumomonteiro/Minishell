/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:16:21 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/03 18:40:52 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_msh *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}

void	close_fds(t_msh *mini)
{
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
}

void	reset_fds(t_msh *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
}

t_token	*skip_cmd(t_token *tmp)
{
	while (tmp && tmp->next)
	{
		if (tmp->type == CMD || tmp->type == ARG)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp && (tmp->type == TRUNC || tmp->type == APPEND
				||tmp->type == HEREDOC || tmp->type == PIPE
				|| tmp->type == INPUT))
			return (tmp->prev);
		else
			tmp = tmp->next;
	}
	return (tmp);
}
