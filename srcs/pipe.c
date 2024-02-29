#include "../includes/minishell.h"

static char	*path_found(char *path, char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (path);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if(!(envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL))
		error();
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path_found(path, paths));
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

void	exec_cmd(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	if(!cmd[0])
		error();
	if (ft_strchr(cmd[0], '/') != NULL)
		path = cmd[0];
	else
		path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

void	error(void)
{
	perror("\033[31mError\e[0m");
	exit(EXIT_FAILURE);
}

void	child_process(char **argv, char **env, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(filein);
	exec_cmd(argv[2], env);
}

void	parent_process(char **argv, char **env, int *fd)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(fileout);
	exec_cmd(argv[3], env);
}

void pipex(int argc, char **argv, char **env)
{
    int		fd[2];
	pid_t	pid;

	if (argc > 3)
	{
		if (!env || !env[0] || !env[2])
		{
			printf("\033[31mError: No environment variables\n\e[0m");
			return ;
		}
		if (pipe(fd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			child_process(argv, env, fd);
		waitpid(pid, NULL, 0);
		parent_process(argv, env, fd);
	}
    else 
        error();
}