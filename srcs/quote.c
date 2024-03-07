#include "../includes/minishell.h"

void sing_quote(char *cmd)
{
    del_quote(cmd);
    printf("%s", cmd);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **$_split(char *str)
{
    int i = 0;
    char **res = NULL;
    char **temp = NULL;
    int j = 0;
    int k = 1;
    int m = 0;

    res = (char **)malloc(sizeof(char *));
    while (str[i])
    {
        if (str[i] == '$')
        {
            temp = ft_split(&str[i], '$');
            res = (char **)realloc(res, (j + 1) * sizeof(char *));
            res[j] = (char *)malloc(ft_strlen(temp[0]) + 2);
            res[j][0] = '$';
            while (temp[0][m] != '\0')
            {
                res[j][k] = temp[0][m];
                k++;
                m++;
            }
            res[j][k] = '\0';
            j++;
            k = 1;
            m = 0;
        }
        i++;
    }
    free(temp);
    return res;
}

int check_nest_quote(char **str)
{
    int i = 0;
    int j = 0;
    int check = 0;

    while(str[i])
    {
        j = 0;
        while(str[i][j])
        {
            if(str[i][j] == '\"')
            {
                check = 1;
                break;
            }
            else
                j++;
        }
        i++;
    }
   return (check);
}


int check_dub_quote(char **str)
{
    int i = 0;
    int j = 0;
    int check = 0;

    while(str[i])
    {
        j = 0;
        while(str[i][j])
        {
            if(str[i][j] == '\"')
                check++;
            j++;
        }
        i++;
    }
    if(check % 2 == 0)
        return 1;
    else
        return 0;
}

int check_sing_quote(char **str)
{
    int i = 0;
    int j = 0;
    int check = 0;

    while(str[i])
    {
        j = 0;
        while(str[i][j])
        {
            if(str[i][j] == '\'')
                check++;
            j++;
        }
        i++;
    }
    if(check % 2 == 0)
        return 1;
    else
        return 0;
}

int var_expand(char *str, int add_space, int nested_quote)
{
    int i = 0;
    int k = 0;
    int len = 0;
    int check = 0;
    int res = 0;
    int flag = 0;
    int check2 = 0;
    char *env_var_name = NULL;

    while (str[i] != '\0') {
        if ((str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0')) {
            k = -1;
            len = strlen(str) - 1;
            i++;
            if(str[i] == '\"')
            {
                del_quote(str);
                char **res = $_split(str);
                while(res[0][++k] != '\0')
                    ft_putchar_fd(res[0][k], 1);
                check2 = 1;
                continue;
            }
            else if(str[i] == '\'')
            {
                sing_quote(&str[i]);
                flag = 1;
                break;
            }
            else
                del_quote(str);
      
            k = 0;
            env_var_name = (char *)malloc(len + 1);
            if (str[len] == ',')
            {
                len--;
                check = 1;
            }
            while (len > 0)
            {
                env_var_name[k] = str[i];
                k++;
                i++;
                len--;
            }
            env_var_name[k] = '\0';
            char *result = getenv(env_var_name);

            if (!result)
            {
                res = 1;
                break;
            }
            k = 0;
            while (result[k] != '\0')
            {
                ft_putchar_fd(result[k], 1);
                k++;
            }
            if (check)
                ft_putchar_fd(',', 1);
            if (!flag && str + 1 && add_space == 1)
                ft_putchar_fd(' ', 1);
            flag = 1; 
        }
        else if (!flag && str[i] == '\'' && !check2 && nested_quote)
            ft_putchar_fd(str[i], 1);
        else if (!flag && str[i] != '\"' && !check2 && str[i] != '\'')
            ft_putchar_fd(str[i], 1);
        i++;
    }
    if (!flag && !res) 
        ft_putchar_fd(' ', 1);
    return (res);
}

void dub_quote(char *cmd) {
    int check = 0;
    char **str = ft_split(cmd, ' ');
    int check1 = check_nest_quote(str);
    if (str == NULL)
        return;
    // printf("%s\n", str[0]);
    if(!check_dub_quote(str))
        return;
    int i = 0;
    while (str[i] != NULL) {
        check = var_expand(str[i], 1, check1);
        if(check)
        {
            char **res = $_split(str[i]);
            int j = 0;
            if(!res)
                return;
            while(res[j] != NULL)
            {
                var_expand(res[j], 0, check1);
                j++;
            }
            ft_putchar_fd(' ', 1);
        }
        i++;
    }
    // ft_putchar_fd(' ', 1);
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
            ft_strlcpy(&cmd[i], &cmd[i + 1], strlen(&cmd[i]));
            continue;
        }
        else if (cmd[i] == '\'' && double_quote == 0)
        {
            single_quote = !single_quote;
            ft_strlcpy(&cmd[i], &cmd[i + 1], strlen(&cmd[i]));
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
    // int j = 0;
    
    int len = ft_strlen(input);
    cmd->token = ft_calloc(1, sizeof(t_cmd) * len);
    cmd->redir = ft_calloc(1, sizeof(t_cmd) * len);

    while (input[*current_pos] && !cmd_delimiter(input[*current_pos]) && input)
    {
        if (input[*current_pos] != '<' && input[*current_pos] != '>')
        {
            token = get_token(input, current_pos);
            cmd->token[i] = ft_strdup(token);
            // printf("%s\n", cmd->token[i]);
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

static char	*path_found(char *path, char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (path);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path_found(path, paths));
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

// void split_cmd(t_cmd *cmd, char **env)
// {
//     int i = 0;
    
//     while(cmd->token[i])
//     {
//         char *path = find_path(cmd->token[i], env);
//         if(!path)
//             return ;
        
//     }
// }
