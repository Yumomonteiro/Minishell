/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:34:45 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/10 14:34:20 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f (lst->content);
		lst = lst->next;
	}
}
/*
void print_string(void *str)
{
    printf("%s\n", (char *)str);
}
int main()
{
    t_list *list = NULL;
    ft_lstadd_front(&list, ft_lstnew("Hello"));
    ft_lstadd_front(&list, ft_lstnew("World"));
    ft_lstadd_front(&list, ft_lstnew("from"));
    ft_lstadd_front(&list, ft_lstnew("the"));
    ft_lstadd_front(&list, ft_lstnew("list"));

    printf("Elements of the list:\n");
    ft_lstiter(list, print_string);

	
    return 0;
}
*/