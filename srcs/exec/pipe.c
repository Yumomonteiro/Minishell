/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:06:36 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/16 14:49:58 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_pipe_and_fork(int pipefd[2], pid_t *pid)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (1);
	}
	return (0);
}

void	execute_child_process(t_msh *mini, t_token *token, int pipefd[2])
{
	t_token	*next_token;

	dup2(mini->pipin, STDIN_FILENO);
	ft_close(mini->pipin);
	next_token = token;
	while (next_token && (next_token->type != PIPE))
	{
		if (next_token->type == TRUNC || next_token->type == APPEND)
			redir(mini, next_token);
		if (next_token->type == INPUT)
			input(mini, next_token);
		next_token = next_token->next;
	}
	if (next_token && next_token->type == PIPE)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exec_cmd(mini, token);
	exit(EXIT_FAILURE);
}

void	handle_parent_process(t_msh *mini, int pipefd[2])
{
	close(pipefd[1]);
	if (mini->pipin != STDIN_FILENO)
		ft_close(mini->pipin);
	mini->pipin = pipefd[0];
}

static void	manage_child_or_parent(t_msh *mini, t_token **token,
			int pipefd[2], pid_t *pids)
{
	pid_t	pid;

	if (setup_pipe_and_fork(pipefd, &pid) != 0)
		exit(1);
	if (pid == 0)
	{
		ft_close(mini->in);
		ft_close(mini->out);
		execute_child_process(mini, *token, pipefd);
	}
	else
	{
		pids[(mini->pid_count)++] = pid;
		handle_parent_process(mini, pipefd);
		while (*token && (*token)->type != PIPE)
			*token = (*token)->next;
		if (*token)
			*token = (*token)->next;
	}
}

int	pipex(t_msh *mini, t_token *token)
{
	int		pipefd[2];
	pid_t	pids[256];
	int		i;

	i = 0;
	mini->pipin = STDIN_FILENO;
	while (token)
	{
		if (token->type == PIPE)
		{
			token = token->next;
			continue ;
		}
		manage_child_or_parent(mini, &token, pipefd, pids);
	}
	while (i < mini->pid_count)
	{
		waitpid(pids[i], &mini->ret, 0);
		i++;
	}
	mini->ret = 0;
	return (0);
}
