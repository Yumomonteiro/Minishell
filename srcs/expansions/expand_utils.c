/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:08:24 by ada-mata          #+#    #+#             */
/*   Updated: 2024/09/02 16:08:24 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ret_size(int ret)
{
	char	*tmp;
	int		ret_len;

	tmp = ft_itoa(ret);
	ret_len = ft_strlen(tmp);
	ft_memdel(tmp);
	return (ret_len);
}

int	get_var_len(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
		return (ret_size(ret));
	if (ft_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	i = ft_strlen(var_value);
	ft_memdel(var_value);
	return (i);
}

int	arg_alloc_len(const char *arg, t_env *env, int ret)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
        if(arg == NULL)
        {
                return (-1);
        }
	while (arg[i])
	{
		if (arg[i] == EXPANSION && arg[i + 1] != '\0')
		{
			i++;
			if ((arg[i] == '\0' || !ft_isalnum(arg[i])) && arg[i] != '?')
				size++;
			else
				size += get_var_len(arg, i, env, ret);
			if (!ft_isdigit(arg[i]))
				while (arg[i + 1] && is_env_char(arg[i]))
					i++;
			else
				size--;
		}
		else
			size++;
		i++;
	}
	return (size);
}

int	calculate_total_length(char **args)
{
	int	total_length;
	int	i;

	total_length = 0;
	i = 0;
	while (args[i])
	{
		total_length += ft_strlen(args[i]) + 1;
		i++;
	}
	return (total_length);
}

char	*concat_args(char **args)
{
	int		total_length;
	char	*result;
	int		i;

	if (!args || !args[0])
		return (NULL);
	total_length = calculate_total_length(args);
	result = malloc(total_length);
	if (!result)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	result[0] = '\0';
	i = 0;
	while (args[i])
	{
		ft_strcat(result, args[i]);
		if (args[i + 1])
			ft_strcat(result, " ");
		i++;
	}
	return (result);
}
