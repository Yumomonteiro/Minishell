#include "../includes/minishell.h"

void sing_quote(char *cmd)
{

    del_quote(cmd);
    printf("%s", cmd);
}

void dub_quote(char *cmd) {
    char *env_var_name = NULL;
    del_quote(cmd);
    char **str = ft_split(cmd, ' ');
    int flag = 0;
    int check = 0;
    int len;
    int k;

    if (str == NULL)
        return;
    int i = 0;
    while (str[i] != NULL) {
        int j = 0;
        while (str[i][j] != '\0') {
            if ((str[i][j] == '$' && str[i][j + 1] != ' ' && str[i][j + 1] != '\0')) {
                k = 0;
                len = ft_strlen(str[i]) - 1;
                j++;
                env_var_name = (char *)malloc(len);
                if(str[i][len] == ',')
                {
                    len--;
                    check = 1;
                }
                while(len > 0)
                {
                    env_var_name[k] = str[i][j];
                    k++;
                    j++;
                    len--;
                }
                env_var_name[k] = '\0';
                char *result = getenv(env_var_name);
                if(!result)
                    break;
                int k = -1;
                while(result[++k] != '\0')
                    ft_putchar_fd(result[k], 1);
                if(check)
                    ft_putchar_fd(',', 1);
                if(!flag && str[i + 1])
                    ft_putchar_fd(' ', 1);
                flag = 1;
            } else if(!flag && str[i][j] != '\"')
                ft_putchar_fd(str[i][j], 1);
            j++;
        }
        // if(!flag)
        ft_putchar_fd(' ', 1);
         flag = 0;
         check = 0;
        i++;
    }
    // printf("\n");
    i = 0;
    while (str[i] != NULL) {
        free(str[i]);
        i++;
    }
    free(str);
}

void del_quote(char *cmd)
{
    int i;
    int double_quote;
    int single_quote;

    i = 0;
    double_quote = 0;
    single_quote = 0;

    while (cmd[i])
    {
        if (cmd[i] == '\"' && single_quote == 0)
        {
            double_quote = !double_quote;
            ft_memmove(&cmd[i], &cmd[i + 1], strlen(&cmd[i]));
            continue;
        }
        else if (cmd[i] == '\'' && double_quote == 0)
        {
            single_quote = !single_quote;
            ft_memmove(&cmd[i], &cmd[i + 1], strlen(&cmd[i]));
            continue;
        }
        i++;
    }
}

int is_quote(char c)
{
    if (c == '\'' || c == '\"')
        return (1);
    return (0);
}

int ft_is_space(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

void skip_space(char *input, int *current_pos)
{
    while (ft_is_space(input[*current_pos]))
        (*current_pos)++;
}

void	skip_quote(const char *input, int *current_pos)
{
	int		double_quote;
	int		single_quote;

	double_quote = 0;
	single_quote = 0;
	while (input[*current_pos])
	{
		if (input[*current_pos] == '\"' && single_quote == 0)
			double_quote = !double_quote;
		else if (input[*current_pos] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		(*current_pos)++;
		if (!double_quote && !single_quote)
			break ;
	}
}

int cmd_delimiter(char c)
{
    if (c == '|' || c == ';' || c == '&')
        return (1);
    return (0);
}

int token_delimiter(char c)
{
    if(ft_strchr(WHITE_SPACE, c) != 0)
        return (1);
    if (c == '|' || c == '>' || c == '<' || c == ';' || c == '&')
        return (1);
    return (0);
}

char *get_token(char *input, int *current_pos)
{
    int start;
    int end;
    char *token;

    start = *current_pos;
    end = start;
    while (input[end] && !token_delimiter(input[end]))
    {
        if (is_quote(input[end]))
            skip_quote(input, &end);
        else
            end++;
    }
    token = ft_substr(input, start, end - start);
    *current_pos = end;
    return (token);
}

char *get_redir(char *input, int *current_pos)
{
    t_redir *redir;

    redir = ft_calloc(1, sizeof(t_redir));
    if(!redir)
        return NULL;
    if(input[*current_pos] == '>')
    {
        *redir->type = input[*current_pos];
        current_pos++;
    }
    else if(ft_strncmp(&input[*current_pos], ">>", 2))
    {
        ft_strncpy(redir->type, &input[*current_pos], 2);
        current_pos += 2;
    }
    else if(input[*current_pos] == '<')
    {
        *redir->type = input[*current_pos];
        current_pos++;
    }
    skip_space(input, current_pos);
    redir->direction = get_token(input, current_pos);
    return (char *)(redir);
}

void get_cmd(char *input, int *current_pos, t_cmd *cmd)
{
    char *token;
    int i = 0;
    
    int len = ft_strlen(input);
    cmd->token = malloc(sizeof(t_cmd) * len);
    cmd->redir = malloc(sizeof(t_cmd) * len);

    while (input[*current_pos] && !cmd_delimiter(input[*current_pos]))
    {
        if (input[*current_pos] != '<' && input[*current_pos] != '>')
        {
            token = get_token(input, current_pos);
            cmd->token[i] = ft_strdup(token);
            free(token);
            i++;
        }
        else if (input[*current_pos] == '<' && input[*current_pos] == '>')
        {
             token = get_redir(input, current_pos);
             cmd->redir[i] = ft_strdup(token);
             free(token);
             i++;
        }
       skip_space(input, current_pos);
    }
}

// void get_redir(char *input, int *current_pos, t_redir *redir)
// {
//     char *token;
//     int i = 0;
    
   
//     redir->direction = malloc(sizeof(t_cmd) * MAX_TOKENS);

//     while (input[*current_pos] && !cmd_delimiter(input[*current_pos]))
//     {
//         if (input[*current_pos] == '<' && input[*current_pos] == '>')
//         {
//              token = get_redir(input, current_pos);
//              redir->direction = ft_strdup(token);
//              free(token);
//              i++;
//         }
//        skip_space(input, current_pos);
//     }
// }




// char **get_redir(char *input, int *current_pos)
// {
//       char **token_list;
//     char *cmd;

//     token_list = ft_calloc(1, sizeof(char *));
//     if(!token_list)
//         return NULL;
//     token_list = ft_calloc(3, sizeof(char *));
//     if(!token_list)
//     {
//         free(token_list);
//         return NULL;
//     }
//     while(input[*current_pos] && !cmd_delimiter(input[*current_pos]))
//     {
//     if(input[*current_pos] == '<' || input[*current_pos] == '>')
//         {
//             t_redir *redir = get_redir(input, current_pos);
//             token_list = redir;
//         }
//     }
//     return (token_list);
// }
    


// void add_token(t_cmd *cmd_list, const char *token)
// {
//     cmd_list->token = malloc(sizeof(t_cmd));

//     if(!cmd_list->token)
//         return NULL;
//     cmd_list->token[cmd_list->size++] = ft_strdup(token);
//     if(!cmd_list->token[cmd_list->size - 1])
//     {
//         free(cmd_list->token);
//         return(-1);
//     }
    
// }