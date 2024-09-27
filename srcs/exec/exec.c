/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:50:14 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/27 18:06:23 by ada-mata &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_tokens(t_token *start)
{
	t_token	*token;
	int		count;

	token = start->next;
	count = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		count++;
	}
	return (count);
}

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	i = count_tokens(start);
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	has_redir(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (is_type(current, TRUNC) || is_type(current, APPEND))
			return (1);
		current = current->next;
	}
	return (0);
}

void	exec_cmd(t_msh *mini, t_token *token)
{
	char	**cmd;

	cmd = cmd_tab(token);
	if (cmd && ft_strcmp(cmd[0], "exit") == 0)
	{
		free_token(mini->start);
		free_env(mini->env);
		free_env(mini->secret_env);
		/* free(mini->env->value);
		free(mini->secret_env->value); */
		exit(0);
	}
	else if (cmd && is_builtin(cmd[0]))
	{
		if (search_pipe(token))
			pipex_builtin(mini, token);
		else if (has_redir(token))
			redir_builtin(cmd, mini, token);
		else
			mini->ret = exec_builtin(cmd, mini, 0);
	}
	else if (cmd)
		mini->ret = exec(cmd, mini->env, mini);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	free(cmd);
}
