/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:52:20 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/09 15:33:21 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int setup_pipe_and_fork(int pipefd[2], pid_t *pid)
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

void execute_child_process(t_msh *mini, t_token *token, int pipefd[2])
{
	t_token *next_token;

	dup2(mini->pipin, STDIN_FILENO);
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

void handle_parent_process(t_msh *mini, int pipefd[2])
{
	close(pipefd[1]);
	if (mini->pipin != STDIN_FILENO)
		ft_close(mini->pipin);
	mini->pipin = pipefd[0];
}

int pipex(t_msh *mini, t_token *token)
{
	int pipefd[2];
	pid_t pid;
	pid_t pids[256]; // Array para armazenar os PIDs (ajuste o tamanho conforme necessário)
	int pid_count = 0;

	mini->pipin = STDIN_FILENO;
	while (token)
	{
		if (token->type == PIPE)
		{
			token = token->next;
			continue;
		}
		if (setup_pipe_and_fork(pipefd, &pid) != 0)
			return (1);

		if (pid == 0)
		{
			// Processo filho
			execute_child_process(mini, token, pipefd);
		}
		else
		{
			// Processo pai
			pids[pid_count++] = pid; // Armazena o PID do processo filho
			handle_parent_process(mini, pipefd);
			while (token && token->type != PIPE)
				token = token->next;
			if (token)
				token = token->next;
		}
	}

	// Aguarda todos os processos filhos ao final
	for (int i = 0; i < pid_count; i++)
		waitpid(pids[i], &mini->ret, 0);

	return (0);
}
