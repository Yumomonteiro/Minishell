#include "../../includes/minishell.h"

int		ft_env(t_env *env)
{
	if(!env)
		return (SUCCESS);
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 1);
	return (SUCCESS);
}