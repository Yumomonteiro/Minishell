/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:08:24 by ada-mata          #+#    #+#             */
/*   Updated: 2024/11/16 12:09:48 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*next_run(t_token *token, int skip)
{
	type_arg(token, 0);
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD && token->type != TRUNC
		&& token->type != APPEND
		&& token->type != INPUT && token->type != PIPE
		&& token->type != HEREDOC)
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
	if (handle_heredoc_or_input(mini, tmp) == 1)
		return (1);
	if (handle_redirection_or_pipe(mini, tmp) == 1)
		return (1);
	return (0);
}

void	process_tokens(t_msh *mini)
{
	t_token	*token;
	t_token	*tmp;

	token = next_run(mini->start, 0);
	if (token)
	{
		if (handle_special_redir_cases(mini, token) == 1)
			return ;
		else
		{
			tmp = token;
			if (tmp->next)
				tmp = skip_cmd(tmp);
			if (is_builtin(token->str) == 0
				&& handle_special_tokens(mini, tmp) == 1)
				return ;
			token = execute_command_or_pipe(mini, token, tmp);
			return ;
		}
	}
}

t_token	*parse_tokens(char *line, t_env *env, int ret, t_token **last_token)
{
	t_token	*current_token;
	t_token	*prev_token;
	int		i;
	int		sep;

	current_token = NULL;
	prev_token = NULL;
	i = 0;
	while (line[i])
	{
		sep = ignore_sep(line, i);
		current_token = next_token(line, env, &i, ret);
		current_token->prev = prev_token;
		if (prev_token)
			prev_token->next = current_token;
		type_arg(current_token, sep);
		prev_token = current_token;
		ft_skip_space(line, &i);
	}
	*last_token = current_token;
	return (current_token);
}

void	minishell(t_msh *mini)
{
	process_tokens(mini);
	cleanup(mini);
}
