/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:00:44 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/15 22:20:36 by ada-mata &       ###   ########.fr       */
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

void	execute_and_cleanup(char *path, char **args, char **env_array)
{
	if (path)
	{
		execve(path, args, env_array);
		perror("minishell: execve failed");
	}
	else
		perror("minishell: command not found");
	exit_cleanup(path, args, env_array);
	exit(EXIT_FAILURE);
}

void	exec_pipe_cmd(t_msh *mini, t_token *token)
{
	char	**args;
	char	*path;
	char	**env_array;
	
	args = build_args(token);
	path = find_executable(args[0], mini->env);
	env_array = env_list_to_array(mini->env);
	if (!env_array || !args || !path)
	{
		exit_cleanup(path, args, env_array);
		return ;
	}
	exec_cmd(mini, token);
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
	else if (token && is_type(token, PIPE) == 0)
	{
		if (token->prev && is_type(token->prev, HEREDOC) == 1)
			token = token->next;
		else
			exec_cmd(mini, token);
	}
	return (next_run(mini->start, SKIP));
}
