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

void	change_env_oldpwd(t_msh *mini)
{
	char	*pwd;
	char	*pwd_var;

	pwd = getcwd(NULL, 0);
	pwd_var = malloc(ft_strlen("PWD=") + ft_strlen(pwd) + 1);
	ft_strcpy(pwd_var, "PWD=");
	ft_strcat(pwd_var, pwd);
	mini->env = rm_env(mini->env, "PWD");
	mini->env = add_env(pwd_var, mini->env);
	free(pwd_var);
	free(pwd);
}

void	change_env_pwd(t_msh *mini, char *oldpwd)
{
	char	*oldpwd_var;
	oldpwd_var = malloc(ft_strlen("OLDPWD=") + ft_strlen(oldpwd) + 1);
	ft_strcpy(oldpwd_var, "OLDPWD=");
	ft_strcat(oldpwd_var, oldpwd);
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

int	get_directory(char **cmd, t_msh *mini, char **dir)
{
	if (!cmd[1])
		*dir = get_env_var_value_cd(mini->env, "HOME");
	else if (ft_strcmp(cmd[1], "-") == 0)
	{
		*dir = get_env_var_value_cd(mini->env, "OLDPWD");
		if (*dir)
			printf("%s\n", *dir);
	}
	else if (strcmp(cmd[1], "~") == 0)
		*dir = get_env_var_value_cd(mini->env, "HOME");
	else
		*dir = cmd[1];
	if (*dir)
		return (0);
	return (1);
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
	if (cmd[1] && cmd[2] != NULL)
	{
		ft_putstr_fd("cd: too many args\n", STDERR);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (get_directory(cmd, mini, &dir))
		return (1);
	ret = handle_directory_change(dir, mini, oldpwd);
	free(oldpwd);
	return (ret);
}
