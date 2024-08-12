#include "../includes/minishell.h"


// void  redir_builtin(char **cmd, t_msh * mini, t_token *token)
// {
//         int flag = 0;
//         while(token)
//         {

//                 if(is_type(token, TRUNC) || is_type(token, APPEND))
//                 {
//                         flag = 1;
//                         redir(mini, token);
//                         exec_builtin(cmd, mini, flag);
//                 }
//                 token = token->next;
//         }
//         reset_std(mini);
// }
// int has_redir(t_token *token)
// {
//         t_token *current;
//         current = token;
//         while(current)
//         {
//                 if(is_type(current, TRUNC) || is_type(current, APPEND))
//                         return (1);
//                 current = current->next;
//         }
//         return 0;
// }

// void exec_cmd(t_msh *mini, t_token *token) {
//     char **cmd;
//     int i;
//     cmd = cmd_tab(token);

//     t_sig sig;
//     i = 0;
//     while (cmd && cmd[i]) {
//         cmd[i] = expansions(cmd[i], mini->env, mini->ret);
//         i++;
//     }

//     if (cmd && ft_strcmp(cmd[0], "exit") == 0) {
//         exit(EXIT_FAILURE);
//     } else if (cmd && is_builtin(cmd[0])) {
//         if (has_redir(token)) {
//             redir_builtin(cmd, mini, token);
//         } else if (search_pipe(token)) {
//             printf("Detectado pipe para comando built-in: %s\n", cmd[0]);
//             //exec_pipes(mini, token);
//         } else {
//             mini->ret = exec_builtin(cmd, mini, 0);
//         }
//     } else if (cmd) {
//         if (search_pipe(token)) {
//             printf("Detectado pipe para comando: %s\n", cmd[0]);
//             //exec_pipes(mini, token);
//         } else {
//             mini->ret = exec_bin(cmd, mini->env, mini, &sig);
//         }
//     }

//     ft_close(mini->pipin);
//     ft_close(mini->pipout);
//     mini->pipin = -1;
//     mini->pipout = -1;
//     free_tab(cmd);
// }