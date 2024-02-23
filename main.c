#include "./includes/minishell.h"

void print_env1(char **env, char *name)
{
	int i;

	i = 0;

	while (env[i] != NULL)
	{
		char *key = strtok(env[i], "=");
		char *value = strtok(NULL, "=");
		if(ft_strncmp(key, name, 3) == 0)
			printf("%s:%s\n", name, value);
		i++;
	}
}

void print_env(char **env)
{
	int i;

	i = 0;

	while (env[i] != NULL)
	{
		while(env[i] != NULL)
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}

// int main(int argc, char **argv)
// {
// 	if(argc == 2)
// 	{
		
// 		sing_quote(argv[1]);
// 	}
// 	else
// 		printf("wront input\n");

	
// 	// t_env *var;
// 	// var = (t_env *)malloc(sizeof(t_env));
// 	// var->env = create_env(env);
// 	// char *new = "VAR=this";
// 	// var->env = add_env(new, var->env);
// 	// print_env(var->env);
// 	// // print_env1(var->env, "VAR");
// 	// var->env = rm_env(var->env, "LESS");
// 	// printf("REMOVENDO VAR\n");
// 	// print_env(var->env);
// 	// //print_env1(var->env, "PATH");
// 	// free_env(var->env);
// 	// free(var);

// 	return (0);
// }

int main(int argc, char **argv, char **envp)
{
        (void)argc;
        (void)argv;
        t_env *var;
        t_cmd *cmds;
        cmds = (t_cmd *)malloc(sizeof(t_cmd));
        var = (t_env *)malloc(sizeof(t_env));
        var->env = create_env(envp);
        char *str;
                while(1)
                {
                        //\033[32m➜ \033[0m \033[36m\033[1mminishell \033[34mgit:(\033[31mmain\033[34m)\033[0m 👍 "
                        str = readline("minishell: ");
                        cmds->cmd = cmd_parsing(str, cmds->cmd);
                        // if(strcmp(str, "pwd") == 0)
                        //         pwd();
			int i = -1;
			while(str[++i] && str[i + 1])
			{
                                
			        if(str[i] == '\"')
				        dub_quote(str + 1);
				else if(str[i] == '\'')
				        sing_quote(str + 1);
			}
                        // else if(strcmp(str, "env") == 0)
                        //         env(var->env);
                        // else if(strcmp(str, "minishell") == 0)
                        //         printf("alooow\n");
                        if(strncmp(str, "echo", 4) == 0)
                        {
                                echo(cmds->cmd);
                        }
                        // else if(strncmp(str, "exit", 4) == 0)
                        // {
                        //         printf("entrou");
                        //         exit(0);
                        // }
                        // else if(strncmp(str, "cd", 3) == 0)
                        //         cd(cmds->cmd, var->env);
                                
                        free(str);
                }
                
}