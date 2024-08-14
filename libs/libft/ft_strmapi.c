/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:54:20 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 15:32:51 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	str = ft_strdup(s);
	if (!s || !f || !str)
		return (0);
	i = 0;
	while (str[i])
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
/*
char uppercase(unsigned int i, char c) {
    if (i % 2 == 1 && c >= 'a' && c <= 'z') {
        return c - 32;  
    return c;  
}

int main() {
    const char *s = "hello, World!";
    
    char *nova_string = ft_strmapi(s, uppercase);

    printf("string Original: %s\n", s);
    printf("nova String em Maiusculas: %s\n", nova_string);

    free(nova_string);

    return 0;
}
*/