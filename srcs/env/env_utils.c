/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:57:27 by ada-mata &        #+#    #+#             */
/*   Updated: 2024/11/09 19:57:27 by ada-mata &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	special_env(t_env *env, char *pwd)
{
	char	*env_pwd;

	env_pwd = ft_strjoin("PWD=", pwd);
	env_add("SHLVL=1", env);
	env_add(env_pwd, env);
	env_add("_=/usr/bin/env", env);
}
