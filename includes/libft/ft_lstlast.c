/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:55:13 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/10 14:14:25 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
/*
int main() {
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	// Cria um ponteiro para o início da lista
	t_list *list = node1; // 
	node1->next = node2;  // Conecta node1 a node2
	node2->next = node3;  // Conecta node2 a node3

	// Usa ft_lstlast para obter o último nó
	t_list *lastNode = ft_lstlast(list);

	// Imprime o conteúdo do último nó
	if (lastNode)
		printf("Conteúdo do último nó: %s\n", (char *)lastNode->content);
	else
		printf("A lista está vazia.\n");

	// Libera a memoria
	ft_lstclear(&list, free);

	return 0;
}
*/