/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:08:24 by ada-mata          #+#    #+#             */
/*   Updated: 2024/09/03 19:38:57 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*next_run(t_token *token, int skip)
{
	type_arg(token, 0);
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

int	handle_special_tokens(t_msh *mini, t_token *tmp)
{
	int	res;

	res = 0;
	if (is_type(tmp->next, HEREDOC) == 1)
	{
		res = heredoc(mini, tmp->next);
		if (res == 1)
			return (1);
	}
	else if (is_type(tmp->next, TRUNC) == 1 || is_type(tmp->next, APPEND) == 1)
	{
		res = redir(mini, tmp->next);
		if (res == 1)
			return (1);
	}
	else if (is_type(tmp->next, INPUT) == 1)
	{
		res = input(mini, tmp->next);
		if (res == 1)
			return (1);
	}
	return (0);
}

void	process_tokens(t_msh *mini)
{
	t_token	*token;
	t_token	*tmp;

	token = next_run(mini->start, NOSKIP);
	while (token)
	{
		tmp = token;
		if (tmp->next)
			tmp = skip_cmd(tmp);
		if (handle_special_tokens(mini, tmp) == 1)
			return ;
		token = execute_command_or_pipe(mini, token, tmp);
	}
}

void	minishell(t_msh *mini)
{
	process_tokens(mini);
	cleanup(mini);
}