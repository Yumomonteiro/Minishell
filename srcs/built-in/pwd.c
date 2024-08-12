#include "../../includes/minishell.h"

int    ft_pwd(int flag)
{
        char *pwd;
        pwd = getcwd(NULL, 0);
        if(!pwd)
        {
                perror("-> minishell error: pwd");
                return 0;
        }
        if (flag == 0)
                printf("%s\n", pwd);
        free(pwd);
        return (0);
}