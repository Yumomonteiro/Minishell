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

int	ft_echo(t_msh *mini, char **args)
{
	int		i;
	int		n_option;
	char	*home;

	i = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		if (args[1] && ft_strcmp(args[1], "~") == 0 && args[2] == NULL)
		{
			home = get_env_value("HOME", mini->env);
			ft_putstr_fd(home, 1);
			write(1, "\n", 1);
			return (SUCCESS);
		}
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		print_args(args, i);
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
