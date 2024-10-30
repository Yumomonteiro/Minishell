/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:37:15 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/02 13:37:15 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

static void	print_args(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
}

int	handle_n_option(char **args, int *flag)
{
	int	i;
	int	j;

	*flag = 1;
	i = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		*flag = 0;
		i++;
	}
	return (i);
}

int	ft_echo(t_msh *mini, char **args)
{
	int		i;
	int		flag;
	char	*home;

	if (nb_args(args) > 1)
	{
		if (args[1] && ft_strcmp(args[1], "~") == 0 && args[2] == NULL)
		{
			home = get_env_value("HOME", mini->env);
			ft_putstr_fd(home, 1);
			write(1, "\n", 1);
			return (SUCCESS);
		}
		i = handle_n_option(args, &flag);
		print_args(args, i);
		if (flag)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	return (SUCCESS);
}
