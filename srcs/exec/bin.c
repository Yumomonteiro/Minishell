/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:40:43 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/03 12:53:24 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell; ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int	execute(char *path, char **args, t_env *env, t_msh *mini)
{
	char	**env_array;
	char	*ptr;
	int		ret;
	pid_t	pid;

	ret = SUCCESS;
	pid = fork();
	if (pid == 0)
	{
		ptr = env_to_str(env);
		env_array = ft_split(ptr, '\n');
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		free_tab(env_array);
		free_token(mini->start);
		exit(ret);
	}
	else
		waitpid(pid, &ret, 0);
	if (!(ret == 32256 || ret == 32512 || ret == 512))
		return (!!ret);
	return (ret / 256);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item != NULL)
	{
		if (ft_strcmp(item->d_name, command) == 0)
		{
			path = path_join(bin, item->d_name);
			break ;
		}
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

int	exec(char **args, t_env *env, t_msh *mini)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;
	t_env	*temp_env;

	ret = UNKNOWN_COMMAND;
	i = 0;
	temp_env = env;
	while (temp_env && temp_env->value
		&& ft_strncmp(temp_env->value, "PATH=", 5) != 0)
		temp_env = temp_env->next;
	if (temp_env == NULL || temp_env->next == NULL)
		return (execute(args[0], args, env, mini));
	bin = ft_split(temp_env->value, ':');
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	ret = check_path(args, env, mini, path);
	free_tab(bin);
	ft_memdel(path);
	return (ret);
}
