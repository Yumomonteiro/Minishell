/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:41:29 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 11:26:50 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s != '\0' && uc != (unsigned char)(*s))
		s++;
	if (uc == (unsigned char)(*s))
		return ((char *)s);
	return (NULL);
}
/*
int main(void)
{
	char str[] = "hello eval";
	int chr = 'o';
	char *resultado = ft_strchr(str, chr);
	printf("%s\n", resultado);
	return (0);
}
*/
