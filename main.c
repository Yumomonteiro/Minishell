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

int		is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		ft_memdel(tmp->value);
		ft_memdel(tmp);
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

void	free_token(t_token *start)
{
	while (start && start->next)
	{
		ft_memdel(start->str);
		start = start->next;
		ft_memdel(start->prev);
	}
	if (start)
	{
		ft_memdel(start->str);
		ft_memdel(start);
	}
}

int		quote_check(t_msh *mini, char **line)
{
	if (quotes(*line, 2147483647))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		mini->ret = 2;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

void	parse(t_msh *mini)
{

	t_token	*token;


	token = mini->start;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		token = token->next;
	}
}

void	minishell(t_msh *mini)
{
	t_token	*token;
	
	token = next_run(mini->start, NOSKIP);
	exec_cmd(mini, token);
	token = next_run(token, SKIP);
}
int		main(int ac, char **av, char **env)
{
	t_msh	mini;
	// t_token *token = NULL;
	char *line;


	(void)ac;
	(void)av;
	env_init(&mini, env);
	while (1)
	{
		line = readline("minishell: ");
		add_history(line);
		if (quote_check(&mini, &line))
			return 0;
		mini.start = get_tokens(line);
		parse(&mini);
		minishell(&mini);
		free(mini.start);
	}
	free_env(mini.env);
	return (mini.ret);
}