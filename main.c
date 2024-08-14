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

void	minishell(t_msh *mini)
{
	t_token	*token;
	
	token = NULL;
	token = next_run(mini->start, NOSKIP);
	exec_cmd(mini, token);
	token = next_run(token, SKIP);
}


int		main(int ac, char **av, char **env)
{
	t_msh	mini;
	char *line = NULL;
	mini.env = NULL;
	mini.secret_env = NULL;

	(void)ac;
	(void)av;
	env_init(&mini, env);
	secret_env_init(&mini, env);
	while (1)
	{
		line = readline("minishell: ");
		if(line[0])
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
	free_env(mini.secret_env);
	return (mini.ret);
}