/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:01:33 by yude-oli          #+#    #+#             */
/*   Updated: 2024/01/27 15:19:11 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, int data)
{
	t_list	*new;
	t_list	*last;

	new = ft_lstnew(data);
	if (!data)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new; 
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