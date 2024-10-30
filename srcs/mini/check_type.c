/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:14:48 by yude-oli          #+#    #+#             */
/*   Updated: 2024/10/30 18:58:31 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	search_redir(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, TRUNC) || is_type(token, APPEND))
			return (1);
		token = token->next;
	}
	return (0);
}

int	search_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

int	check_args(char **args, t_token *token)
{
	if (args && args[0] && ft_strncmp(args[0], "cat", 3) == 0
		&& !args[1] && token && token->next && token->next->type == PIPE)
	{
		return (1);
	}
	return (0);
}
int	env_init(t_msh *mini, char **env_array)
{
	t_env	*env;
	char	*pwd;
	char	*env_pwd;
	int		i;

	pwd = getcwd(NULL, 0);
	env_pwd = NULL;
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
		if (add_env_variable(&env, env_array[i++]))
			return (1);
	if (!env || !env->value)
	{
		env_pwd = ft_strjoin("PWD=", pwd);
		env_add("SHLVL=1", env);
		env_add(env_pwd, env);
		env_add("=/usr/bin/env", env);
	}
	return (0);
}
