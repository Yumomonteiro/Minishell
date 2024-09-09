/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:08:24 by ada-mata          #+#    #+#             */
/*   Updated: 2024/09/03 19:45:59 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_eof(void)
{
	printf("exit\n");
	exit(0);
}

int	handle_sig_eof(char *line)
{
	if (line == NULL)
	{
		handle_eof();
		return (1);
	}
	return (0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
