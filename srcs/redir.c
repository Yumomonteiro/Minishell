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
void redir(t_msh *mini, t_token *token)
{
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
            return;
        }
        if (dup2(mini->fdout, STDOUT_FILENO) == -1) {
            perror("Erro ao redirecionar STDOUT");
            close(mini->fdout);
            return;
        }
    } 
    if(token->next->next)
    {
        token = token->next->next;
        if(is_type(token, TRUNC) == 1 || is_type(token, APPEND) == 1)
                redir(mini, token);
    }
}
// void	redir(t_msh *mini, t_token *token, int type)
// {
// 	ft_close(mini->fdout);
// 	if (type == TRUNC)
// 		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
// 	else
// 		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
// 	if (mini->fdout == -1)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR);
// 		ft_putstr_fd(token->str, STDERR);
// 		ft_putendl_fd(": No such file or directory", STDERR);
// 		mini->ret = 1;
// 		mini->no_exec = 1;
// 		return ;
// 	}
// 	dup2(mini->fdout, STDOUT);
// }
