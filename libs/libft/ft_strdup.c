/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:51:25 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 11:34:13 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = ((char *)malloc(ft_strlen(s1) + 1));
	if (!s2)
		return (0);
	ft_memcpy (s2, s1, ft_strlen(s1) + 1);
	return (s2);
}
/*
int main(void)
{
	char str[] = "hello eval";
	printf("%s\n", ft_strdup(str));
	return (0);
}
*/