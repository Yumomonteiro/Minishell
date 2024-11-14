/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:50:14 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/14 21:33:55 by yude-oli         ###   ########.fr       */
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
	int		num_tokens;

	if (!start)
		return (NULL);
	num_tokens = count_tokens(start);
	tab = malloc(sizeof(char *) * (num_tokens + 1));
	if (!tab)
		return (NULL);
	token = start;
	i = 0;
	while (token && token->type < TRUNC)
	{
		tab[i] = ft_strdup(token->str);
		if (!tab[i])
			free_tab(tab);
		i++;
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
	mini->cmd = cmd_tab(token);
	if (mini->cmd && ft_strcmp(mini->cmd[0], "exit") == 0)
	{
		mini_exit(mini, mini->cmd);
		mini_clean(mini);
		free_tab(mini->cmd);
		exit(0);
	}
	else if (mini->cmd && is_builtin(mini->cmd[0]))
	{
                printf("entrou\n");
		if (search_pipe(token))
			pipex_builtin(mini, token);
		else if (has_redir(token))
			redir_builtin(mini->cmd, mini, token);
		else
			mini->ret = exec_builtin(mini->cmd, mini, 0);
	}
	else if (mini->cmd && is_type(token, PIPE) == 0)
		mini->ret = exec(mini->cmd, mini->env, mini);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	free_tab(mini->cmd);
}
