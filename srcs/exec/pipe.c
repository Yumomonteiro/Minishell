/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:52:20 by yude-oli          #+#    #+#             */
/*   Updated: 2024/09/02 19:39:47 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_join_pipe(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}
t_env	*get_path_variable(t_env *env)
{
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	return (env && env->value) ? env : NULL;
}
char	*search_in_paths(char **bin_paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (bin_paths[i])
	{
		path = path_join_pipe(bin_paths[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		ft_memdel(path);
		i++;
	}
	return (NULL);
}
char	*find_executable(char *cmd, t_env *env)
{
	char	**bin_paths;
	char	*path;
	t_env	*temp_env;

	temp_env = get_path_variable(env);
	if (!temp_env)
		return (NULL);
	bin_paths = ft_split(temp_env->value + 5, ':');
	if (!bin_paths)
		return (NULL);
	path = search_in_paths(bin_paths, cmd);
	if (path)
	{
		free_tab(bin_paths);
		return (path);
	}
	free_tab(bin_paths);
	return (NULL);
}

int	count_args(t_token *token)
{
	int count = 0;
	while (token && token->type != PIPE)
	{
		count++;
		token = token->next;
	}
	return (count);
}

char **build_args(t_token *token)
{
	int argc = count_args(token);
	char **args = malloc((argc + 1) * sizeof(char *));
	int i = 0;
	while (token && token->type != PIPE && (token->type == ARG || token->type == CMD)) {
		args[i++] = token->str;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

void	exec_pipe_cmd(t_msh *mini, t_token *token)
{
	if (mini)
	{
		char **args = build_args(token);
		char *path = find_executable(args[0], mini->env);
		char **env_array = env_list_to_array(mini->env);
		if (!env_array) {
			perror("env_to_str");
			exit(EXIT_FAILURE);
		}
		if (path) {
				if(check_args(args, token) == 0)
				{
					execve(path, args, env_array);
					exit(EXIT_FAILURE);
				}
				token = token->next;
				exec_cmd(mini, token);
		} else {
			perror("Command not found");
			exit(EXIT_FAILURE);
		}
	}
}

int pipex(t_msh *mini, t_token *token)
{
	int pipefd[2];
	pid_t pid;
	mini->pipin = STDIN_FILENO;
	while (token)
	{
		if (token->type == PIPE) {
			token = token->next;
			continue;
		}
		if (pipe(pipefd) == -1) {
			perror("pipe");
			return 1;
		}
		if ((pid = fork()) == -1) {
			perror("fork");
			return 1;
		}
		if (pid == 0)
		{
			dup2(mini->pipin, STDIN_FILENO);            
			t_token *next_token = token;
			while (next_token && (next_token->type != PIPE)) 
			{
				if(next_token && (next_token->type == TRUNC || next_token->type == APPEND))
					redir(mini, next_token);
				// if(next_token && (next_token->type == INPUT))
				//         input(mini, next_token);
				// if(next_token && (next_token->type == HEREDOC))
				//         heredoc(mini, next_token);
				next_token = next_token->next;
			}
			if (next_token && next_token->type == PIPE)
			{
				dup2(pipefd[1], STDOUT_FILENO);
			}
			close(pipefd[0]);
			close(pipefd[1]); 
			exec_pipe_cmd(mini, token);
			perror("exec_cmd");
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipefd[1]); 
			waitpid(pid, &mini->ret, 0);
			mini->pipin = pipefd[0]; // Guarda o input para o próximo comando
			while (token && token->type != PIPE) {
				token = token->next;
			}
			if (token) {
				token = token->next;
			}
		}
	}
	return 0;
}
