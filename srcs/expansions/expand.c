/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:07:58 by ada-mata          #+#    #+#             */
/*   Updated: 2024/11/09 19:28:36 by ada-mata &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}

static int	varlcpy(char *new_arg, const char *env_value, int pos)
{
	int		i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

static void	insert_var(t_expansions *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_var_value(arg, ex->j, env, ret);
	if (env_value != NULL)
		ex->i += varlcpy(ex->new_arg, env_value, ex->i);
	ft_memdel(env_value);
	if (arg[ex->j] == '?')
		ex->j++;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
}

char	*expansions(char *arg, t_env *env, int ret)
{
	t_expansions	ex;
	int				new_arg_len;

	new_arg_len = arg_alloc_len(arg, env, ret);
	ex.new_arg = malloc(sizeof(char) * new_arg_len + 2);
	if (!(ex.new_arg))
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.new_arg[ex.i++] = '$';
			else
				insert_var(&ex, arg, env, ret);
		}
		ex.new_arg[ex.i++] = arg[ex.j++];
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}

char	*get_env_var_value_cd(t_env *env, char *env_var)
{
	while (env)
	{
		if (ft_strncmp(env->value, env_var, ft_strlen(env_var)) == 0)
			return (env->value + (ft_strlen(env_var) + 1));
		env = env->next;
	}
	return (NULL);
}
