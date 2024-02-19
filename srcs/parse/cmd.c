/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:52:16 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/16 15:51:43 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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