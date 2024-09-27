/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:50:14 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/27 17:46:21 by ada-mata &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path(char **args, t_env *env, t_msh *mini, char *path)
{
	int	ret;

	if (path != NULL)
		ret = execute(path, args, env, mini);
	else
		ret = execute(args[0], args, env, mini);
	return (ret);
}

t_env	*get_path_variable(t_env *env)
{
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env && env->value)
		return (env);
	else
		return (NULL);
}

char	*search_in_paths(char **bin_paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (bin_paths[i])
	{
		path = path_join_pipe(bin_paths[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		ft_memdel(path);
		i++;
	}
	return (NULL);
}

char	*find_executable(char *cmd, t_env *env)
{
	char	**bin_paths;
	char	*path;
	t_env	*temp_env;

	temp_env = get_path_variable(env);
	if (!temp_env)
		return (NULL);
	bin_paths = ft_split(temp_env->value + 5, ':');
	if (!bin_paths)
		return (NULL);
	path = search_in_paths(bin_paths, cmd);
	if (path)
	{
		free(bin_paths);
		return (path);
	}
	free(bin_paths);
	return (NULL);
}

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		count++;
		token = token->next;
	}
	return (count);
}
