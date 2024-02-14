/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:37:11 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/10 12:49:06 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->next = lst[0];
		lst[0] = new;
	}
	else
		return ;
}
/*
int main() {
	
	t_list *no1 = ft_lstnew("Node 1");

	t_list *list;
	list = no1;
	
	// Imprime a lista antes de adicionar o novo nó
	printf("Lista antes da adição:\n");
	t_list *current = list;
	while (current) {
		printf("%s\n", (char *)current->content);
		current = current->next;
	}

	// Cria um novo nó
	t_list *no2 = ft_lstnew("Node 2");

	// Adiciona o novo nó ao início da lista
	ft_lstadd_back(&list, no2);

	// Imprime a lista após a adição
	printf("\nLista após a adição:\n");
	current = list;
	while (current) {
		printf("%s\n", (char *)current->content);
		current = current->next;
	}

	// Lembre-se de liberar a memória alocada para os nós
	ft_lstclear(&list, free);

	return 0;
}
*/