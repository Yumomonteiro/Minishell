#include "../../includes/minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void		free_node(t_msh *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

void unset_env_var(char *var, t_env **env, t_msh *mini)
{
	t_env *current = *env;
	t_env *prev = NULL;
	t_env *tmp;

	while (current)
	{
		if (ft_strncmp(var, current->value, env_size(current->value)) == 0)
		{
			tmp = current->next;
			if (prev)
				prev->next = tmp;
			else
				*env = tmp;
			free_node(mini, current);
			break;
		}
		prev = current;
		current = current->next;
	}
}

void unset_secret_env_var(char *var, t_env **secret_env, t_msh *mini)
{
	t_env *current = *secret_env;
	t_env *prev = NULL;
	t_env *tmp;

	while (current)
	{
		if (ft_strncmp(var, current->value, env_size(current->value)) == 0)
		{
			tmp = current->next;
			if (prev)
				prev->next = tmp;
			else
				*secret_env = tmp;
			free_node(mini, current);
			break;
		}
		prev = current;
		current = current->next;
	}
}

int ft_unset(char **a, t_msh *mini)
{
	if (!(a[1]))
		return (SUCCESS);

	unset_env_var(a[1], &(mini->env), mini);
	unset_secret_env_var(a[1], &(mini->secret_env), mini);

	return (SUCCESS);
}