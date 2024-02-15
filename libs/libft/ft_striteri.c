/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:12:20 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/11 16:30:53 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !(*s) || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		++i;
	}
}
/*
void ft_position(unsigned int i, char *c) {
    // Exemplo de função que imprime a posição e o caractere
    printf("Posição %u: %c\n", i, *c);
}

int main() {
    char str[] = "Exemplo";
	
   ft_striteri(str, ft_position); 
    
    return 0;
}
*/
