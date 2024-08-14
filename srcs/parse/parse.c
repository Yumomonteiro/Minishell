#include "../../includes/minishell.h"

t_token *next_token(char *line, t_env *env, int *i, int ret)
{
    t_token *token;
    int j;
    char c;
    char temp[1024];

    j = 0;
    c = ' ';

    if (!(token = malloc(sizeof(t_token))))
        return NULL;

    while (line[*i] && (line[*i] != ' ' || c != ' '))
    {
        if (c == ' ' && (line[*i] == '\'' || line[*i] == '"'))
            c = line[(*i)++];
        else if (c != ' ' && line[*i] == c)
        {
            c = ' ';
            (*i)++;
        }
        else if (line[*i] == '\\' && line[*i + 1])
            handle_escapes(line, temp, &j, i);
        else if (line[*i] == '$' && c != '\'')
            handle_variable_expansion(line, env, temp, &j, i, ret, c);
        else
            temp[j++] = line[(*i)++];
    }

    temp[j] = '\0';
    token->str = strdup(temp);
    token->next = NULL;
    return token;
}

t_token *get_tokens(char *line, t_env *env, int ret)
{
    t_token *prev;
    t_token *next;
    int i;
    int sep;

    prev = NULL;
    next = NULL;
    i = 0;
    ft_skip_space(line, &i);
    while (line[i])
    {
        sep = ignore_sep(line, i);
        next = next_token(line, env, &i, ret);
        next->prev = prev;
        if (prev)
            prev->next = next;
        prev = next;
        type_arg(next, sep);
        ft_skip_space(line, &i);
    }
    if (next)
        next->next = NULL;
    while (next && next->prev)
        next = next->prev;
    return next;
}

int		is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
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
