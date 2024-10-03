/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:12:59 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/02 13:12:59 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var_value_cd(t_env *env, char *env_var)
{
	while (env)
	{
		if (strncmp(env->value, env_var, strlen(env_var)) == 0)
			return (env->value + (strlen(env_var) + 1));
		env = env->next;
	}
	return (NULL);
}

void	change_env_oldpwd(t_msh *mini)
{
	char	*pwd;
	char	*pwd_var;

	pwd = getcwd(NULL, 0);
	pwd_var = malloc(strlen("PWD=") + strlen(pwd) + 1);
	strcpy(pwd_var, "PWD=");
	strcat(pwd_var, pwd);
	mini->env = rm_env(mini->env, "PWD");
	mini->env = add_env(pwd_var, mini->env);
	free(pwd_var);
	free(pwd);
}

void	change_env_pwd(t_msh *mini, char *oldpwd)
{
	char	*oldpwd_var;

	oldpwd_var = malloc(strlen("OLDPWD=") + strlen(oldpwd) + 1);
	strcpy(oldpwd_var, "OLDPWD=");
	strcat(oldpwd_var, oldpwd);
	mini->env = rm_env(mini->env, "OLDPWD");
	mini->env = add_env(oldpwd_var, mini->env);
	free(oldpwd_var);
}

static int	handle_directory_change(char *dir, t_msh *mini, char *oldpwd)
{
	if (dir)
	{
		if (chdir(dir) != 0)
		{
			ft_putstr_fd("cd: Erro ao alterar diretorio\n", STDERR);
			return (1);
		}
		change_env_pwd(mini, oldpwd);
		change_env_oldpwd(mini);
	}
	return (0);
}

int	ft_cd(char **cmd, t_msh *mini)
{
	char	*dir;
	char	*oldpwd;
	int		ret;

	oldpwd = NULL;
	dir = NULL;
	if (!mini->env)
		return (1);
	if (cmd[2] != NULL)
	{
		ft_putstr_fd("cd: too many args\n", STDERR);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (!cmd[1])
		dir = get_env_var_value_cd(mini->env, "HOME");
	else if (strcmp(&cmd[1][0], "-") == 0)
		dir = get_env_var_value_cd(mini->env, "OLDPWD");
	else
		dir = cmd[1];
	ret = handle_directory_change(dir, mini, oldpwd);
	free(oldpwd);
	return (ret);
}
