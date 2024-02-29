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

void free_cmds(char **cmds)
{
	int i = -1;
	while(cmds[++i])
		free(cmds[i]);
	free(cmds);
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
		int pos = 0;
        t_env *var;
        t_cmd *cmds;
	
        cmds = (t_cmd *)malloc(sizeof(t_cmd));
        var = (t_env *)malloc(sizeof(t_env));
		cmds = (t_cmd *)malloc(sizeof(t_cmd));
			if (!cmds) 
			{
				free(var);
				return 1;
			}
        var->env = create_env(envp);
        char *str;
                while(1)
                {
					   str = readline("minishell: ");
						add_history(str); 

					

						cmds->token = get_cmd(str, &pos, cmds->token);
						int j = -1;
						while(cmds->token[++j])
							printf("%s\n", cmds->token[j]);
						
						int i = -1;
						while(str[++i] && str[i + 1])
						{
											
								if(str[i] == '\"')
									dub_quote(str);
							else if(str[i] == '\'')
									sing_quote(str);
						}
                        // if(strncmp(str, "echo", 4) == 0)
                        // {
                        //         ft_echo(cmds->token);
                        // }
                        // cd(cmds->cmd, var->env);
                        free(str);
                }
				free(cmds);
                
}

// int main() {
//     char input[] = "this is 'quoted string' and this is not";
//     int current_pos = 0;

//     while (input[current_pos]) {
//         char *token = get_token(input, &current_pos);
// 		del_quote(token);
//         if (token) {
//             printf("Token: %s\n", token);
//             free(token);
//         }
//         // Skip white spaces
//         while (input[current_pos] && cmd_delimiter(input[current_pos]))
//             current_pos++;
//     }

//     return 0;
// }