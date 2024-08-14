/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:48:49 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 13:23:13 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	tot_size;
	void	*dst;

	tot_size = size * count;
	dst = malloc(tot_size);
	if (!dst)
		return (0);
	ft_memset (dst, 0, tot_size);
	return (dst);
}
/*
int main(void)
{
    size_t count = 5; // Número de elementos
    size_t size = sizeof(int); // Tamanho elemento
    
    int *arr = (int *)ft_calloc(count, size);

    if (!arr)
    {
        printf("A alocação de memória falhou.\n");
        return 1;
    }
	size_t i = 0;
    while (i < count)
    {
        printf("arr[%zu] = %d\n", i, arr[i]);
		i++;
    }

    free(arr);

    return 0;
}
*/
