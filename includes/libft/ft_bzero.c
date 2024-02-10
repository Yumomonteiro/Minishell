/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:13:20 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 10:11:42 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset (s, '\0', n);
}
/*
int main()
{
    char str[] = "Hello, World!";
    size_t len = sizeof(str) - 1; // Exclui o nulo

    printf("Antes %s\n", str);

    ft_bzero(str, len);

    printf("Depois %s\n", str);

    return 0;
}*/