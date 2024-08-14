/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:31:44 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 16:12:26 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
/*
int main()
{
	char dest[] = "";
	char src[] = "Hello Eval";
	size_t size = 12;

	ft_strlcpy(dest, src, size);
	printf("tamanho da origem %zu\n ", ft_strlcpy(dest, src, size));
	printf("dest: %s", dest);
}
*/