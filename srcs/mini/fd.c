/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:16:21 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/03 19:45:30 by ada-mata         ###   ########.fr       */
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
