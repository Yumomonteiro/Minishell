/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:02:43 by ada-mata          #+#    #+#             */
/*   Updated: 2024/09/03 17:02:43 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_word(char *input, char **args, int *i, int *arg_index)
{
	int	start;
	int	length;

	start = *i;
	while (input[*i] && !is_sep(input, *i))
		(*i)++;
	if (*i > start)
	{
		length = *i - start;
		args[*arg_index] = malloc(length + 1);
		if (!args[*arg_index])
		{
			perror("Failed to allocate memory");
			return (-1);
		}
		ft_strncpy(args[*arg_index], input + start, length);
		args[*arg_index][length] = '\0';
		(*arg_index)++;
	}
	return (0);
}

int	parse_separator(char *input, char **args, int *i, int *arg_index)
{
    if ((input[*i] == '>' && input[*i + 1] == '>') || (input[*i] == '<' && input[*i + 1] == '<'))
    {
        args[*arg_index] = malloc(3);
        if (!args[*arg_index])
        {
            perror("Failed to allocate memory");
            return (-1);
        }
        args[*arg_index][0] = input[*i];
        args[*arg_index][1] = input[*i + 1];
        args[*arg_index][2] = '\0';
        (*arg_index)++;
        (*i) += 2; 
    }
    else
    {
        args[*arg_index] = malloc(2);
        if (!args[*arg_index])
        {
            perror("Failed to allocate memory");
            return (-1);
        }
        args[*arg_index][0] = input[*i];
        args[*arg_index][1] = '\0';
        (*arg_index)++;
        (*i)++;
    }
    return (0);
}

int	parse_command_loop(char *input, char **args, int *arg_index)
{
    int	i;

    i = 0;
    while (input && (size_t)i < ft_strlen(input))
    {
        ft_skip_space(input, &i);
        if (input[i] == '\0')
            break;
        if (parse_word(input, args, &i, arg_index) < 0)
            return (-1);
        if (is_sep_special(input, i))
        {
            if (parse_separator(input, args, &i, arg_index) < 0)
                return (-1);
        }
    }
    return (0);
}

char	**parse_input(char *input)
{
	char	**args;
	int		arg_index;

	arg_index = 0;
	args = malloc(ARG_SIZE * sizeof(char *));
	if (!args)
		return (NULL);
	if (parse_command_loop(input, args, &arg_index) < 0)
	{
		free_tab(args);
		return (NULL);
	}
	args[arg_index] = NULL;
	return (args);
}
