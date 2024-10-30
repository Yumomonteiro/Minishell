/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:46:41 by ada-mata          #+#    #+#             */
/*   Updated: 2024/10/30 18:40:31 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	func_initiate(char **env, t_msh *mini)
{
	mini->env = NULL;
	mini->start = NULL;
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	mini->secret_env = NULL;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_init(mini, env);
	secret_env_init(mini, env);
	shell_level(mini->env);
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
}

void	process_line(char *line, t_msh *mini)
{
	char	**args;
	char	*line_arg;

	args = parse_input(line);
	line_arg = concat_args(args);
	mini->start = get_tokens(line_arg, mini->env, mini->ret);
	if (parse(mini) == 1)
	{
		free_tab(args);
		free_token(mini->start);
		free(line_arg);
		return ;
	}
	minishell(mini);
	free_tab(args);
	free_token(mini->start);
	free(line_arg);
}

void	shell_loop(t_msh *mini)
{
	char	*line;

	while (1)
	{
		line = readline("minishell: ");
		if (handle_sig_eof(line) == 1)
			continue ;
		if (line[0])
		{
			add_history(line);
			if (!quote_check(mini, &line))
			{
				process_line(line, mini);
			}
		}
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_msh		mini;

	if (ac > 1 && av)
		exit_error();
	func_initiate(env, &mini);
	shell_loop(&mini);
	free_all(&mini);
	return (mini.ret);
}
