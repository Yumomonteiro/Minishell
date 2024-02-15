/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:17:40 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/10 15:47:05 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
    char str1[] = "Hello, World!";
    char str2[] = "Hello, C Programming!";

    size_t len1 = 13; 
    size_t len2 = 21;

    // Usando ft_memcmp para comparar as duas strings
    int result = ft_memcmp(str1, str2, len1 < len2 ? len1 : len2);

    if (result < 0)
    {
        printf("str1 é menor do que str2\n");
    }
    else if (result > 0)
    {
        printf("str1 é maior do que str2\n");
    }
    else
    {
        printf("str1 e str2 são iguais\n");
    }

    return 0;
}
*/
