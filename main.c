/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:46:41 by ada-mata          #+#    #+#             */
/*   Updated: 2024/09/01 19:55:15 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token	*next_run(t_token *token, int skip)
{
	type_arg(token, 0);
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

t_token	*skip_cmd(t_token *tmp)
{
	while (tmp && tmp->next)
	{
		if (tmp->type == CMD || tmp->type == ARG)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp && (tmp->type == TRUNC || tmp->type == APPEND
				||tmp->type == HEREDOC || tmp->type == PIPE
				|| tmp->type == INPUT))
			return (tmp->prev);
		else
			tmp = tmp->next;
	}
	return (tmp);
}

t_token	*execute_command_or_pipe(t_msh *mini, t_token *token, t_token *tmp)
{
	int	res;

	res = 0;
	if (is_type(tmp->next, PIPE) == 1 && !is_builtin(token->str))
	{
		res = pipex(mini, token);
		if (res == 1)
			return (NULL);
		token = tmp->next;
	}
	if (token && is_type(token, PIPE) == 0)
	{
		if (token->prev && is_type(token->prev, HEREDOC) == 1)
			token = token->next;
		else
			exec_cmd(mini, token);
	}
	return (next_run(mini->start, SKIP));
}

int	handle_special_tokens(t_msh *mini, t_token *tmp)
{
	int	res;

	res = 0;
	if (is_type(tmp->next, HEREDOC) == 1)
	{
		res = heredoc(mini, tmp->next);
		if (res == 1)
			return (1);
	}
	else if (is_type(tmp->next, TRUNC) == 1 || is_type(tmp->next, APPEND) == 1)
	{
		res = redir(mini, tmp->next);
		if (res == 1)
			return (1);
	}
	else if (is_type(tmp->next, INPUT) == 1)
	{
		res = input(mini, tmp->next);
		if (res == 1)
			return (1);
	}
	return (0);
}

void	process_tokens(t_msh *mini)
{
	t_token	*token;
	t_token	*tmp;

	token = next_run(mini->start, NOSKIP);
	while (token)
	{
		tmp = token;
		if (tmp->next)
			tmp = skip_cmd(tmp);
		if (handle_special_tokens(mini, tmp) == 1)
			return ;
		token = execute_command_or_pipe(mini, token, tmp);
	}
}

void	cleanup(t_msh *mini)
{
	reset_std(mini);
	close_fds(mini);
	reset_fds(mini);
}

void	minishell(t_msh *mini)
{
	process_tokens(mini);
	cleanup(mini);
}

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

void	exit_error(void)
{
	printf("Execute :  ./minishell\n");
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	t_msh	mini;
	char	*line;

	mini.env = NULL;
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.secret_env = NULL;
	if (ac > 1 && av)
		exit_error();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_init(&mini, env);
	secret_env_init(&mini, env);
	shell_level(mini.env);
	while (1)
	{
		line = readline("minishell: ");
		if (handle_sig_eof(line) == 1)
			continue ;
		if (line[0])
		{
			add_history(line);
			quote_check(&mini, &line);
			mini.start = get_tokens(line, mini.env, mini.ret);
			parse(&mini);
			minishell(&mini);
			free(mini.start);
		}
	}
	free_env(mini.env);
	return (mini.ret);
}
