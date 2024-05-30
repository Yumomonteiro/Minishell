// #include "../includes/minishell.h"

// void sing_quote(char *cmd)
// {
//     int len = ft_strlen(cmd);
//     int i = 0;
//     if(cmd[0] == '$')
//     {
//         if(cmd[len - 1] == '\"')
//             while(i < len - 1)
//                 write(1, &cmd[i++], 1);
//         else
//             printf("%s ", cmd);
//     }
//     else
//     {
//         del_quote(cmd);
//         printf("%s ", cmd);
//     }
// }

// char **$_split(char *str)
// {
//     int i = 0;
//     char **res = NULL;
//     char **temp = NULL;
//     int j = 0;
//     int k = 1;
//     int m = 0;

//     res = (char **)malloc(sizeof(char *));
//     while(str[i] == '$' && str[i + 1] == '$')
//         i++;
//     while (str[i])
//     {
//         if (str[i] == '$')
//         {
//             temp = ft_split(&str[i], '$');
//             res = (char **)realloc(res, (j + 1) * sizeof(char *));
//             res[j] = (char *)malloc(ft_strlen(temp[0]) + 2);
//             res[j][0] = '$';
//             while (temp[0][m] != '\0')
//             {
//                 res[j][k] = temp[0][m];
//                 k++;
//                 m++;
//             }
//             res[j][k] = '\0';
//             j++;
//             k = 1;
//             m = 0;
//         }
//         i++;
//     }
//     free(temp);
//     return res;
// }

// void process_variable(char *str, int *i, int *check, int *flag) {
//     int pos = 0;
//     int k = 0;
//     int len = strlen(str) - 1;
//     if (str[len] == '\'') 
//         pos = 1;

//     (*i)++;
//         del_quote(str);
//         k = 0;
//         char *env_var_name = (char *)malloc(len + 1);
//         if (str[len] == ',') {
//             len--;
//             *check = 1;
//         }
//         while (len > 0) {
//             env_var_name[k] = str[*i];
//             k++;
//             (*i)++;
//             len--;
//         }
//         env_var_name[k] = '\0';
//         char *result = getenv(env_var_name);
//         if (!result) {
//             *check = 1;
//             return;
//         }
//         k = 0;
//         while (result[k] != '\0') {
//             ft_putchar_fd(result[k], 1);
//             k++;
//         }
//         if (*check)
//             ft_putchar_fd(',', 1);
//         if(pos)
//             ft_putchar_fd('\'', 1);
//         if (!(*flag))
//             ft_putchar_fd(' ', 1);
//         *flag = 1;
//         free(env_var_name);
//     }

// int var_expand(char *str, int nested_quote)
// {
//     int i = 0;
//     int res = 0;
//     int flag = 0;
//     int k = 0;
//     int check2 = 0;
//     int len = ft_strlen(str);

//     while (str[i] != '\0') {
//         if ((str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0')) {
//             int check = 0;

//                 while(str[k++])
//                 {
//                     if(str[k] == '\'')
//                     {
//                         while((k < len + 1 || str[k] == '\'') && (str[k] != '\"'))
//                         {
//                             write(1, &str[k++], 1);
//                             check2 = 1;
//                         }
//                         ft_putchar_fd(' ', 1);
//                         break;
//                     }
//                     if(str[k] == '\"')
//                     {
//                         del_quote(str);
//                         while((k < len + 1 || str[k] == '\"') && (str[k] != '\''))
//                         {
//                             write(1, &str[k++], 1);
//                         }
//                          ft_putchar_fd(' ', 1);
//                         break;
//                     }
//                 }
//             while(str[i] == '$' && str[i + 1] == '$')
//                 i++;
//             if(!check2)
//                 process_variable(str, &i, &check, &flag);
//             if (check) {
//                 res = 1;
//                 break;
//             }
//         }
//         if(str[i] == '\"' && str[i + 1] == '\'')
//         {
//             i++;
//             while(str[i] == '\'' && str[i + 1] == '\'')
//                 i++;
//         }
//         else if (!flag && str[i] == '\'' && nested_quote && !check2)
//             ft_putchar_fd(str[i], 1);
//         else if (!flag && str[i] != '\"' && str[i] != '\'' && !check2)
//              ft_putchar_fd(str[i], 1);
//         i++;
//     }
//     if (!flag && !res) 
//         ft_putchar_fd(' ', 1);
//     return (res);
// }

// int get_pos(char *str)
// {
//     int i = -1;
//     int pos = 0;
//     while(str[++i])
//     {
//         if(str[i] == '\"')
//             pos = i;
//     }
//     return (pos);
// }

// int s_quote_after(char *str)
// {
//     int pos;
//     int k = 0;
//     pos = get_pos(str);
//     while(str[pos])
//     {
//         if(str[pos] == '\'')
//             k++;
//         pos++;
//     }
//     return k;
// }

// int check_$(char *str)
// {
//     int i = 0;

//     while(str[i])
//     {
//         if(str[i] == '$')
//             return (1);
//         i++;
//     }
//     return (0);
// }

