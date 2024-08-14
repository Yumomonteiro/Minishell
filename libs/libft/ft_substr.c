/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:05:28 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/10 15:06:19 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subst;
	size_t	size;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	subst = (char *)malloc(sizeof(char) * (len + 1));
	if (!subst)
		return (NULL);
	ft_strlcpy(subst, s + start, len + 1);
	return (subst);
}
/*
int main()
{
    const char *str = "hello eval";
    unsigned int start = 3; // Posição inicial
    size_t len = 7; // Tamanho da substring

    char *substring = ft_substr(str, start, len);

    if (!substring)
    {
        printf("A alocação de memória falhou.\n");
        return 1;
    }

    printf("Substring: %s\n", substring);

    free(substring);

    return 0;
}
*/