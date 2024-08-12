#include "../includes/minishell.h"

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}
int	input(t_msh *mini, t_token *token)
{
        if(!token->next)
        {
               printf("-bash: syntax error near unexpected token `newline'\n");
               return 1;
        }
	ft_close(mini->fdin);
	mini->fdin = open(token->next->str, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return 0;
	}
	dup2(mini->fdin, STDIN);
        return 0;
}
int redir(t_msh *mini, t_token *token)
{

        if(!token->next)
        {
               printf("-bash: syntax error near unexpected token `newline'\n");
               return 1;
        }
    if (token->next)
    {
        ft_close(mini->fdout);
        if(is_type(token, TRUNC))
                mini->fdout = open(token->next->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        else
                mini->fdout = open(token->next->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
        if (mini->fdout == -1)
        {
            ft_putstr_fd("minishell: ", STDERR);
            ft_putstr_fd(token->str, STDERR);
            ft_putendl_fd(": No such file or directory", STDERR);
            mini->ret = 1;
            mini->no_exec = 1;
            return 0;
        }
        if (dup2(mini->fdout, STDOUT_FILENO) == -1) {
            perror("Erro ao redirecionar STDOUT");
            close(mini->fdout);
            return 0;
        }
    } 
    if(token->next->next)
    {
        token = token->next->next;
        if(is_type(token, TRUNC) == 1 || is_type(token, APPEND) == 1)
                redir(mini, token);
    }
    return 0;
}
int heredoc(t_msh *mini, t_token *token)
{
        printf("entrou\n");
    int fd[2];
    char *line;
    t_token *delimiter_token;

    // Obter o próximo token que deve ser o delimitador
    if (!token->next) {
        ft_putendl_fd(" syntax error near unexpected token `newline'", STDERR_FILENO);
        return 1;
    }
    delimiter_token = token->next;
    char *delimiter = delimiter_token->str;

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }
        printf("entrou na função\n");
    while (1)
    {
        printf("entrou no loop da função\n");
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
            break;
        ft_putendl_fd(line, fd[1]);
        free(line);
    }
    close(fd[1]);

    mini->fdin = fd[0];
    if (dup2(mini->fdin, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd[0]);
        return 1;
    }
        if(token->next->next)
        {
                token = token->next->next;
                if(is_type(token, TRUNC) || is_type(token, APPEND))
                        redir(mini, token);
                else if(is_type(token, PIPE))
                        pipex(mini, token);
        }


    return 0;
}