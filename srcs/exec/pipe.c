#include "../../includes/minishell.h"

char *path_join_pipe(const char *s1, const char *s2) {
    char *tmp;
    char *path;

    tmp = ft_strjoin(s1, "/");
    path = ft_strjoin(tmp, s2);
    ft_memdel(tmp);
    return path;
}

char *find_executable(char *cmd, t_env *env) {
    char **bin_paths;
    char *path;
    int i = 0;
    t_env *temp_env = env;
    // Encontrar a variável de ambiente PATH
    while (temp_env && temp_env->value && ft_strncmp(temp_env->value, "PATH=", 5) != 0)
        temp_env = temp_env->next;

    if (!temp_env || !temp_env->value)
        return NULL;

    bin_paths = ft_split(temp_env->value + 5, ':');
    if (!bin_paths)
        return NULL;

    while (bin_paths[i]) {
        path = path_join_pipe(bin_paths[i], cmd);
        if (access(path, X_OK) == 0) {
            free_tab(bin_paths);
            return path;
        }
        ft_memdel(path);
        i++;
    }

    free_tab(bin_paths);
    return NULL;
}

int count_args(t_token *token) {
    int count = 0;
    while (token && token->type != PIPE) {
        count++;
        token = token->next;
    }
    return count;
}

char **build_args(t_token *token) {
    int argc = count_args(token);
    char **args = malloc((argc + 1) * sizeof(char *));
    int i = 0;

    while (token && token->type != PIPE && (token->type == ARG || token->type == CMD)) {
        args[i++] = token->str;
        token = token->next;
    }
    args[i] = NULL;
    return args;
}

void exec_pipe_cmd(t_msh *mini, t_token *token) {
    if (mini) {
        char **args = build_args(token);
        char *path = find_executable(args[0], mini->env);
        char **env_array = env_list_to_array(mini->env);

//        // Imprimir informações para depuração
//         printf("Comando: %s\n", args[0]);
//         if (path) {
//             printf("Path encontrado: %s\n", path);
//         } else {
//             printf("Path não encontrado\n");
//         }
//         for (int i = 0; args[i]; i++) {
//             printf("Arg[%d]: %s\n", i, args[i]);
//         }

        if (!env_array) {
            perror("env_to_str");
            exit(EXIT_FAILURE);
        }
        if (path) {
                //printf("entrou no path\n");
                execve(path, args, env_array);
                perror("execve");
                exit(EXIT_FAILURE);
        } else {
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }
}


int pipex(t_msh *mini, t_token *token) {
    int pipefd[2];
    pid_t pid;
    mini->pipin = STDIN_FILENO; // O input inicial é o STDIN
    while (token) {
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
