#include "../../includes/minishell.h"

void	is_valid_cmd(char **cmd)
{
	if(!cmd)
		printf("valido");
}               
char **env_list_to_array(struct s_env *env_list)
{
    int count = 0;
    struct s_env *current = env_list;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    char **array = malloc((count + 1) * sizeof(char *));
    if (array == NULL) {
        return NULL;  // Falha na alocação de memória
    }

    // Passo 3: Copiar os valores para o array
    current = env_list;
    for (int i = 0; i < count; i++) {
        array[i] = strdup(current->value);
        if (array[i] == NULL) {
            // Falha na alocação de memória, limpar tudo
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
        current = current->next;
    }

    // Finalizar o array com NULL
    array[count] = NULL;

    return array;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int exec_builtin(char **args, t_msh *mini, int flag) {
    int result;

    result = 0;
    if (flag == 1) {
        if (dup2(mini->fdout, STDOUT_FILENO) == -1) {
            perror("dup2");
            return 1;
        }
        close(mini->fdout);
    }

    if (ft_strcmp(args[0], "echo") == 0) {
        result = ft_echo(mini, args);
    } else if (ft_strcmp(args[0], "cd") == 0) {
        result = ft_cd(args, mini);
    } else if (ft_strcmp(args[0], "pwd") == 0) {
        result = ft_pwd(0);
    } else if (ft_strcmp(args[0], "env") == 0) {
        result = ft_env(mini->env);
    } else if (ft_strcmp(args[0], "export") == 0) {
        result = ft_export(args, mini->env, mini->secret_env);
    } else if (ft_strcmp(args[0], "unset") == 0) {
        result = ft_unset(args, mini);
    }
    return result;
}

