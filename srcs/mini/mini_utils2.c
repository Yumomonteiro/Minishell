/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:08:24 by ada-mata          #+#    #+#             */
/*   Updated: 2024/11/16 14:55:53 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_special_redir_cases(t_msh *mini, t_token *token)
{
	if (is_type(token, TRUNC) || is_type(token, APPEND))
	{
		if (search_pipe(token))
			pipex(mini, token);
		else
			redir(mini, token);
		return (1);
	}
	if (is_type(token, INPUT))
	{
		if (search_pipe(token))
			pipex(mini, token);
		else
			input(mini, token);
		return (1);
	}
	if (is_type(token, HEREDOC))
		return (heredoc(mini, token), 1);
	if (is_type(token, PIPE))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|' \n", 2);
		return (1);
	}
	return (0);
}

int	handle_heredoc_or_input(t_msh *mini, t_token *tmp)
{
	int	res;

	res = 0;
	if (is_type(tmp->next, HEREDOC) == 1)
	{
		res = heredoc(mini, tmp->next);
		if (res == 1)
			return (1);
	}
	else if (is_type(tmp->next, INPUT) == 1)
	{
		if (search_pipe(tmp))
		{
			res = pipex(mini, tmp);
			if (res == 1)
				return (1);
		}
		res = input(mini, tmp->next);
		if (res == 1)
			return (1);
	}
	return (0);
}

int	handle_redirection_or_pipe(t_msh *mini, t_token *tmp)
{
	int	res;

	res = 0;
	if (is_type(tmp->next, TRUNC) == 1 || is_type(tmp->next, APPEND) == 1)
	{
		if (search_pipe(tmp))
		{
			res = pipex(mini, tmp);
			if (res == 1)
				return (1);
		}
		res = redir(mini, tmp->next);
		if (res == 1)
			return (1);
	}
	return (0);
}

int	free_heredoc(char *line)
{
	if (line == NULL)
	{
		printf("bash: warning: here-document delimited"
			" by end-of-file (wanted `eof')\n");
		return (1);
	}
	return (0);
}
