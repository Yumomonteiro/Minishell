/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:31:05 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/16 11:21:48 by ada-mata &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_builtin(char **cmd, t_msh *mini, t_token *token)
{
	int	flag;

	flag = 0;
	while (token)
	{
		if (is_type(token, TRUNC) || is_type(token, APPEND))
		{
			flag = 1;
			redir(mini, token);
			exec_builtin(cmd, mini, flag);
		}
		token = token->next;
	}
	reset_std(mini);
}

void	handle_child_process(int fd_in, t_token *token,
		int pipefd[2], t_msh *mini)
{
	t_token	*next_token;
	char	**cmd;

	dup2(fd_in, STDIN_FILENO);
	ft_close(fd_in);
	next_token = token;
	cmd = cmd_tab(token);
	while (next_token && next_token->type != PIPE)
	{
		if (next_token->type == TRUNC || next_token->type == APPEND)
		{
			redir(mini, next_token);
			exec_builtin(cmd, mini, 0);
		}
			
		if (next_token->type == INPUT)
			input(mini, next_token);
		next_token = next_token->next;
	}
	if (next_token && next_token->type == PIPE)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (cmd && is_builtin(cmd[0]))
		exec_builtin(cmd, mini, 0);
	else
		exec_cmd(mini, token);
	free_tab(cmd);
	exit(EXIT_FAILURE);
}

void	setup_child_process(int fd_in, t_token *token,
		int pipefd[2], t_msh *mini)
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		ft_close(mini->in);
		ft_close(mini->out);
		handle_child_process(fd_in, token, pipefd, mini);
	}
}

void	pipex_builtin(t_msh *mini, t_token *token)
{
	int	pipefd[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (token)
	{
		if (token->type == PIPE)
		{
			token = token->next;
			continue ;
		}
		setup_child_process(fd_in, token, pipefd, mini);
		close(pipefd[1]);
		waitpid(-1, &mini->ret, 0);
		fd_in = pipefd[0];
		while (token && token->type != PIPE)
			token = token->next;
		if (token)
			token = token->next;
	}
}
