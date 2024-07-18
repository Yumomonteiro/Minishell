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
        t_token *tmp;
        token = next_run(mini->start, NOSKIP);
        //printf("%s\n", token->str);
        while(token)
        {
                //printf("%s\n", token->str);
                if(is_type(token->next, TRUNC) == 1)
                        redir(mini, token->next);
                else if(is_type(token->next, APPEND) == 1)
                        redir(mini, token->next);
                // else if(token->type == PIPE)
                //         pipex(mini);
                if(token)
                {
                        if (token->next && token->next->next)
                                if(is_type(token->next->next, TRUNC) == 1 || is_type(token->next->next, APPEND) == 1)
                                {
                                        tmp = token;
                                        redir(mini, token->next->next);
                                        exec_cmd(mini, tmp);
                                }
                                else
                                        exec_cmd(mini, token);
                        else
                                exec_cmd(mini, token);
                }
                token = next_run(mini->start, SKIP); 
        }
        reset_std(mini);
	close_fds(mini);
	reset_fds(mini);
}
void handle_eof(void) {
    printf("exit\n");
    exit(0);
}
int handle_sig_eof(char *line)
{
         if(line == NULL)
        {
                handle_eof();
                return(1);
        }
        return 0;
}

void handle_sigint(int sig) {
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void exit_error(void)
{
        printf("Execute :  ./minishell\n");
        exit(0);
}
int		main(int ac, char **av, char **env)
{
        t_msh	mini;
        mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	if(ac > 1 && av)
    	        exit_error();
	char *line;
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, SIG_IGN);

	env_init(&mini, env);
        shell_level(mini.env);
	while (1)
	{
		line = readline("minishell: ");
                if(handle_sig_eof(line) == 1)
                        continue;
                if (line[0])
                {
                        add_history(line);
                        quote_check(&mini, &line);
                        mini.start = get_tokens(line);
                        parse(&mini);
                        minishell(&mini);
                        free(mini.start);
                }
	}
	free_env(mini.env);
	return (mini.ret);
}