// void dub_quote(char *cmd) {
//     int check = 0;
//     int s_quote = 0;
//     int check_$_sgn = 0;
//     s_quote = s_quote_after(cmd);
//     check_$_sgn = check_$(cmd);
//     if(s_quote % 2 != 0)
//         return ;
//     char **str = ft_split(cmd, ' ');
//     int check1 = check_nest_quote(str);
//     if (!str)
//         return;
//     int i = 0;
//     while (str[i] != NULL && str) {
//         check = var_expand(str[i], check1);
//         if(check)
//         {
//             char **res = $_split(str[i]);
//             int j = 0;
//             if(!res)
//                 return;
//             while(res[j] != NULL)
//             {
//                 var_expand(res[j], check1);
//                 j++;
//             }
//             ft_putchar_fd(' ', 1);
//         }
//         i++;
//     }
//     i = 0;
//     while (str[i] != NULL) {
//         free(str[i]);
//         i++;
//     }
//     free(str);
// }

// char *get_token(char *input, int *current_pos)
// {
//     int start;
//     int end;
//     char *token;

//     start = *current_pos;
//     end = start;
//     while (input[end] && !token_delimiter(input[end]))
//     {
//         if (is_quote(input[end]))
//             skip_quote(input, &end);
//         else
//             end++;
//     }
//     token = ft_substr(input, start, end - start);
//     *current_pos = end;
//     return (token);
// }

// t_redir	*get_redir(char *input, int *curr_pos)
// {
// 	t_redir	*redir;

// 	redir = ft_calloc(1, sizeof(t_redir));
// 	if (!redir)
// 		return 0;
//     if (!ft_strncmp(&input[*curr_pos], "<<", 2))
// 	{
// 		ft_strncpy(redir->type, (char *)&input[*curr_pos], 2);
// 		*curr_pos += 2;
// 	}
// 	else if (input[*curr_pos] == '<')
// 		*redir->type = input[(*curr_pos)++];
// 	else if (!ft_strncmp(&input[*curr_pos], ">>", 2))
// 	{
// 		ft_strncpy(redir->type, (char *)&input[*curr_pos], 2);
// 		*curr_pos += 2;
// 	}
// 	else if (input[*curr_pos] == '>')
// 		*redir->type = input[(*curr_pos)++];
// 	skip_space(input, curr_pos);
// 	redir->direction = get_token(input, curr_pos);
// 	return (redir);
// }

// void get_input(char *input, int *current_pos, t_cmd *cmd)
// {
//     char *token;
//     int i = 0;
//     int check = 0;
    
//     int len = ft_strlen(input);
//     cmd->token = ft_calloc(1, sizeof(t_cmd) * len);
//     cmd->redir = ft_calloc(1, sizeof(t_cmd) * len);
//     cmd->type = ft_calloc(1, sizeof(t_cmd) * len);
//     check = check_$(input);
//     if(check)
//         cmd->find_$ = TRUE;
//     while (input[*current_pos] && !cmd_delimiter(input[*current_pos]) && input && i < len)
//     {
//         if (input[*current_pos] != '<' && input[*current_pos] != '>')
//         {
//             // if(input[*current_pos] == '$')
//             token = get_token(input, current_pos);
//             cmd->token[i] = ft_strdup(token);
//             cmd->type[i] = 0;
//             free(token);
//             i++;
//         }
//         else if (input[*current_pos] == '<' || input[*current_pos] == '>')
//         {
//              token = (char *)get_redir(input, current_pos);
//              cmd->redir[i] = ft_strdup(token);
//              cmd->type[i] = 1;
//              free(token);
//              i++;
//         }
//        skip_space(input, current_pos);
//     }
// }

// int is_pipe(char *str)
// {
//     int i;

//     i = 0;
//     while(str[i])
//     {
//         if(str[i] == '|')
//             return(1);
//         i++;
//     }
//     return (0);
// }

// // void get_pipe(char *input, int *current_pos, t_cmd *cmd)
// // {
// //     char *token;
// //     int i = 0;
    
// //     int len = ft_strlen(input);
// //     cmd->pipe = ft_calloc(1, sizeof(t_cmd));
// //         if(input[*current_pos] == '|')
// //         {
// //             printf("entrou\n");
// //         }
// //         i++;
// //         skip_space(input, current_pos);

// // }

// int	find_path(char *cmd, char **envp)
// {
// 	char	**paths;
// 	char	*path;
// 	int		i;
// 	char	*part_path;

// 	i = 0;
// 	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
// 		i++;
// 	paths = ft_split(envp[i] + 5, ':');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		part_path = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(part_path, cmd);
// 		free(part_path);
// 		if (access(path, F_OK) == 0)
// 			return (1);
// 		free(path);
// 		i++;
// 	}
// 	i = -1;
// 	while (paths[++i])
// 		free(paths[i]);
// 	free(paths);
// 	return (0);
// }

// void	get_cmd(char **cmd, char **envp, t_cmd *input)
// {
//     int i;
//     int j = 0;
// 	int	path;
//     int len = 0;
//     while(cmd[len])
//         len++;
//     input->cmd = (char**)ft_calloc(1, sizeof(t_cmd) * len);
//     i = 0;
// 	if(!cmd[0])
// 		return ;
//     while(cmd[i])
//     {
//         if (ft_strchr(cmd[i], '/') != NULL)
// 		    input->cmd[j++] = ft_strdup(cmd[i]);
//         else
// 		    path = find_path(cmd[i], envp);
// 	    if (!path)
// 	    {
//             i++;
//             continue;
// 	    }
//         else if(path)
//         {
//             input->cmd[j++] = ft_strdup(cmd[i]);
//             input->type[j] = 2;
//         }
//         i++;
//     }
// }

// void error(char *str)
// {
//     printf("%s\n", str);
// }