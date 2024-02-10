/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:21:41 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/10 12:48:51 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;

	if (!lst[0])
		return ;
	while (lst[0])
	{
		aux = (lst[0])->next;
		ft_lstdelone (lst[0], del);
		lst[0] = aux;
	}
	lst[0] = 0;
}
/*
int main()
{
    t_list *list = ft_lstnew(ft_strdup("Elemento 1"));
    list->next = ft_lstnew(ft_strdup("Elemento 2"));
    list->next->next = ft_lstnew(ft_strdup("Elemento 3"));

    t_list *current = list;
    printf("Antes\n");
    while (current)
    {
        printf("%s\n", (char*)current->content);
        current = current->next;
    }

    ft_lstclear(&list, free);
    current = list; // Redefina o ponteiro current para a lista após a limpeza.
    printf("Depois\n");
    while (current)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }

    return (0);
}
*/