#include "../includes/minishell.h"


char is_space(char *str)
{
        int i = 0;
        while(str[i])
        {
                if(str[i] == ' ')
                        return (' ');
                else if(str[i] == '\t')
                        return ('\t');
                i++;
        }
        return (' ');
}

char **cmd_parsing(char *str, char **cmd)
{
        char check_space = is_space(str);
        cmd = ft_split(str, check_space);
        if(!cmd)
                return 0; 
        return(cmd);       
}