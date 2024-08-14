#include "../../includes/minishell.h"

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "<<") == 0 && separator == 0)
		token->type = HEREDOCS;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

int		next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

void handle_escapes(char *line, char *temp, int *j, int *i)
{
    temp[(*j)++] = line[++(*i)];
    (*i)++;
}

void handle_variable_expansion(char *line, t_env *env, char *temp, int *j, int *i, int ret, char quote)
{
    if (line[*i] == '$' && quote != '\'')
    {
        int start = *i;
        (*i)++;
        while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
        {
            (*i)++;
        }
        char var_part[1024];
        strncpy(var_part, &line[start], *i - start);
        var_part[*i - start] = '\0';

        char *expanded_value = expansions(var_part, env, ret);
        strcpy(&temp[*j], expanded_value);
        *j += strlen(expanded_value);
        free(expanded_value);
    }
}