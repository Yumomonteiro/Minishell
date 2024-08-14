/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:01:33 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/29 14:30:21 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!*lst)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

/*
int main()
{
	t_list *node1 = ft_lstnew("Primeiro no");
	t_list *node2 = ft_lstnew("Segundo no");
	t_list *node3 = ft_lstnew("Terceiro no");

	t_list *lista = NULL;

	ft_lstadd_back(&lista, node1);
	ft_lstadd_back(&lista, node2);
	ft_lstadd_back(&lista, node3);

	t_list *current = lista;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}

	ft_lstclear(&lista, free);

	return 0;
}
*/