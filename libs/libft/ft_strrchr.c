/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:50:27 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 17:27:11 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return ((char *)(str + i));
		i --;
	}
	return (NULL);
}
/*
int main()
{
	char str1[] = "Hello evaluator";
	int c = 'o';
	printf("%s\n", ft_strrchr(str1, c));
	return (0);
}
*/
