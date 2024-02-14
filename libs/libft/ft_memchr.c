/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:34:51 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 10:25:33 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
/*
int main() {
    const char *str = "Hello, World!";
    char character = 'o';

    void *result = ft_memchr(str, character, ft_strlen(str));

    if (result != NULL) {
        printf("Caractere '%c' encontrado em: %s\n", character, (char *)result);
    } else {
        printf("Caractere '%c' não encontrado na string.\n", character);
    }

    return 0;
}
*/
