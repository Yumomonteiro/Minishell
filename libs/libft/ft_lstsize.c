/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:45:24 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/10 14:49:23 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
/*
int main() {
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	t_list *list = node1; //é o primeiro nó da lista
	node1->next = node2;  // Conecta node1 a node2
	node2->next = node3;  // Conecta node2 a node3

	int size = ft_lstsize(list);

	printf("Tamanho da lista: %d\n", size);

	return 0;
}
*/