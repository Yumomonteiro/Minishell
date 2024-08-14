#include "../../includes/minishell.h"

int			str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void swap(t_env *a, t_env *b) {
    char *temp = a->value;
    a->value = b->value;
    b->value = temp;
}

void sort_env(t_env *env) {
    if (env == NULL)
        return;

    int swapped;
    t_env *ptr1;
    t_env *lptr = NULL;

    swapped = 1;
    while (swapped) {
        swapped = 0;
        ptr1 = env;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->value, ptr1->next->value) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}

void print_sorted_env(t_env *env)
{
	sort_env(env);
	while (env && env->next != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env->value, 1);
	}
		
}

