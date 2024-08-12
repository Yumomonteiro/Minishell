#include "../../includes/minishell.h"

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * i)))
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}
int has_redir(t_token *token)
{
        t_token *current;
        current = token;
        while(current)
        {
                if(is_type(current, TRUNC) || is_type(current, APPEND))
                        return (1);
                current = current->next;
        }
        return 0;
}void pipex_builtin(t_msh *mini, t_token *token) {
    int pipefd[2];
    pid_t pid;
    int fd_in = STDIN_FILENO; // O input inicial é o STDIN

    while (token) {
        if (token->type == PIPE) {
            token = token->next;
            continue;
        }
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return;
        }
        if ((pid = fork()) == -1) {
            perror("fork");
            return;
        }

        if (pid == 0) { // Processo filho
            dup2(fd_in, STDIN_FILENO); // Redireciona a entrada

            t_token *next_token = token;
            while (next_token && next_token->type != PIPE) {
                next_token = next_token->next;
            }
            if (next_token && next_token->type == PIPE) {
                dup2(pipefd[1], STDOUT_FILENO); // Redireciona a saída para o pipe
            }

            close(pipefd[0]);
            close(pipefd[1]); // Fecha o descritor de escrita no pipe

            char **cmd = cmd_tab(token);
            if (cmd && is_builtin(cmd[0])) {
                exec_builtin(cmd, mini, 0); // Executa o builtin
            } else {
                exec_pipe_cmd(mini, token); // Executa o comando
            }

            // Se execve falhar, deve-se sair do processo filho
            perror("exec_cmd");
            exit(EXIT_FAILURE);
        } else { // Processo pai
            close(pipefd[1]); // Fecha o descritor de escrita no pipe
            waitpid(pid, &mini->ret, 0);
            fd_in = pipefd[0]; // Guarda o input para o próximo comando
            
            // Avance para o próximo comando após o PIPE
            while (token && token->type != PIPE) {
                token = token->next;
            }
            if (token) {
                token = token->next;
            }
        }
    }
}


void  redir_builtin(char **cmd, t_msh * mini, t_token *token)
{
        int flag = 0;
        while(token)
        {

                if(is_type(token, TRUNC) || is_type(token, APPEND))
                {
                        flag = 1;
                        redir(mini, token);
                        exec_builtin(cmd, mini, flag);
                }
                token = token->next;
        }
        reset_std(mini);
}
void exec_cmd(t_msh *mini, t_token *token)
{
    char **cmd;
    int i;
    cmd = cmd_tab(token);
    
    
    t_sig sig;
    i = 0;
	while(cmd && cmd[i])
	{
		cmd[i] = expansions(cmd[i], mini->env, mini->ret);
		i++;
	}
       
        if (cmd && ft_strcmp(cmd[0], "exit") == 0)
                exit(EXIT_FAILURE);
        else if (cmd && is_builtin(cmd[0]))
        {
                
                if(search_pipe(token))
                {
                        pipex_builtin(mini, token);
                         
                }
                
                else if(has_redir(token))
                {
                        redir_builtin(cmd, mini, token);
                }    
                else
                {
                        mini->ret = exec_builtin(cmd, mini, 0);
                }
                                
        }
        else if (cmd)
        {
                 
                mini->ret = exec_bin(cmd, mini->env, mini, &sig);
        }
        
        ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
        free_tab(cmd);
}