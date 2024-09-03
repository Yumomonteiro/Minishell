/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:30:16 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/03 14:39:45 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc_pipe(t_msh *mini, int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	mini->fdin = fd[0];
	return (0);
}

void	read_heredoc_input(const char *delimiter, int fd[1])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
}

void	handle_heredoc_next_token(t_msh *mini, t_token *token)
{
	token = token->next->next;
	if (is_type(token, TRUNC) || is_type(token, APPEND))
		redir(mini, token);
	else if (is_type(token, PIPE))
		pipex(mini, token);
}

int	heredoc(t_msh *mini, t_token *token)
{
	int	fd[2];

	if (!token->next)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (1);
	}
	if (handle_heredoc_pipe(mini, fd) != 0)
		return (1);
	read_heredoc_input(token->next->str, fd);
	if (dup2(mini->fdin, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd[0]);
		return (1);
	}
	if (token->next->next)
		handle_heredoc_next_token(mini, token);
	return (0);
}
