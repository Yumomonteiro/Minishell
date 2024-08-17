/* #include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		is_builtin(char *command)
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

int		exec_builtin(char **args, t_msh *mini)
{
	int		result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	// if (ft_strcmp(args[0], "cd") == 0)
	// 	result = ft_cd(args, mini->env);
	// if (ft_strcmp(args[0], "pwd") == 0)
	// 	result = ft_pwd();
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(mini->env);
	if (ft_strcmp(args[0], "export") == 0)
		ft_export(args, mini->env, mini->secret_env);
	if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, mini);
	return (result);
}
 */