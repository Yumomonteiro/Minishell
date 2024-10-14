/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:00:44 by yude-oli          #+#    #+#             */
/*   Updated: 2024/10/14 16:07:08 by ada-mata &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_join_pipe(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char	**build_args(t_token *token)
{
	int		i;
	int		argc;
	char	**args;

	argc = count_args(token);
	args = malloc((argc + 1) * sizeof(char *));
	i = 0;
	while (token && token->type != PIPE
		&& (token->type == ARG || token->type == CMD))
	{
		args[i++] = token->str;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

void	exec_pipe_cmd(t_msh *mini, t_token *token)
{
	char	**args;
	char	*path;
	char	**env_array;

	if (mini)
	{
		args = build_args(token);
		path = find_executable(args[0], mini->env);
		env_array = env_list_to_array(mini->env);
		if (!env_array)
			return ;
		if (path)
		{
			if (check_args(args, token) == 0)
			{
				execve(path, args, env_array);
				exit(EXIT_FAILURE);
			}
			token = token->next;
			exec_cmd(mini, token);
		}
		else
			perror("minishell: command not found");
	}
	exit_cleanup(path, args, env_array);
}

t_token	*execute_command_or_pipe(t_msh *mini, t_token *token, t_token *tmp)
{
	int	res;

	res = 0;
	if (is_type(tmp->next, PIPE) == 1 && !is_builtin(token->str))
	{
		res = pipex(mini, token);
		if (res == 1)
			return (NULL);
		token = tmp->next;
	}
	if (token && is_type(token, PIPE) == 0)
	{
		if (token->prev && is_type(token->prev, HEREDOC) == 1)
			token = token->next;
		else
			exec_cmd(mini, token);
	}
	return (next_run(mini->start, SKIP));
}

t_token	*skip_cmd(t_token *tmp)
{
	while (tmp && tmp->next)
	{
		if (tmp->type == CMD || tmp->type == ARG)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp && (tmp->type == TRUNC || tmp->type == APPEND
				||tmp->type == HEREDOC || tmp->type == PIPE
				|| tmp->type == INPUT))
			return (tmp->prev);
		else
			tmp = tmp->next;
	}
	return (tmp);
}
