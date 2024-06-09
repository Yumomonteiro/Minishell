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

// void exec_cmd(t_msh *mini, t_token *token)
// {
//     char **cmd;
//     int i;
//     cmd = cmd_tab(token);
//     i = 0;
// 		// printf("cmd[1][0] = %c\n", cmd[1][0]);

// 	while(cmd && cmd[i])
// 	{
// 		if(cmd[i][0] == '\'')
// 			break;
// 		else
// 			cmd[i] = expansions(cmd[i], mini->env, mini->ret);
// 		i++;
// 	}
//   if (cmd && ft_strcmp(cmd[0], "exit") == 0)
//       exit (SUCCESS);
//   else if (cmd && is_builtin(cmd[0]))
//       mini->ret = exec_builtin(cmd, mini);
//     free_tab(cmd);
// }

void exec_cmd(t_msh *mini, t_token *token)
{
    char **cmd;
    int i;
    cmd = cmd_tab(token);
    i = 0;

    while (cmd && cmd[i])
    {
        if (!(token->quoted && token->quote_type == '\'')) // Skip expansion if single-quoted
        {
            if (!token->quoted || token->quote_type == '\"') // Expand if not quoted or double-quoted
            {
                cmd[i] = expansions(cmd[i], mini->env, mini->ret);
            }
        }
        i++;
        token = token->next; // Move to the next token
    }

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

