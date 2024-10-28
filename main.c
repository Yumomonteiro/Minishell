/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata & yude-oli <marvin@42.fr>  <ad    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:46:41 by ada-mata          #+#    #+#             */
/*   Updated: 2024/10/28 18:29:30 by ada-mata &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	func_initiate(char **env, t_msh *mini)
{
	mini->env = NULL;
	mini->start = NULL;
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	mini->secret_env = NULL;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_init(mini, env);
	secret_env_init(mini, env);
	shell_level(mini->env);
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
}

void	free_all(t_msh *mini)
{
	if (mini->env)
		free_env(mini->env);
	if (mini->secret_env)
		free_env(mini->secret_env);
	if (mini->start)
		free_token(mini->start);
	if (mini->env->value)
		free(mini->env->value);
	if (mini->secret_env->value)
		free(mini->secret_env->value);
}

char **parse_command(char *input) {
    char **args = malloc(ARG_SIZE * sizeof(char *));
    int arg_index = 0;
    int i = 0;

    while (input && input[i] && (size_t)i < ft_strlen(input))
		{
        while (isspace(input[i]))
					i++;
        if (input[i] == '\0')
					break;
        int start = i;
        while (input[i] && !is_sep(input, i))
          i++;
        if (i > start)
				{
            int length = i - start;
            args[arg_index] = malloc(length + 1);
            ft_strncpy(args[arg_index], input + start, length);
            args[arg_index][length] = '\0';
            arg_index++;
        }
        if (is_sep(input, i))
				{
            args[arg_index] = malloc(2);
            args[arg_index][0] = input[i];
            args[arg_index][1] = '\0';
            arg_index++;
            i++;
        }
    }
    args[arg_index] = NULL;
    return args;
}

char *concat_args(char **args)
{
    if (!args || !args[0])
			return NULL;
    int total_length;
		int	i;
		char *result;
		
		total_length = 0;
    i = 0;
    while (args[i])
		{
        total_length += ft_strlen(args[i]) + 1;
        i++;
    }
    result = malloc(total_length);
    if (!result) {
        perror("Failed to allocate memory");
        return NULL;
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

int	main(int ac, char **av, char **env)
{
	t_msh	mini;
	char	*line;
	char **args = NULL;
	char *line_arg;

	if (ac > 1 && av)
		exit_error();
	func_initiate(env, &mini);
	while (1)
	{
		line = readline("minishell: ");
		if (handle_sig_eof(line) == 1)
			continue;
		if (line[0])
		{
			add_history(line);
			if ((quote_check(&mini, &line)))
				continue;
			args = parse_command(line);
			line_arg = concat_args(args);
			mini.start = get_tokens(line_arg, mini.env, mini.ret);
			if (parse(&mini) == 1) 
				continue;
			minishell(&mini);
			free_token(mini.start);
			free_tab(args);
			free(line_arg);
		}
		free(line);
	}
	free_all(&mini);
	return (mini.ret);
}



