/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:47 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/07 11:44:48 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}
/*
int main() {
	char buffer[20] = "hello evaluator"; // Um buffer de 20 bytes

	// Preenche o buffer com 'A' usando a função ft_memset
	ft_memset(buffer, 'A', 10);

	// Imprime o conteúdo do buffer
	printf("Buffer: %s\n", buffer);

	return 0;
}*/