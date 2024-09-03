/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:18:41 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/03 19:45:43 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input(t_msh *mini, t_token *token)
{
	if (!token->next)
	{
		printf("-bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	ft_close(mini->fdin);
	mini->fdin = open(token->next->str, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		return (0);
	}
	dup2(mini->fdin, STDIN);
	return (0);
}

int	handle_redirection(t_msh *mini, t_token *token)
{
	ft_close(mini->fdout);
	if (is_type(token, TRUNC))
		mini->fdout = open(token->next->str, O_CREAT
				| O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fdout = open(token->next->str, O_CREAT
				| O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		return (0);
	}
	if (dup2(mini->fdout, STDOUT_FILENO) == -1)
	{
		perror("Erro ao redirecionar STDOUT");
		close(mini->fdout);
		return (0);
	}
	return (1);
}

void	check_next_redir(t_msh *mini, t_token *token)
{
	token = token->next->next;
	if (is_type(token, TRUNC) || is_type(token, APPEND))
		redir(mini, token);
	if (is_type(token, INPUT))
		input(mini, token);
}

int	redir(t_msh *mini, t_token *token)
{
	if (!token->next)
	{
		printf("-bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (token->next)
	{
		if (!handle_redirection(mini, token))
			return (0);
	}
	if (token->next->next)
		check_next_redir(mini, token);
	return (0);
}
