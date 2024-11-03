/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:49:43 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/03 16:44:58 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_env_values(struct s_env *env_list, char **array, int count)
{
	struct s_env	*current;
	int				i;

	current = env_list;
	i = 0;
	while (i < count)
	{
		array[i] = ft_strdup(current->value);
		if (array[i] == NULL)
		{
			while (i > 0)
				free(array[--i]);
			free(array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	return (array);
}

char	**env_list_to_array(struct s_env *env_list)
{
	int				count;
	struct s_env	*current;
	char			**array;

	current = env_list;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	array = malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = copy_env_values(env_list, array, count);
	if (array == NULL)
		return (NULL);
	array[count] = NULL;
	return (array);
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_msh *mini, int flag)
{
	int	result;

	result = 0;
	if (flag == 1)
	{
		if (dup2(mini->fdout, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		close(mini->fdout);
	}
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(mini, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, mini);
	else if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd(0);
	else if (ft_strcmp(args[0], "env") == 0)
		result = ft_env(mini->env);
	else if (ft_strcmp(args[0], "export") == 0)
		result = ft_export(args, mini->env, mini->secret_env);
	else if (ft_strcmp(args[0], "unset") == 0)
		result = ft_unset(args, mini);
	return (result);
}
