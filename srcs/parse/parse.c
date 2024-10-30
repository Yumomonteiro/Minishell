/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:59:18 by ada-mata          #+#    #+#             */
/*   Updated: 2024/09/02 16:59:18 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_special_variable(char *line, char *temp, int *indices, int ret)
{
	int		*j;
	int		*i;
	char	*ret_str;
	int		k;

	j = &indices[0];
	i = &indices[1];
	if (line[*i] == '$' && line[*i + 1] == '?')
	{
		ret_str = ft_itoa(ret);
		k = 0;
		while (ret_str[k])
			temp[(*j)++] = ret_str[k++];
		free(ret_str);
		(*i) += 2;
	}
}

void	process_token_character(char **params, int *indices,
									int ret, t_env *env)
{
	char	*line;
	char	*temp;
	char	*c;
	int		*j;
	int		*i;

	line = params[0];
	temp = params[1];
	c = params[2];
	j = &indices[0];
	i = &indices[1];
	if (*c == ' ' && (line[*i] == '\'' || line[*i] == '"'))
		*c = line[(*i)++];
	else if (*c != ' ' && line[*i] == *c)
		handle_word_deliminator(c, i, line);
	else if (line[*i] == '\\' && line[*i + 1])
		handle_escapes(line, temp, j, i);
	else if (line[*i] == '$' && line[*i + 1] == '?')
		handle_special_variable(line, temp, indices, ret);
	else if (line[*i] == '$' && *c != '\'')
		handle_variable_expansion(params, env, indices, ret);
	else
		temp[(*j)++] = line[(*i)++];
}

t_token	*next_token(char *line, t_env *env, int *i, int ret)
{
	t_token	*token;
	int		indices[3];
	char	c;
	char	temp[1024];
	char	*params[4];

	indices[0] = 0;
	indices[1] = *i;
	indices[2] = 0;
	c = ' ';
	params[0] = line;
	params[1] = temp;
	params[2] = &c;
	token = malloc(sizeof(t_token));
	if (!(token))
		return (NULL);
	while (line[indices[1]] && (line[indices[1]] != ' ' || c != ' '))
		process_token_character(params, indices, ret, env);
	temp[indices[0]] = '\0';
	token->str = strdup(temp);
	token->next = NULL;
	*i = indices[1];
	return (token);
}

t_token	*get_tokens(char *line, t_env *env, int ret)
{
	t_token	*last_token;
	t_token	*token_head;

	last_token = NULL;
	if (!line)
		return (0);
	ft_skip_space(line, &(int){0});
	token_head = parse_tokens(line, env, ret, &last_token);
	if (last_token)
		last_token->next = NULL;
	while (token_head && token_head->prev)
		token_head = token_head->prev;
	return (token_head);
}

int	parse(t_msh *mini)
{
	t_token	*token;

	token = mini->start;
	if (token == NULL)
		return (1);
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		token = token->next;
	}
	return (0);
}
