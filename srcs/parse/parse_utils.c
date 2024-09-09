/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:21:07 by ada-mata          #+#    #+#             */
/*   Updated: 2024/09/02 16:21:07 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

int	next_alloc(char *line, int *i)
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

void	handle_escapes(char *line, char *temp, int *j, int *i)
{
	temp[(*j)++] = line[++(*i)];
	(*i)++;
}

void	handle_variable_expansion(char **params, t_env *env,
									int *indices, int ret)
{
	char	*line;
	char	*temp;
	char	quote;
	int		*j;
	int		*i;

	line = params[0];
	temp = params[1];
	quote = *params[2];
	j = &indices[0];
	i = &indices[1];
	if (line[*i] == '$' && quote != '\'')
	{
		indices[2] = *i;
		(*i)++;
		while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
			(*i)++;
		strncpy(env->var_cpy, &line[indices[2]], *i - indices[2]);
		env->var_cpy[*i - indices[2]] = '\0';
		env->expanded_value = expansions(env->var_cpy, env, ret);
		strcpy(&temp[*j], env->expanded_value);
		*j += strlen(env->expanded_value);
		free(env->expanded_value);
	}
}

void	handle_word_deliminator(char *c, int *i, char *line)
{
	if (*c != ' ' && line[*i] == *c)
	{
		*c = ' ';
		(*i)++;
	}
}
