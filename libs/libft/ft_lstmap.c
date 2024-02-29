/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:17:30 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/28 13:46:13 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*elem;

	if (!lst)
		return (0);
	new_lst = NULL;
	while (lst)
	{
		elem = ft_lstnew((f(lst->data)));
		if (!elem)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		ft_lstadd_back (&new_lst, elem);
		lst = lst->next;
	}
	return (new_lst);
}
/*
void *uppercase(void *str)
{
    char *s = (char *)str;
    char *result = (char *)malloc(ft_strlen(s) + 1);
    if (result)
	{
	size_t	i;
	
	i = 0;
        while (s[i])
        {
            result[i] = ft_toupper((unsigned char)s[i]);
			i++;
		}
        result[ft_strlen(s)] = '\0';
    }
    return result;
}
int main()
{
    t_list *list = NULL;
    ft_lstadd_back(&list, ft_ft_lstclear(&new_lst, del)lstnew("Hello"));
    ft_lstadd_back(&list, ft_lstnew("World"));
    ft_lstadd_back(&list, ft_lstnew("from"));
    ft_lstadd_back(&list, ft_lstnew("the"));
    ft_lstadd_back(&list, ft_lstnew("list"));

    t_list *new_list = ft_lstmap(list, uppercase, free);

    printf("list:\n");
    t_list *current = new_list;
    while (current)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
    return 0;
}
*/