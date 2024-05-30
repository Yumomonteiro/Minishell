#include "../includes/minishell.h"

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

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	if (!(token = malloc(sizeof(t_token)))
	|| !(token->str = malloc(sizeof(char) * next_alloc(line, i))))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->str[j++] = line[(*i)++];
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

int		ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
				&& line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

void	ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
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
	return (next);
}

int		is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;", line[i]))
		return (0);
	else if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

int		quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

int		expand_check(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 1;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\'')
			open = 0;
		else if (open == 1 && line[i] == '\'')
			open = 1;
		i++;
	}
	return (open);
}

// void del_quote(char *cmd)
// {
//     int i;
//     int double_quote;
//     int single_quote;

//     i = 0;
//     double_quote = 0;
//     single_quote = 0;

//     while (cmd[i])
//     {
//         if (cmd[i] == '\"' && single_quote == 0)
//         {
//             double_quote = !double_quote;
//             ft_strlcpy(&cmd[i], &cmd[i + 1], strlen(&cmd[i]));
//             continue;
//         }
//         else if (cmd[i] == '\'' && double_quote == 0)
//         {
//             single_quote = !single_quote;
//             ft_strlcpy(&cmd[i], &cmd[i + 1], strlen(&cmd[i]));
//             continue;
//         }
//         i++;
//     }
// }

// int is_quote(char c)
// {
//     if (c == '\'' || c == '\"')
//         return (1);
//     return (0);
// }

// int ft_is_space(char c)
// {
//     if (c == ' ' || (c >= 9 && c <= 13))
//         return (1);
//     return (0);
// }

// void skip_space(char *input, int *current_pos)
// {
//     while (ft_is_space(input[*current_pos]))
//         (*current_pos)++;
// }

// void	skip_quote(const char *input, int *current_pos)
// {
// 	int		double_quote;
// 	int		single_quote;

// 	double_quote = 0;
// 	single_quote = 0;
// 	while (input[*current_pos])
// 	{
// 		if (input[*current_pos] == '\"' && single_quote == 0)
// 			double_quote = !double_quote;
// 		else if (input[*current_pos] == '\'' && double_quote == 0)
// 			single_quote = !single_quote;
// 		(*current_pos)++;
// 		if (!double_quote && !single_quote)
// 			break ;
// 	}
// }

// int cmd_delimiter(char c)
// {
//     if (c == '|' || c == ';' || c == '&')
//         return (1);
//     return (0);
// }

// int token_delimiter(char c)
// {
//     if(ft_strchr(WHITE_SPACE, c) != 0)
//         return (1);
//     if (c == '|' || c == '>' || c == '<' || c == ';' || c == '&')
//         return (1);
//     return (0);
// }

