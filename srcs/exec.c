#include "../includes/minishell.h"

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * i)))
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}


void exec_cmd(t_msh *mini, t_token *token)
{
    char **cmd;
    cmd = cmd_tab(token);

    if (cmd && ft_strcmp(cmd[0], "exit") == 0)
    {
        exit(SUCCESS);
    }
    else if (cmd && is_builtin(cmd[0]))
    {
        mini->ret = exec_builtin(cmd, mini);
    }

    free_tab(cmd);
}



