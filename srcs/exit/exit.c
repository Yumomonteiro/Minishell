/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:50:57 by ada-mata          #+#    #+#             */
/*   Updated: 2024/10/30 18:16:29 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_is_num(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	mini_exit(t_msh *mini, char **cmd)
{
	if (cmd[1] && cmd[2])
	{
		mini->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	}
	else if (cmd[1] && str_is_num(cmd[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1])
	{
		mini->ret = ft_atoi(cmd[1]);
	}
	else
		mini->ret = 0;
}

void	exit_error(void)
{
	printf("Execute :  ./minishell\n");
	exit(0);
}

void	exit_cleanup(char *s1, char **s2, char **s3)
{
	if (s1)
		free(s1);
	if (s2)
		free_tab(s2);
	if (s3)
		free_tab(s3);
}

void	mini_clean(t_msh *mini)
{
	if (mini->env)
		free_env(mini->env);
	if (mini->secret_env)
		free_env(mini->secret_env);
	if (mini->start)
		free_token(mini->start);
}
