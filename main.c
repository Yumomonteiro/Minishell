#include <stdio.h>
#include "includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
        if(argc)
                cd_builtin(argv, envp);
        return 0;
}