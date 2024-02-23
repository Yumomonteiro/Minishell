#include "../includes/minishell.h"

void sing_quote(char *cmd)
{
   int len = ft_strlen(cmd);
   len--;
   int i = 0;
    while(i < len)
    {
        write(1, &cmd[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

void dub_quote(char *cmd) {
    char *env_var_name = NULL;
    char **str = ft_split(cmd, ' ');
    int flag = 0;
    int len;
    int k;

    if (str == NULL) {
        return;
    }

    int i = 0;
    while (str[i] != NULL) {
        int j = 0;
        while (str[i][j] != '\0') {
            if (!(str[i][j] == '$' && str[i][j + 1] != ' ' && str[i][j + 1] != '\0')) {
                  if (!flag && str[i][j] != '\"') {
                    ft_putchar_fd(str[i][j], 1);
                } 
            } else {
                k = 0;
                len = ft_strlen(str[i]) - 1;
                j++;
                env_var_name = (char *)malloc(len);
                if(str[i][len] == '\"' || str[i][len] == ',')
                    len--;
                while(len > 0)
                {
                    env_var_name[k] = str[i][j];
                    k++;
                    j++;
                    len--;
                }
                env_var_name[k] = '\0';
                char *result = getenv(env_var_name);
                    printf("%s ", result);;
                flag = 1;
            }
            j++;
        }
        if(!flag)
            ft_putchar_fd(' ', 1);
         flag = 0;
        i++;
    }
    printf("\n");
    i = 0;
    while (str[i] != NULL) {
        free(str[i]);
        i++;
    }
    free(str);
}

