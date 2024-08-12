/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:08:57 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 15:48:17 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0')
	{
		if (i < (n -1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(str1[i]) - (unsigned char)(str2[i]));
}
/*
 int main()
 {
	char str1[] = "Hello eval";
	char str2[] = "Hello fval";
	size_t n = 8;
	int resultado = ft_strncmp(str1, str2, n);

	if (resultado < 0) {
        printf("str1 é menor que str2\n");
    } else if (resultado > 0) {
        printf("str1 é maior que str2\n");
    } else {
        printf("str1 e str2 são iguais nos primeiros %zu caracteres\n", n);
    }

    return 0;
}
*/