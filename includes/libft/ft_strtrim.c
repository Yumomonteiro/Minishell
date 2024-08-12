/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:27:44 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 17:43:56 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*trim;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	trim = ft_substr(s1, 0, i + 1);
	if (!trim)
		return (0);
	return (trim);
}
/*
int main ()
{
	char str[] = "hellheheheheheorhe";
	char str2[] = "he";
	printf("%s\n", ft_strtrim(str, str2));
	
	return (0);
}
*/