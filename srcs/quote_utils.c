#include "../includes/minishell.h"

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

void literal_check(t_cmd *cmd, char **str)
{
    int dub_quote;

    dub_quote = check_dub_quote(str);

    if(dub_quote)
        cmd->literal = TRUE;
    else
        cmd->literal = FALSE;

}