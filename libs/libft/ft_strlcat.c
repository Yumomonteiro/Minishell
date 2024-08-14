/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:20:05 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 12:56:26 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	i;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	c = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && c + 1 < dstsize)
	{
		dst[c] = src[i];
		c++;
		i++;
	}
	dst[c] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
/*
int main() {
    char dest[30] = "Hello, ";
    char src[] = "world!";

    size_t result = ft_strlcat(dest, src, sizeof(dest));

    printf("Resultado: %zu\n", result);
    printf("String resultante: \"%s\"\n", dest);

    return 0;
}*/
