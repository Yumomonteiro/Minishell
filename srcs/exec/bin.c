#include "../../includes/minishell.h"

int			error_message(char *path)
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

int	                exec_magic(char *path, char **args, t_env *env, t_msh *mini, t_sig *sig)
{
	char	**env_array;
	char	*ptr;
	int		ret;
	ret = SUCCESS;
	sig->pid = fork();
	if (sig->pid == 0)
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
		waitpid(sig->pid, &ret, 0);
	ret = (ret == 32256 || ret == 32512) ? ret / 256 : !!ret;
	return (ret);
}

char		*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char		*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(folder);
	return (path);
}

int			exec_bin(char **args, t_env *env, t_msh *mini, t_sig *sig)
{
    int		i;
    char	**bin;
    char	*path;
    int		ret;
    t_env	*temp_env;

    i = 0;
    temp_env = env;
    while (temp_env && temp_env->value && ft_strncmp(temp_env->value, "PATH=", 5) != 0)
        temp_env = temp_env->next;
    if (temp_env == NULL || temp_env->next == NULL)
        return (exec_magic(args[0], args, env, mini, sig));
    bin = ft_split(temp_env->value, ':');
    if (!args[0] && !bin[0])
        return (ERROR);
    i = 1;
    path = check_dir(bin[0] + 5, args[0]);
    while (args[0] && bin[i] && path == NULL)
        path = check_dir(bin[i++], args[0]);
        
    if (path != NULL)
        ret = exec_magic(path, args, env, mini, sig);
    else
        ret = exec_magic(args[0], args, env, mini, sig);
    free_tab(bin);
    ft_memdel(path);
    return (ret);
}
