/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:46:41 by ada-mata          #+#    #+#             */
/*   Updated: 2024/09/18 15:39:54 by ada-mata &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	func_initiate(char **env, t_msh *mini)
{
	mini->env = NULL;
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

void free_all(t_msh *mini)
{
    free_env(mini->env);
    free_env(mini->secret_env);
}

void free_tokens(t_token *token)
{
    t_token *tmp;

    while (token) {
        tmp = token;
        token = token->next;
        if (tmp->str)
            free(tmp->str); 
        free(tmp); 
    }
}


int	main(int ac, char **av, char **env)
{
	t_msh	mini;
	char	*line;

	if (ac > 1 && av)
		exit_error();
	func_initiate(env, &mini);
	while (1)
	{
		line = readline("minishell: ");
		if (handle_sig_eof(line) == 1)
			continue ;
		if (line[0])
		{
			add_history(line);
			if ((quote_check(&mini, &line)))
				continue ;
			mini.start = get_tokens(line, mini.env, mini.ret);
			if (parse(&mini) == 1)
				continue ;
			minishell(&mini);
			/* free_tokens(mini.start); */
		}
	}
	free_all(&mini);
	free(mini.env->value);
	free(mini.secret_env->value);
	return (mini.ret);
}
