/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:32:11 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/14 16:17:34 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*partition_path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0 && env[i + 1])
		i++;
        if(ft_strnstr(env[i], "PATH", 4) == 0)
                return (0);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		partition_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(partition_path, cmd);
		free(partition_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute_cmd(char **argv, char **env)
{
	char	**cmd;
	char	*path;
	int		i;

	i = -1;
	cmd = ft_split(*argv, ' ');
	if (!cmd[0])
		exit(0);
	path = find_path(cmd[0], env);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		write(2, "Error, invalid command!\n", 24);
		exit(0);
	}
	if (execve(path, cmd, env) == -1) 
                printf("Error\n");
}
int     cd_builtin(char **args, char **envp)
{
        if (!args[0])
        {
                printf("error");
        }
        execute_cmd(&args[1], envp);
        return 0;
}