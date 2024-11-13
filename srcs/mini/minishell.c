/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:08:24 by ada-mata          #+#    #+#             */
/*   Updated: 2024/11/13 11:03:11 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// ls
t_token	*next_run(t_token *token, int skip)
{
	type_arg(token, 0);
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD && token->type != TRUNC && token->type != APPEND
		&& token->type != INPUT && token->type != PIPE && token->type != HEREDOC)
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
int	handle_special_redir_cases(t_msh *mini, t_token *token)
{
	if (is_type(token, TRUNC) || is_type(token, APPEND))
	{
		redir(mini, token);
		return (1);
	}
	if (is_type(token, INPUT))
	{
		input(mini, token);
		return (1);
	}
	if (is_type(token, HEREDOC))
	{
		heredoc(mini, token);
		return (1);
	}
	if (is_type(token, PIPE))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		mini->ret = 258;
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
		if(handle_special_redir_cases(mini, token) == 1)
			return ;
		tmp = token;
		if (tmp->next)
			tmp = skip_cmd(tmp);
		if (handle_special_tokens(mini, tmp) == 1)
			return ;
		token = execute_command_or_pipe(mini, token, tmp);
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
